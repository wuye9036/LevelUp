#--------------------------------------------------------------------------
# Tool Name:  High/Low Clustering (Getis-Ord General G)
# Source Name: GeneralG.py
# Version: ArcGIS 9.2
# Author: ESRI
#
# This tool calculates the General G spatial autocorrelation statistic.
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Imports
#--------------------------------------------------------------------------
import sys, os, locale

# HelperFunctions.py contains functions and custom classed used by all
# Stat tools.
from GPHelper.HelperFunctions import *
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#General G Tool Functions 
#   get_inputs -		parses sys.argv and returns an object of class gen
#					   that contains each user specified input argument.
#
#   build_value_lists - constructs dictionary structures for X, Y and Z.
#
#   calculate_GeneralG - calculate General G index and Z Score.
#
#   output_results -	if requested, a pop up display of results is
#					   presented.
#--------------------------------------------------------------------------
def get_inputs():
	"""Given the list of inputs for the script when run, return an object
	containing the variables for the script"""
	try:
		sInputFCs = sys.argv[1]					 # Input Feature Class(Multiple)
		sZField = sys.argv[2].upper()			  # Attribute Field Name
		sDisplayIt = sys.argv[3]				   # w/or without pop up results
		sSpaceConcept = sys.argv[4]				# Concept of spatial relations
		sDistanceMethod = sys.argv[5]		  # Euclidean or Manhattan distance
		sStandardization = sys.argv[6]			 # Standardization Method
		dValue = str(sys.argv[7])
		dDistance = locale.atof(dValue)						  # Distance Band or threshold distance
		sWeights = sys.argv[8]					 # optional weights matrix file
		
		fBeta = 1.0
		if sSpaceConcept == sInvDist2: fBeta = 2.0
		if sSpaceConcept.find(sFromFile) >= 0: bWtsFile = iTrue
		else: bWtsFile = iFalse
		iOffset = 0
		if sStandardization == sNone: sStandardization = None 
		if sWeights == "#" or sWeights == "": sWeights = None
	except: raise ReportError (msgParseErr)

	#Make a generic object, populate it with our variables, then return it
	#Make a generic object, populate it with our variables, then return it
	ret_list = []
	try:
		for sInputFC in sInputFCs.split(';'):
			obj = Gen()
			if sInputFC[0] == '\'' and sInputFC[-1] == '\'':
				sInputFC = eval(sInputFC)
			obj.add('sInputFC',sInputFC)
			obj.add('sZField',sZField)
			obj.add('sDisplayIt', sDisplayIt)
			obj.add('sSpaceConcept', sSpaceConcept)
			obj.add('sDistanceMethod', sDistanceMethod)
			obj.add('sStandardization',sStandardization)
			obj.add('dDistance', dDistance)
			obj.add('sWeights', sWeights)
			obj.add('fBeta',fBeta)
			obj.add('bWtsFile', bWtsFile)
			obj.add('iOffset', iOffset)
			
			ret_list.append(obj)
	except: raise ReportError (msgInputsErrr)
	return ret_list

def build_value_lists(dcWeight, dcRowSum):
	"""Reads through feature table extracting geometry and field info.
	   Returns this information in dictionary structures."""
	# Process user specified weights matrix, if necessary.  Format: From, To, Weight
	# If we encounter errors, we will abort and use default (inverse distance)
	bDefault = iTrue
	sIDField = None
	dDistAllSum = 0.0
	if inputs.bWtsFile:
		bDefault, sIDField, dcRowSum, dDistAllSum = read_user_weights(properties, inputs.sWeights, dcWeight, dcRowSum, dDistAllSum, iTrue)

	sFieldList = properties.sFID + ";" + properties.sShapeField + ";" + inputs.sZField
	if sIDField: sFieldList = sFieldList + ";" + sIDField
	pRows = pGP.SearchCursor(inputs.sInputFC,"","",sFieldList)
	# pRows = pGP.SearchCursor(inputs.sInputFC)   
	pRow = pRows.Next()
	iRec = 0
	lsBadRecs = []
	iBadRecCnt = 0

	pGP.AddMessage (sBuildingLists)
	while pRow <> None:
		iRec = iRec + 1
		try:
			sKey = str(pRow.GetValue(properties.sFID))
			pGeometry = pRow.GetValue (properties.sShapeField)
			sCentroid = pGeometry.TrueCentroid
			dX = locale.atof (str (sCentroid.split()[0]))
			dY = locale.atof (str (sCentroid.split()[1]))
			dZ = None
			dTmp = locale.str(pRow.GetValue(inputs.sZField))
			dZ = locale.atof(dTmp)
			if dZ < 0.0: raise 1
			if sIDField:
				sID = str(pRow.GetValue(sIDField))
				if (sID in dcID.values()): raise ReportError (msgDuplicateKeys)
				dcID[sKey] = str(sID)
			sKeys.append(sKey)
			dcX[sKey] = dX
			dcY[sKey] = dY
			dcZ[sKey] = dZ
		except:
			if iBadRecCnt < iCutOff:
				try:
					lsBadRecs.append(sKey)
				except:
					sKey = "pos:" + `iRec`
					lsBadRecs.append(sKey)
			iBadRecCnt = iBadRecCnt + 1
			if dZ:
				if dZ < 0.0: raise ReportError(msgNoNegsErr)
			pass
		pRow = pRows.Next()

	# Report any problems encountered reading feature input data.
	if iBadRecCnt:
		sMessage = msgReadErr % (iBadRecCnt, iRec)
		pGP.AddWarning (sMessage)
		pGP.AddWarning(`lsBadRecs`)

	# For contiguity conceptualization, find neighbor polygons
	dcNeighbors = {}
	if inputs.sSpaceConcept.find(sContiguity) >= 0:
		dcNeighbors = build_neighbor_list (inputs)		

	# Compute row sums, if necessary.
	if inputs.sStandardization:
		if bDefault: dcRowSum, dDistAllSum = calculate_rowsums(inputs, dcX, dcY, {}, dcRowSum, sKeys, iTrue, dcNeighbors)
		# Make sure we have at least one neighbor per feature if required.
		validate_standardization(inputs, dcRowSum, dDistAllSum, sKeys, dcID)
	else: dcRowSum = None
			
	return dDistAllSum, bDefault, dcNeighbors

def calculate_GeneralG(inputs):
	dZSum = 0.0
	dZ2Sum = 0.0
	dZ3Sum = 0.0
	dZ4Sum = 0.0 
	lNumObs = len(sKeys)
	if lNumObs < iMinObs:
		raise ReportError (msgNoRecsErr) 
	rN = float(lNumObs)

	for sKey in sKeys:
		dZSum = dZSum + dcZ[sKey]
		dZ2Sum = dZ2Sum + dcZ[sKey]**2.0
		dZ3Sum = dZ3Sum + dcZ[sKey]**3.0
		dZ4Sum = dZ4Sum + dcZ[sKey]**4.0

	# Calculate standard deviation for this data set.
	dZMean = dZSum/rN
	dZVar = ((dZ2Sum/rN) - dZMean**2.0)**0.5
	if not abs(dZVar) > 0.0:
		raise ReportError(msgZeroVarianceErr)

	# Loop for each Z value.
	iNeighborCnt = 0
	dNeighborProductSum = 0.0
	dTotalProductSum = 0.0
	dS1 = 0.0 
	dS2 = 0.0
	dWijSum = 0.0
	dWijWji2Sum = 0.0 
	fInterval = rN / 5.0
	fMore = fInterval
	iComplete = 20
	pGP.AddMessage (sCalculating)
	for i in range(0,lNumObs):
		if i > fInterval: fInterval, iComplete = check_progress(fInterval, fMore, iComplete)
		iKey = sKeys[i]
		dWijRowSum = 0.0 
		for j in range(0, lNumObs):
			jKey = sKeys[j]
			if iKey != jKey:  # i may not equal j
				dTotalProductSum = dTotalProductSum + (dcZ[iKey] * dcZ[jKey])
				# Calculate the weight (dWij)
				if inputs.sSpaceConcept.find(sContiguity) >= 0:
					dWij = 0.0 
					if dcNeighbors.has_key(iKey):
						if jKey in dcNeighbors[iKey]:
							dWij = 1.0
					dWji = dWij
				elif bDefault: # calculate distance between i and j
					dDist = calc_distance (inputs.sDistanceMethod, iKey, jKey, dcX, dcY, {})
					dWij =  conv_to_weight(dDist, inputs.sSpaceConcept, inputs.fBeta, inputs.dDistance, inputs.iOffset)
					dWji = dWij
				else:
					# weights are from user specified file, note: we do not assume
					# symmetry for weights file.  If a weight is missing, the value
					# is set to zero.
					if len(dcID) > 0:
						sKey = dcID[iKey] + ":" + dcID[jKey]
						sKeyR = dcID[jKey] + ":" + dcID[iKey]
					else:
						sKey = iKey + ":" + jKey
						sKeyR = jKey + ":" + iKey
					try:dWij = dcWeight[sKey]
					except KeyError: dWij = 0.0
					try: dWji = dcWeight[sKeyR]
					except KeyError: dWji = 0.0 
				if inputs.sStandardization:
					dWij = standardize_weight (dWij, inputs, dcRowSum, iKey, dcID, dDistAllSum)
					dWji = standardize_weight (dWji, inputs, dcRowSum, jKey, dcID, dDistAllSum)
				dNeighborProductSum = dNeighborProductSum + (dWij * dcZ[iKey] * dcZ[jKey])
				dWijSum = dWijSum + dWij
				dWijWji2Sum = dWijWji2Sum + (dWij + dWji)**2.0
				dWijRowSum = dWijRowSum + (dWij + dWij)
		dS2 = dS2 + dWijRowSum**2.0
	pGP.AddMessage (s100Percent)
	pGP.AddMessage (sDone)
	pGP.AddMessage (" ")
	if not abs(dWijSum) > 0.0: raise ReportError(msgNoPairsErr)

	# Calculate B and S working variables needed to calculate variance.
	dS1 = 0.5 * dWijWji2Sum
	B0 = ((rN**2.0 + (-3.0 * rN) + 3.0) * dS1) - (rN * dS2) + (3.0 * dWijSum**2.0)
	B1 = -1.0 * (((rN**2.0 - rN) * dS1) - (2.0 * rN * dS2) + (6.0 * dWijSum**2.0))
	B2 = -1.0 * ((2.0 * rN * dS1) - ((rN + 3.0) * dS2) + (6.0 * dWijSum**2.0))
	B3 = (4.0 * (rN - 1.0) * dS1) - (2.0 * (rN + 1.0) * dS2) + (8.0 * dWijSum**2.0)
	B4 = dS1 - dS2 + dWijSum**2.0
	
	# Calculate Observed G, Expected G and Z Score.
	dGObs = dNeighborProductSum / dTotalProductSum
	dGExp = dWijSum / (rN * (rN - 1.0))
	dZVar = ( (((B0 * dZ2Sum**2.0) + (B1 * dZ4Sum) + (B2 * dZSum**2.0 * dZ2Sum) +
			   (B3 * dZSum * dZ3Sum) + (B4 * dZSum**4.0)) /
			  ((dZSum**2.0 - dZ2Sum)**2.0 *
			   (rN * (rN - 1.0) * (rN - 2.0) * (rN - 3.0)))) - dGExp**2.0 )
	if abs(dZVar) > 0.0: dZScore = (dGObs - dGExp) / dZVar**0.5
	else:
		sMessage = msgVarianceErr % (sZField)
		raise ReportError (sMessage)
	return dGObs, dGExp, dZVar, dZScore

def output_results():
	"""Display results."""
	sGObs = locale.format("%f", dGObs)
	sZValue = locale.format("%f", dZScore)
	sGExp = locale.format("%f", dGExp)
	sZVar = locale.format("%f", dZVar)
	if inputs.sDisplayIt == "true":
		if "WIN" in sys.platform.upper():
			sCommandLine = (os.path.dirname(sys.argv[0]) + "\\GenGMsg.exe " + sGObs + " " + sZValue)
			os.system(sCommandLine)
		else:
			pGP.AddWarning (msgNoGraphics)
			pass			
		   
	sObsGenG = sOGenG + sGObs
	sExpGenG = sEGenG + sGExp
	sVariance = sGenGVar + sZVar
	sZScoreResult = sZScore + sZValue + sStandardDeviations
	pGP.AddMessage(sObsGenG)
	pGP.AddMessage(sExpGenG)
	pGP.AddMessage(sVariance)
	pGP.AddMessage(sZScoreResult)
	return sGObs, sZValue
	
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#MAIN

if __name__ == "__main__":
	"""This tool calculates the General G spatial autocorrelation
	statistic."""
	
	#Get input arguments, construct an "inputs" object	
	sFile = sys.argv[11].strip()
	output_f = open( sFile, "w" )
	output_f.write ( "Feature Class Name, Observed General G, Expect General G, General G Variance, Z Score\n" )
	
	#Get input arguments, construct an "inputs" object	
	for inputs in get_inputs():
		iNumRecs = pGP.GetCount(inputs.sInputFC)
		if iNumRecs < 30:
			pGP.AddWarning (msgFewRecsWrn)	 

		#Get and check feature class information: fields, shapefile, etc.
		properties = get_featureclass_properties(inputs.sInputFC)
		check_field_properties(inputs, properties)
		check_numeric_properties(inputs)

		# Get X, Y and Z values.
		sKeys = []
		dcX = {}
		dcY = {}
		dcZ = {}
		dcID = {}
		dcRowSum = {}
		dcWeight = {}
		dDistAllSum, bDefault, dcNeighbors = build_value_lists(dcWeight, dcRowSum)

		#Calculate the stats.
		dGObs, dGExp, dZVar, dZScore = calculate_GeneralG(inputs)
		
		#Create output feature class.
		sGObs, sZValue = output_results()
		
		output_f.write( "%s, %f, %f, %f, %f\n" % (inputs.sInputFC, dGObs, dGExp, dZVar, dZScore) )
		
		#Wrap it up (clean up temp files, set derived output values).
		try:
			pGP.SetParameterAsText (8,sGObs)
			pGP.SetParameterAsText (9,sZValue)
		except:
			pGP.AddWarning(msgDerivedOutputErr)
			pass
	pGP = None
#==========================================================================
