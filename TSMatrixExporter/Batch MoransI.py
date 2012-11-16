#--------------------------------------------------------------------------
# Tool Name:  Spatial Autocorrelation (Moran's I)
# Source Name: MoranI.py
# Version: ArcGIS 9.2
# Author: ESRI
#
# This tool calculates Global Moran's I (a measure
# of spatial autocorrelation).
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
#Moran's I Tool Functions 
#   get_inputs -		parses sys.argv and returns an object of class gen
#					   that contains each user specified input argument.
#
#   build_value_lists - constructs list structures for X, Y and Z.
#					   Returns an object containing these value lists.
#
#   calculate_MoransI - calculate Moran's Index and Z Score.
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
	ret_list = []
	try:
		for sInputFC in sInputFCs.split(';'):
			print "Cacluating %s ..." % sInputFC
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
	
	dSumZ = 0.0
	dZ2Sum = 0.0
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
			dTmp = locale.str(pRow.GetValue(inputs.sZField))
			dZ = locale.atof(dTmp)
			if sIDField:
				sID = str(pRow.GetValue(sIDField))
				if (sID in dcID.values()): raise ReportError (msgDuplicateKeys)
				dcID[sKey] = str(sID)
			dcX[sKey] = dX
			dcY[sKey] = dY
			dcZ[sKey] = dZ
			sKeys.append(sKey)
			dSumZ = dSumZ + dZ
			dZ2Sum = dZ2Sum + dZ**2.0
		except:
			if iBadRecCnt < iCutOff:
				try:
					lsBadRecs.append(sKey)
				except:
					sKey = "pos:" + `iRec`
					lsBadRecs.append(sKey)
			iBadRecCnt = iBadRecCnt + 1
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
		if bDefault: dcRowSum, dDistAllSum = calculate_rowsums(inputs,dcX,dcY,{},dcRowSum, sKeys, iTrue, dcNeighbors)
		# Make sure we have at least one neighbor per feature if required.
		#validate_standardization(inputs, dcRowSum, dDistAllSum, sKeys, dcID)
	else: dcRowSum = None
	
	return dDistAllSum, dSumZ, dZ2Sum, bDefault, dcNeighbors

def calculate_MoransI():
	"""Calculate Moran's Index and Z Score."""
	dSumWC = 0.0		# summation of weighted co-variance (dWij * dCij)
	dSumW = 0.0		 # summation of all weights (dWij)
	dM2 = 0.0		   
	dM4 = 0.0	   
	dSumS1 = 0.0
	dSumS2 = 0.0
	lNumObs = len(dcZ.keys())
	if lNumObs < iMinObs:
		raise ReportError (msgNoRecsErr) 

	# Calculate sample mean.
	rN = lNumObs * 1.0
	dZMean = dSumZ/rN
	dZVar = ((dZ2Sum/rN) - dZMean**2.0)**0.5
	if not abs(dZVar) > 0.0:
		raise ReportError(msgZeroVarianceErr)

	# Begin calculating Moran's I
	fInterval = rN / 5.0
	fMore = fInterval
	iComplete = 20
	pGP.AddMessage (sCalculating)
	for i in range (0, lNumObs):
		dWijS2Sum = 0.0
		dWjiS2Sum = 0.0 
		iKey = sKeys[i]
		dZiDeviation = dcZ[iKey] - dZMean	 # Calculate deviation from mean
		dM2 = dM2 + dZiDeviation**2.0
		dM4 = dM4 + dZiDeviation**4.0
		if i > fInterval: fInterval, iComplete = check_progress(fInterval, fMore, iComplete)
		# Look for i's local neighbors
		for j in range(0,lNumObs):
			if i <> j:
				jKey = sKeys[j]
				dZjDeviation = dcZ[jKey] - dZMean
				dCij = dZiDeviation * dZjDeviation  # Calculate ij co-variance
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
					try: dWij = dcWeight[sKey]
					except KeyError: dWij = 0.0
					try: dWji = dcWeight[sKeyR]
					except KeyError: dWji = 0.0
				if inputs.sStandardization:
					dWij = standardize_weight (dWij, inputs, dcRowSum, iKey, dcID, dDistAllSum)
					dWji = standardize_weight (dWji, inputs, dcRowSum, jKey, dcID, dDistAllSum)
					
				# Create sums needed to calculate Moran's I
				dSumWC = dSumWC + (dWij * dCij)
				dSumW = dSumW + dWij
				dWijS2Sum = dWijS2Sum + dWij
				dWjiS2Sum = dWjiS2Sum + dWji
				dSumS1 = dSumS1 + (dWij + dWji)**2.0
		dSumS2 = dSumS2 + ((dWijS2Sum + dWjiS2Sum)**2.0)
	dSumS1 = 0.5 * dSumS1
	pGP.AddMessage (s100Percent)
	pGP.AddMessage (sDone)
	pGP.AddMessage (" ")

	# we need a few more working variables:
	dM2 = (dM2 * 1.0) / rN					   # standard deviation 
	dM4 = (dM4 * 1.0) / rN  

	dB2 = dM4/(dM2**2.0)						 # sample kurtosis
	dExpected = -1.0 / (rN - 1.0)				# Expected Moran's I

	# Finally, we can calculate Moran's I and its significance (Z Score).
	# This Z Score is based on the calculated RANDOMIZATION null hypothesis.
	if not dSumW > 0.0:
		raise ReportError(msgNoWts)
	
	dMoranI = dSumWC / (dM2 * dSumW)

	dDiv = ((rN-1.0)*(rN-2.0)*(rN-3.0)*(dSumW**2.0))
	dTmp1 = rN*((rN**2.0-(3.0*rN)+3.0)*dSumS1-(rN*dSumS2)+3.0*(dSumW**2.0))
	dTmp2 = dB2*((rN**2.0-rN)*dSumS1-(2.0*rN*dSumS2)+6.0*(dSumW**2.0))
	
	rVariance = abs((dTmp1/dDiv) - (dTmp2/dDiv) - (dExpected**2.0))
	dMoranZScore = (dMoranI - dExpected) / (rVariance**0.5)

	return dMoranI, dExpected, rVariance, dMoranZScore

def output_results():
	"""Display results."""
	sMoranI = locale.format("%f", dMoranI)
	sZValue = locale.format("%f", dMoranZScore)
	sExpected = locale.format("%f", dExpected)
	sVar = locale.format("%f", rVariance)
	if inputs.sDisplayIt == "true":
		if "WIN" in sys.platform.upper():
			sCommandLine = (os.path.dirname(sys.argv[0]) + "\\MoranMsg.exe " + sMoranI + " " + sZValue)
			os.system(sCommandLine)
		else:
			pGP.AddWarning (msgNoGraphics)
			pass
	sIndexResult = sMoransIndex + sMoranI
	sExpResult = sExpectedIndex + sExpected
	sVarResult = sVariance + sVar
	sZScoreResult = sZScore + sZValue
	pGP.AddMessage(sIndexResult)
	pGP.AddMessage (sExpResult)
	pGP.AddMessage (sVarResult)
	pGP.AddMessage(sZScoreResult)
	pGP.AddMessage ("  ")
	return 1
	
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#MAIN

if __name__ == "__main__":
	"""This tool calculates Global Moran's I (a measure of spatial
	autocorrelation)."""
	
	sFile = sys.argv[11].strip()
	output_f = open( sFile, "w" )
	output_f.write ( "feature class name, Moran's Index, Expect Index, Variance, Z Score\n" )
	
	#Get input arguments, construct an "inputs" object	
	for inputs in get_inputs():
		iNumRecs = pGP.GetCount(inputs.sInputFC)
		if iNumRecs < 30:
			pGP.AddWarning (msgFewRecsWrn)	   

		#Get and check feature class information: fields, shapefile, etc.
		properties = get_featureclass_properties(inputs.sInputFC)
		inputs = check_field_properties(inputs, properties)
		check_numeric_properties(inputs)

		# Get X, Y and Z values.
		sKeys = []
		dcX = {}
		dcY = {}
		dcZ = {}
		dcID = {}
		dcRowSum = {}
		dcWeight = {}
		dDistAllSum, dSumZ, dZ2Sum, bDefault, dcNeighbors = build_value_lists(dcWeight, dcRowSum)

		#Calculate stats.
		dMoranI, dExpected, rVariance, dMoranZScore = calculate_MoransI()
		
		#Create output feature class.
		output_results()
		
		output_f.write( "%s, %f, %f, %f, %f\n" % (inputs.sInputFC, dMoranI, dExpected, rVariance, dMoranZScore) )
		#Set derived output parameters.
		try:
			pGP.SetParameterAsText (8,dMoranI)
			pGP.SetParameterAsText (9,dMoranZScore)
		except:
			pGP.AddWarning (msgDerivedOutputErr)
			pass
	pGP = None
	output_f.close()
#==========================================================================
