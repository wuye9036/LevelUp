#--------------------------------------------------------------------------
# Source Name: HelperFunctions.py
# Version: ArcGIS 9.2
# Author: ESRI
#
# This module contains Python functions and custom classes used by all of the
# sample spatial statistic tools.  
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Imports and Constants
#--------------------------------------------------------------------------
import sys, math, os, locale, random, tempfile, arcgisscripting

sCountField = "ICOUNT"
sLinkField = "LINK2COUNT"
sResultsField = "SCORE"
sAreaField = "F_AREA"
sTmpResults = "tmpRxx.txt"
sTmpPntFC = "tmpPnts.shp"
sTmpTable = "tmpTbl.dbf"
sTmpLineFC = "tmpLines.shp"
sTmpFreq = "tmp_freq.dbf"
sLeftFidField = "left_fid"
sRightFidField = "right_fid"
sFrequencyFields = "LEFT_FID;RIGHT_FID"
sDelimiter = ";"
iCutOff = 100
iTrue = 1
iFalse = 0
iMinObs = 3
iSimulationCnt = 9

#Define message constants so they may be easily translated.
""" Strings """
sInvDist2 = "Inverse Distance Squared"
sInverse = "Inverse"
sNone = "None"
sFromFile = "From File"
sFixedDst = "Fixed Distance"
sIndifference = "Indifference"
sContiguity = "Contiguity"
sRow = "Row"
sGlobal = "Global"
sTrue = "true"
sFalse = "false"
sAll = "All"
sStandardDeviations = " Standard Deviations"
sManhattanDst = "Manhattan Distance"
sUserSA = "User provided Study Area Feature Class"
sMinRec = "Minimum Enclosing Rectangle"
sExiting = "Exiting..."

""" Error/Warning Messages """
msgTooManyNeighbors = "Number of neighbors specified (%i) is greater than or equal to the number of features in the feature class (%i). \nPlease choose a smaller number of neighbors and try again\n"
msgNegativeNeighbors = "Zero and Negative numbers are not valid for the 'Number of Neighbors' parameter\n"
msgMinDist = "The minimum %i neighbor distance is %f"
msgAvgDist = "The average %i neighbor distance is %f"
msgMaxDist = "The maximum %i neighbor distance is %f\n"
msgUnits = "The units are in the units of the feature class spatial reference\n"
msgParseErr = "Cannot parse input arguments."
msgInputsErr = "Cannot construct INPUTS object; invalid arguments."
msgErrorCreatingPoint = "Error creating point."
msgReadErr = "Problems reading %s records of %s: "
msgNoRecsErr = "Too few records for analysis"
msgFewRecsWrn = "Warning: ideally you will have a minimum of 30 input features for analysis."
msgSomeNoNeighbors = "Warning: some features have no neighbors and will be excluded from the analysis."
msgNoWts = "No valid weights found... exiting."
msgNoDims = "The dimension field you specified does not contain valid values... exiting."
msgNothingLeft2Analyze = "No features left in reduced analysis area..."
msgNoNeighborsErr = "Sum of distances from each to every other feature is zero... exiting to avoid zero divide."
msgDerivedOutputErr = "Cannot set derived output."
msgOverwriteErr = "Cannot overwrite: %s"
msgTmpFileErr = "Error creating temp file."
msgTmpFileWriteErr = "Error writing to temp file."
msgOverwriteFldWrn = "Overwriting values in output for field: %s"
msgVarianceErr = "The variance for %s is zero... exiting."
msgZeroVarianceErr = "Zero variance:  This tool is designed to work with weighted point data.  For incident data, consider using the Collect Events utility to create weighted data.  Alternatively, select a field with a broader range of values."
msgZeroDivideErr = "Standard error or expected mean distance is zero; check input data ... exiting."
msgNoPairsErr = "No features pairs encountered... exiting."
msgWtConvertWrn = "Weights of zero interpreted as 1.0 to avoid divide by zero."
msgNullWeights = "Null weights encountered... these were interpreted as zero for processing."
msgNullSelfPot = "Null values for Self Potential encountered... these were treated as zero for processing."
msgTooFewErr = "Too few points/records for case %s, skipping..."
msgNoLenWrn = "No length (first point matches last point) for %s of %s features. "
msgExcludedWrn = "These features were excluded from analysis."
msgLineOnlyErr = "This tool only makes sense for line or polyline features... exiting."
msgPolyOnlyErr = "This tool was designed to work with Polygon Feature Classes... exiting."
msgPolyConceptOnly = "The Polygon Contiguity concept is only appropriate for Polygon input... exiting."
msgNoNegsErr = "The General G statistic was designed to work with positive attribute values.  Exiting..."
msgMultiPntWrn = "WARNING: Only the first part of the multipoint feature will be processed."
msgNotProjWrn = "The input feature class does not appear to contain projected data."
msgDstCalcWrn = "WARNING: Distance calculations may not be accurate for unprojected data."
msgGetPropErr = "Cannot retrieve feature class properties"
msgNoExtent = "Cannot retrieve feature class extent -- likely either the environment extent is invalid or there are no features in (or selected in) the input feature class."
msgPropObjErr = "Cannot construct PROPERTIES object"
msgWtsMatrixErr = "Errors processing user specified weights matrix... exiting."
msgDstCalcErr = "Error calculating distance."
msgMissingCaseErr = "Specified case field, %s, not found in %s"
msgMissingWtErr = "Specified weight field, %s, not found in %s"
msgWtTypeErr = "Weight field, %s, must be numeric... it is: %s."
msgMissingDimErr = "Specified dimension field, %s, not found in %s"
msgDimTypeErr = "Dimension field, %s, must be numeric... it is: %s."
msgMissingFldErr = "Specified analysis field, %s, not found in %s"
msgFldTypeErr = "Analysis field, %s, must be numeric... it is: %s."
msgExpectedNumericFields = "Analysis fields must be numeric... exiting."
msgInvalidFields = "Cannot find specified K function results fields... exiting"
msgMissingSelfErr = "Specified self potential field, %s, not found in %s"
msgSelfTypeErr = "Self potential field, %s, must be numeric... it is: %s."
msgIgnoringWtsWrn = "WARNING: Weights file information is ignored for the inverse, fixed distance, and indifference methods."
msgIgnoringStyAreaWrn = "WARNING: Study area feature class is ignored for minimum enclosing rectangle study area method."
msgIgnoringDstWrn = "WARNING: The distance band/threshold value is ignored for the Polygon Contiguity method."
msgMissingDstErr = "A non-Zero distance band is required for the fixed distance method... exiting."
msgDstBandTooBig = "Distance band must be smaller than feature class extent."
msgMissingThrshErr = "Non-zero threshold distance is required for the Zone of Indifference method."
msgMissingWMatrixErr = "You must provide a pathname to your Weights Matrix File or select a different conceptualization for Spatial Relationships."
msgMissingSAParam = "You must provide a pathname to a polygon study area or select a different study area method.  Exiting..."
msgAreaErr = "Feature Class AREA must be greater than 0... exiting."
msgAreaWarn = "Warning: AREA value and/or extent is zero... inappropriate use of this tool"
msgDstRadiusErr = "Distance radius must be greater than 0."
msgDstBandErr = "Distance Band cannot be less than zero... exiting."
msgSuggestions = ('Try increasing distance band (large enough so that every feature centroid has at least one "neighbor"), ' +
				  'or use a different conceptualization of spatial relationships ' +
				  '(like inverse distance or zone of indifference.), ' +
				  'or run without row standardization.')
msgLrgBegDist = "The beginning distance value you specified is larger than expected... please check that this value is reasonable."
msgLrgDstBands = ('The number of distance bands with the distance increment value you specified ' +
				  'may produce some large distance bands encompassing all or most of the features ' +
				  'in your study area... please check that these values are reasonable.')
msgInvalidStudyArea = ('The study area specified either is not a Polygon Feature class or it contains more than ' +
					   'one polygon feature. This tools expects a single polygon study area feature class.  ' +
					   'Exiting...')
msgCheckWMatrix = "Try checking weights matrix; make sure all features have at least one entry."
msgNeedNeighborsErr = "Found at least one feature with no neighboring features... exiting"
msgIDMismatchErr = "ID mismatch... check ID values in weights file against table ID values."
msgFileFormatErr = ("Invalid weights file format.  First record must be the name of the ID field.  " +
					"Each record following the header record should be formatted: FROM TO WEIGHT")
msgDoNotUseFID = ("You cannot use the FID field for your unique ID field with this tool.  " +
				  "You can create an ID field using AddField and set the values equal to " +
				  "the FID using the CalculateField tool, however.")
msgDuplicateKeys = "Duplicate ID keys encountered. Please use an ID field with Unique values.  Skipping duplicates."
msgNegSelfPot = "Warning: Negative Self Potential values have been interpreted as zero for processing."
msgNegWeights = "Warning: Negative Weight values have been interpreted as zero for processing."
msgNegativeWts = "Warning: Your spatial weigths matrix contains negative weights... are you SURE this is correct?"
msgNoGraphics = "Graphics only display on Windows Operating Systems."
										
""" Progress Messages """
sConstructingGrid = "Constructing a geographic grid..."
sClippingGrid = "Clipping a geographic grid..."
sBuildingLists = "Building Lists..."
sComputingWeights = "Computing Weights..."
sComplete = "% complete"
s100Percent = "				  100% complete"
sCalculating = "Calculating results..."
sCalculatingConfEnv = "Computing Confidence Envelope..."
sDone = "Calculations complete..."
sReadingWeightsFile = "Reading weights file..."
sLOTSofWeights = "Reading weights for %s features (potentially %s weights/records)"
sWtsSoFar = " weights read so far..."
sWritingResults = "Writing results..."

""" Results Messages """
sMoransIndex = "Moran's Index = "
sExpectedIndex = "Expected Index = "
sVariance = "Variance = "
sZScore = "Z Score = "
sNNMeanDst = "Nearest Neighbor Observed Mean Distance = "
sExpectedNNMeanDst = "Expected Mean Distance = "
sNNRatio = "Nearest Neighbor Ratio = "
sOGenG = "Observed General G = "
sEGenG = "Expected General G = "
sGenGVar = "General G Variance = "

#Create a global Geoprocessing Dispatch Object
try:
	if pGP:
		pass
except:
	try:
		pGP = arcgisscripting.create()
	except: raise ReportError ("Error creating the geoprocessing object.")

#Set the locale.
locale.setlocale(locale.LC_ALL, "")

#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Custom Exceptions
#	See http://www.python.org/doc/current/tut/node10.html for more
#	information about custom exceptions
#--------------------------------------------------------------------------
class ReportError(Exception):
	"""Send an error message to the application history window."""
	def __init__(self, message):
		self.message = message
	def __str__(self):
		pGP.AddError(self.message)
		return repr(self.message)
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Custom Classes
#--------------------------------------------------------------------------
class Gen:
	"""A generic object."""
	def __init__(self):
		pass
	def add(self, name, value):
		self.__dict__[name] =  value
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Return Functions -- Functions that return information
#   get_featureclass_properties - queries a featureclass and returns a
#		properties object with info about fields, spatial reference, etc.
#
#   calc_distance - calculates the distance between two locations based on
#		   distance measurement method specified and self-potential info,
#		   if any.
#
#   read_user_weights - reads FROM, TO, WEIGT ascii text file.
#
#   conv_to_weight - converts a distance to a weight based on specified
#		   conceptualization of spatial relationships.
#
#   standardize_weight - converts a wieght to a row or globally
#		   standardized weight.
#
#   calculate_rowsums - constructs a dictionary of rowsums.
#
#   conv_to_radians - converts degrees to radians
#   
#--------------------------------------------------------------------------
def get_featureclass_properties(aFeatureClass):
	"""Returns field and spatial reference information for aFeatureClass"""
	global dTolerance

	try:
		pFCInfo = pGP.describe(aFeatureClass)
		pSpatialRef = pFCInfo.SpatialReference  # Get spatial reference object
		sFID = pFCInfo.OIDFieldName
		sShapeType = pFCInfo.ShapeType.lower()
		if sShapeType == "multipoint":
			pGP.AddWarning (msgMultiPntWrn)
		if pSpatialRef.Type != "Projected":
			pGP.AddWarning(msgNotProjWrn)
		bHasZ = pFCInfo.HasZ
		try:
			#lsEnvelope = map((lambda x: locale.atof(x)),(pFCInfo.Extent).split())
			lsEnvelopeRaw = (pFCInfo.Extent).split()
			lsEnvelope = map((lambda x: locale.atof(str(x))), lsEnvelopeRaw)
			d1 = abs(lsEnvelope[3] - lsEnvelope[1])
			d2 = abs(lsEnvelope[2] - lsEnvelope[0])
			dMaxExtent = max(d1, d2)
			dShortExtent = min(d1, d2)
			dExtArea = d1 * d2
			dTolerance = (dMaxExtent + dShortExtent) * math.exp(-10.0)
		except:
			lsEnvelope = None
			dMaxExtent = 0.0
			dShortExtent = 0.0
			dExtArea = 0.0
			dTolerance = 0.0
		
		pFields = pGP.ListFields(aFeatureClass)
		dcFields = {}
		pField = pFields.Next()
		while pField:						   # Collect field names and types
			sName = (pField.Name).upper()
			sType = pField.Type
			dcFields[sName] = sType
			if sType == "Geometry": sShapeField = sName
			pField = pFields.Next()

	# Make a generic object containing feature class properties.
		try:
			obj = Gen()
			obj.add('dcFields', dcFields)
			obj.add('sShapeField', sShapeField)
			obj.add('pSpatialRef', pSpatialRef)
			obj.add('lsEnvelope', lsEnvelope)
			obj.add('dMaxExtent', dMaxExtent)
			obj.add('dExtArea', dExtArea)
			obj.add('dShortExtent', dShortExtent)
			obj.add('sFID', sFID)
			obj.add('sShapeType', sShapeType)
			obj.add('bHasZ', bHasZ)
		except:
			raise "CaughtError", msgPropObjErr
		
	except "CaughtError", ErrorMsg:
		raise ReportError(ErrorMsg + "\n" + sExiting)
	except:
		raise ReportError (msgGetPropErr + "\n" + sExiting)
	
	return obj

def read_user_weights (properties, sWeights, dcWeight, dcRowSum, dDistAllSum, bExcludeII):
	""" Reads FROM, TO, WEIGHT file into dictionary structure.
		Header recorder must identify ID field.  """
	try:
		bDefault = iFalse
		f = open(sWeights, 'r')
		# Make sure we have a valid ID field.
		sFieldName = f.readline().strip()
		if sFieldName.upper() == (properties.sFID).upper():
			sIDField = None
			sTokens = f.readline().split()
		else:
			sPathName = os.path.dirname(sWeights)
			sIDField = pGP.ValidateFieldName(sFieldName, sPathName)
			if not sIDField.upper() in properties.dcFields.keys():
				# Maybe we didn't get a header record
				try:
					sTokens = sFieldName.split()
					# If we have two integers and a weight, we'll assume the
					# ID field is the FID field
					id1 = int(sTokens[0])
					id2 = int(sTokens[1])
					dWt = locale.atof(sTokens[2])
					sIDField = None
				except:
					raise ReportError(msgFileFormatErr)
			else:
				sTokens = f.readline().split()
		pGP.AddMessage (sReadingWeightsFile)
		
		# Read each record in weights file, creating a dictionary structure of distances.
		bNegWts = iFalse
		while len(sTokens) > 0:
			sFrom = sTokens[0]
			sTo = sTokens[1]
			dWeight = locale.atof(sTokens[2])
			if dWeight < 0.0: bNegWts = iTrue
			sKey = sFrom + ":" + sTo
			dcWeight[sKey] = dWeight
			if not (sFrom == sTo and bExcludeII):
				if (dcRowSum.has_key(sFrom)):
					dcRowSum[sFrom] = dcRowSum[sFrom] + dWeight
				else:
					dcRowSum[sFrom] = dWeight
				dDistAllSum = dDistAllSum + dWeight
			sTokens = f.readline().split()
		f.close()
		if bNegWts: pGP.AddWarning(msgNegativeWts)
	except:   # If we encounter unexpected errors, we bail
		bDefault = iTrue
		sIDField = None
		f.close()
		raise ReportError(msgWtsMatrixErr)
	return bDefault, sIDField, dcRowSum, dDistAllSum

def calc_distance (sMethod, i, j, x, y, dcSelf):
	""" Calculates distance"""
	try:
		if i == j:
			if len(dcSelf) > 0: dDist = dcSelf[i]
			else: dDist = 0.0 
		else:
			if sMethod == sManhattanDst:
				dDist = abs(x[j] - x[i]) + abs(y[j] - y[i])
			else:  # Euclidean distance
				dDist = ((x[j] - x[i])**2.0 + (y[j] - y[i])**2.0)**0.5
	except: raise ReportError (msgDstCalcErr)
	return dDist

def conv_to_weight (dDist, sSpaceConcept, fBeta, dDistance, iOffset):
	""" Converts a distance to a weight based on user specified concept of 
	spatial relationships and threshold distance (if any)."""
	if sSpaceConcept.find(sInverse) >= 0:
		dDist = dDist + iOffset
		dDistance = dDistance + iOffset
		if dDist > 0.0: dWeight = 1.0 / dDist**fBeta
		else: dWeight = 0.0 
	elif sSpaceConcept.find(sFixedDst) >= 0:
		if dDist <= dDistance: dWeight = 1.0
		else: dWeight = 0.0
	elif sSpaceConcept.find(sIndifference) >= 0:
		if dDist > dDistance: dWeight = (1.0 / (dDist - dDistance))
		else: dWeight = 1.0 
	else: dWeight = dDist
	if not (sSpaceConcept.find(sIndifference) >= 0 or
			sSpaceConcept.find(sFixedDst) >= 0):
		if dDistance > 0.0:
			if dDist > dDistance: dWeight = 0.0 
	return dWeight		

def standardize_weight (dWeight, inputs, dRowSum, sKey, dcID, dDistAllSum):
	""" Applies either row or global standardization to the passed weight."""
	if inputs.sStandardization == sRow:
		if len(dcID) > 0: sKey = dcID[sKey]
		try:
			dStdWt = (dWeight / dRowSum[sKey])
		except:
			dStdWt = 0.0
	elif inputs.sStandardization == sGlobal:
		dStdWt = (dWeight / dDistAllSum)
	else: dStdWt = dWeight
	return dStdWt

def calculate_rowsums(inputs, dcX, dcY, dcSelf, dcRowSum, sKeys, bExcludeII, dcNeighbors):
	"""Sum the weights for each row if required for standardization."""
	pGP.AddMessage(sComputingWeights)
	lNumObs = len(sKeys)
	rN = float(lNumObs)
	fInterval = (((rN * rN) / 2.0)/ 5.0) + 2.0   # to track progress
	fMore = fInterval
	iComplete = 20
	iCnt = 0
	dDistAllSum = 0.0
	for i in range (0, lNumObs):	  # Loop for each row
		for j in range (i, lNumObs):  # Assume symmetry (dij = dji)
			if not(i == j and bExcludeII):
				iCnt = iCnt + 1
				iFrom = sKeys[i]
				jTo = sKeys[j]
				if inputs.sSpaceConcept.find(sContiguity) >= 0:
					if jTo in dcNeighbors[iFrom]:
						dWeight = 1.0
					else:
						dWeight = 0.0
				else:
					# calculate distance between i and j
					dDist = calc_distance (inputs.sDistanceMethod, iFrom, jTo, dcX, dcY, dcSelf)
					dWeight =  conv_to_weight(dDist, inputs.sSpaceConcept, inputs.fBeta, inputs.dDistance, inputs.iOffset)
				# Keep track of row sum.
				if (dcRowSum.has_key(iFrom)):
					dcRowSum[iFrom] = dcRowSum[iFrom] + dWeight
				else:
					dcRowSum[iFrom] = dWeight
				# Compute Global Sum
				dDistAllSum = dDistAllSum + dWeight		 
				if i <> j:
					if (dcRowSum.has_key(jTo)):
						dcRowSum[jTo] = dcRowSum[jTo] + dWeight
					else:
						dcRowSum[jTo] = dWeight
					dDistAllSum = dDistAllSum + dWeight
				# Report progress
				if iCnt > fInterval:
					fInterval, iComplete = check_progress(fInterval, fMore, iComplete)
	pGP.AddMessage (s100Percent)
	pGP.AddMessage(" ")
	return dcRowSum, dDistAllSum
			
def conv_to_radians (dDegrees):
	""" Converts degrees to radians. """
	return math.pi/180.0*dDegrees

def construct_convex_hull(sKeys, dcX, dcY):
	""" Construct a convex hull around points in a list."""
	# Algorithm to create a convex hull adapted from Python Recipes, author: Dinu C. Gherman.
	pPnts = []
	for iKey in sKeys:
		p = (dcX[iKey], dcY[iKey])
		if not (p in pPnts): pPnts.append(p)
	if len(pPnts) < 3: return pPnts  # we need at least 3 non-coincident points to create a convex hull

	# Build upper half of hull.					
	pPnts.sort()
	pUpper = [pPnts[0], pPnts[1]]
	for p in pPnts[2:]:
		pUpper.append(p)
		while len(pUpper) > 2 and not right_turn(pUpper[-3:]):
			del pUpper[-2]

	# Build lower half of hull.
	pPnts.reverse()
	pLower = [pPnts[0], pPnts[1]]
	for p in pPnts[2:]:
		pLower.append(p)
		while len(pLower) > 2 and not right_turn(pLower[-3:]):
			del pLower[-2]

	# Remove duplicate.
	del pLower[0]
	return (pUpper + pLower)

def right_turn((p, q, r)):
	# Do the vectors pq:qr form a right turn or not?
	# The sign (+ or -) determines the side, right or left, on which the
	# point r lies when measured against a directed vector from p to q.
	# Sarrus' rule is used to calculate the determinant.
	# This code was adapted from Python Recipes, author: Dinu C. Gherman
	dSum1 = q[0]*r[1] + p[0]*q[1] + r[0]*p[1]
	dSum2 = q[0]*p[1] + r[0]*q[1] + p[0]*r[1]
	if ((dTolerance > 0.0) and (abs(dSum1 - dSum2) < dTolerance)):
		return 2
	elif (dSum1 - dSum2) < 0:
		return 1
	else:
		return 0

def point_in_hull (r, pPoly):
	""" Determine if a given point, r, is within a given convex hull polygon, pPoly.
		We require pPoly to be a list of perimeter points in clockwise order
		and that the first and last point are the same (closing the hull). """
	for i in range(0, len(pPoly[:-1])):
		p, q = pPoly[i], pPoly[i+1]
		if not right_turn((p, q, r)):
			return 0  # point r is outside convex hull
	return 1  # point r is INSIDE convex hull

def point_in_poly (r, pPoly):
	"""Determine if a given point, r, is within a given polygon, pPoly using the
	crossings method.  We require pPoly to be a list of perimeter polygon points
	in clockwise order and that the first and last point are the same (closing
	the polygon).  This function will also handle a multi-part polygon where additional
	parts represent "holes"."""
	iCross = 0
	pPartStart = pPoly[0]
	bSkip = iFalse					   # we don't want to skip the first edge
	for i in range(0, len(pPoly[:-1])):
		p, q = pPoly[i], pPoly[i+1]
		if bSkip and (p == pPartStart):  # found transition from one part to another...skip
			pPartStart = q
			bSkip = iFalse
		else:
			# If point is on the pq line, it is inside
			if (right_turn((p, q, r)) == 2):
				return iTrue

			# Count crossings
			if ((p[1] > r[1]) and (q[1] <= r[1]) or	 
				(q[1] > r[1]) and (p[1] <= r[1])):
				# edge straddles horizonal line, see if edge is left or right of r
				x = p[0] + (((r[1] - p[1]) * (q[0] - p[0])) / (q[1] - p[1]))
				if x > r[0]:
					iCross = iCross + 1
			bSkip = iTrue

	if (int(iCross / 2) * 2) == iCross:
		return iFalse		 # point r is outside pPoly
	else:
		return iTrue		  # point r is inside pPoly

def minimum_enclosing_rectangle (pSA, properties):
	# Find Minimum Enclosing Rectangle
	if len(pSA) < 3: return []
	dArea = properties.dExtArea + 1.0
	dXprev = pSA[0][0]
	dYprev = pSA[0][1]
	dXorig = pSA[0][0]
	dYorig = pSA[0][1]
	
	for p in pSA[1:]:
		dX = p[0]
		dY = p[1]

		dX0 = dX - dXprev
		dY0 = dY - dYprev
		dXprev = dX
		dYprev = dY

		d0len = math.sqrt((dX0 * dX0) + (dY0 * dY0))
		dX0 = dX0 / d0len
		dY0 = dY0 / d0len

		dX1 = -1.0 * dY0
		dY1 = dX0

		dsmin = 0.0
		dsmax = 0.0
		dtmin = 0.0
		dtmax = 0.0
		
		for p2 in pSA[2:]:
			dPntX = p2[0]
			dPntY = p2[1]

			dDiffX = dPntX - dXorig
			dDiffY = dPntY - dYorig
			dsProd = (dX0 * dDiffX) + (dY0 * dDiffY)
			dsmin = min(dsmin, dsProd)
			dsmax = max(dsmax, dsProd)

			dtProd = (dX1 * dDiffX) + (dY1 * dDiffY)
			dtmin = min(dtmin,dtProd)
			dtmax = max(dtmax, dtProd)

			dslen = dsmax - dsmin
			dtlen = dtmax - dtmin
			dst = dslen * dtlen

		if (dst < dArea):
			dArea = dst
			dLen0 = dslen
			dLen1 = dtlen
			dDir0X = dX0
			dDir0Y = dY0
			dDir1X = dX1
			dDir1Y = dY1

			dCenterX = dXorig + 0.5 * (dsmin + dsmax) * dX0 + 0.5 * (dtmin + dtmax) * dX1
			dCenterY = dYorig + 0.5 * (dsmin + dsmax) * dY0 + 0.5 * (dtmin + dtmax) * dY1
				
	deX0 = 0.5 * dLen0 * dDir0X
	deY0 = 0.5 * dLen0 * dDir0Y
	deX1 = 0.5 * dLen1 * dDir1X
	deY1 = 0.5 * dLen1 * dDir1Y

	pX0 = dCenterX - deX0 - deX1
	pY0 = dCenterY - deY0 - deY1
	pX1 = dCenterX + deX0 - deX1
	pY1 = dCenterY + deY0 - deY1
	pX2 = dCenterX + deX0 + deX1
	pY2 = dCenterY + deY0 + deY1
	pX3 = dCenterX - deX0 + deX1
	pY3 = dCenterY - deY0 + deY1

	pRectangle = [(pX3, pY3), (pX2, pY2), (pX1, pY1), (pX0, pY0), (pX3, pY3)]

	return pRectangle

def get_random_XY(pStudyArea, properties, sKeys, dcX, dcY):
	""" Get random coordinates within the study area. """
	# Get study area extent
	dMinX = properties.lsEnvelope[0]
	dMaxX = properties.lsEnvelope[2]
	dMinY = properties.lsEnvelope[1]
	dMaxY = properties.lsEnvelope[3]

	iCnt = 0
	for sKey in sKeys:
		dX = (random.random() * (dMaxX - dMinX)) + dMinX
		dY = (random.random() * (dMaxY - dMinY)) + dMinY
		p = (dX, dY)
		while not point_in_poly(p, pStudyArea):
			iCnt = iCnt + 1
			dX = (random.random() * (dMaxX - dMinX)) + dMinX
			dY = (random.random() * (dMaxY - dMinY)) + dMinY
			p = (dX, dY)

		dcX[sKey] = dX
		dcY[sKey] = dY
		
	return dcX, dcY

def shuffle_Z (dcZ):
	""" Randomly shuffle a set of values."""
	lsKeys = dcZ.keys()
	lsValues = dcZ.values()
	for k in lsKeys:
		iPick = len(lsValues)
		idx = int(iPick * random.random())
		dcZ[k] = lsValues[idx]
		del lsValues[idx]

	return dcZ

def calculate_area(pPoly):
	# function to return the area of a polygon
	dAreaSum = 0.0
	pPartStart = pPoly[0]
	bSkip = iFalse
	
	for i in range(0, len(pPoly[:-1])):
		p, q = pPoly[i], pPoly[i+1]
		if bSkip and (p == pPartStart):
			pPartStart = q
			bSkip = iFalse
	   
		else:
			dAreaSum = dAreaSum + ((q[0] * p[1]) - (p[0] * q[1]))
			bSkip = iTrue
	
	dArea = dAreaSum / 2.0

	# This tool requires an AREA value... it won't work on truly linear study areas
	if not (dArea > 0.0): 
		raise ReportError (msgAreaErr)

	return dArea
	
def get_poly_geometry (sStudyAreaPath):
	""" single part only"""
	
	pStudyArea = []
	pRows = pGP.SearchCursor(sStudyAreaPath)
	pRow = pRows.Next()
	pFeat = pRow.shape
	pArray = pFeat.GetPart(0)
	pArray.Reset()
	pPnt = pArray.Next()
	while pPnt:
		pStudyArea.append((pPnt.x, pPnt.y))
		pPnt = pArray.Next()
	return pStudyArea

def build_value_lists(aFeatureClass):
	"""Reads through feature table extracting geometry info.
	   Returns this information in dictionary structures."""
	#pGP.AddMessage ("Building the point list for a feature class...")

	# Initialization of some parameters
	dcX = {}
	dcY = {}
	properties = get_featureclass_properties(aFeatureClass)
	sFieldList = properties.sFID + ";" + properties.sShapeField
	iRec = 0
	lsBadRecs = []
	iBadRecCnt = 0

	# read points from a feature class
	pRows = pGP.SearchCursor(aFeatureClass, "", "", sFieldList)
	pRow = pRows.Next()
	while pRow <> None:
		iRec = iRec + 1
		try:
			sKey = pRow.GetValue(properties.sFID)
			pGeometry = pRow.GetValue (properties.sShapeField)
			sCentroid = pGeometry.TrueCentroid
			dcX[sKey] = locale.atof (str (sCentroid.split()[0]))
			dcY[sKey] = locale.atof (str (sCentroid.split()[1]))
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

	return dcX, dcY

def calc_dist (i, j, x, y, dcSelf):
	""" Calculates distance"""
	try:
		if i == j:
			if len(dcSelf) > 0: dDist = dcSelf[i]
			else: dDist = 0.0 
		else:
			dDist = ((x[j] - x[i])**2.0 + (y[j] - y[i])**2.0)**0.5
	except: raise ReportError (msgDstCalcErr)
	return dDist

def build_neighbor_list (dcX, dcY, dDistLimit):
	""" Collect a list of each feature's neighbors,
		based on a polygon feature class."""
	pGP.AddMessage("Building Neighbor Structure...")

	dcNeighbors = {}
	sKeys = dcX.keys()
	lNumObs = len(sKeys)

	for i in range (0, lNumObs):
		iKey = sKeys[i]
		for j in range (i, lNumObs):
			jKey = sKeys[j]
			if iKey != jKey:
				dDist = calc_dist (iKey, jKey, dcX, dcY, {})

				try:
					lsNeighbors = dcNeighbors[iKey] 
				except:
					lsNeighbors = []
					dcNeighbors[iKey] = lsNeighbors

				if dDist <= dDistLimit:
					lsNeighbors.append(jKey)
					
	return dcNeighbors

def build_point_list_from_neighbors (dcNeighbors, dcX, dcY):

	try:
		# create a point list
		pLinePnts = []
		pLineNds = []
		for iKey, jKeys in dcNeighbors.iteritems():
			lNumObs = len(jKeys)
			for i in range (0, lNumObs):
				jKey = jKeys[i]
				pLineNds.append((iKey, jKey))

				# build a point with iKey
				dX = dcX[iKey]
				dY = dcY[iKey]
				p = (dX, dY)
				pLinePnts.append(p)

				# build a point with jKey
				dX = dcX[jKey]
				dY = dcY[jKey]
				p = (dX, dY)
				pLinePnts.append(p)
	except:
		sErrors = pGP.GetMessages(2)
		raise ReportError (sErrors)

	return pLinePnts, pLineNds  

def read_linguistic_values (sLinguisticValues):
	""" read linguistic values for feature class"""
	pGP.AddMessage("Reading linguistic values from text file...")

	values = {}

	try:
		f = open(sLinguisticValues, 'r')
		# Make sure we have a valid ID field.
		lineno = 0
		for line in f.readlines():
			sTokens = line.replace("\n", "").split(" ")
			values[lineno] = sTokens
			lineno += 1
		f.close()
	except:   # If we encounter unexpected errors, we bail
		raise ReportError(msgWtsMatrixErr)
			
	return values
		   
def nearest_point (pSA, dcX, dcY):
	""" Code to perform NEAR functionality... given a set of points and also points
	defining a study area, this tool returns for each point the shortest distance
	to the study area and the X/Y coordinate where that distance intersects the
	study area. """

	#pGP.AddMessage("Building a list of nearest points...")
	
	dcNear = {}		 # nearest distances
	dcNearXY = {}	   # nearest points   
	dcNextNear = {}	 # 

	# loop through each point
	sKeys = dcX.keys()
	for sKey in sKeys:				  # nearest distance from p to p1p2
		p = (dcX[sKey], dcY[sKey])
		p1 = pSA[0]
		lsDist = []
		for p2 in pSA[1:]:  # look for the nearest distance of point p1
			dDeltaX = p2[0] - p1[0]		  
			dDeltaY = p2[1] - p1[1]	 # vector p2p1
			dDelta1X = p[0] - p1[0]		  
			dDelta1Y = p[1] - p1[1]	 # vector pp1
			
			dLenSq = ((p1[0] - p2[0])**2.0 + (p1[1] - p2[1])**2.0)  # p1p2 norm

			if (dLenSq == 0 or p == p1):
				dcNear[sKey] = 0.0
				dcNearXY[sKey] = p1
				dDistSq = 0.0 

			else:
				dT = (dDeltaX * dDelta1X) + (dDeltaY * dDelta1Y)  # dot product

				dNearPointX = dT * dDeltaX
				dNearPointY = dT * dDeltaY  # nearest relative to p1

				dDelta1X = (dDelta1X * dLenSq - dNearPointX) / dLenSq
				dDelta1Y = (dDelta1Y * dLenSq - dNearPointY) / dLenSq

				dT = dT / dLenSq

				if dT <= 0.0:
					dNearPointX = p1[0]
					dNearPointY = p1[1]
				elif dT >= 1.0:
					dNearPointX = p2[0]
					dNearPointY = p2[1]
				else:
					dNearPointX = p1[0] + (dNearPointX / dLenSq)
					dNearPointY = p1[1] + (dNearPointY / dLenSq)							
				
				# Now let's get the distance.
				dDistSq = (dNearPointX - p[0])** 2.0 + (dNearPointY - p[1])** 2.0
				try:
					if dDistSq < dcNear[sKey]:
						dcNear[sKey] = dDistSq
						dcNearXY[sKey] = (dNearPointX, dNearPointY)
				except:
					dcNear[sKey] = dDistSq
					dcNearXY[sKey] = (dNearPointX, dNearPointY)
			p1 = p2
			lsDist.append(dDistSq)
		dcNear[sKey] = math.sqrt(dcNear[sKey])
		lsDist.sort()
		dcNextNear[sKey] = math.sqrt(lsDist[1]) 

	return dcNear, dcNearXY, dcNextNear		

def get_feature_points(sStudyAreaPath):
	"""Converse the features to the list of points."""

	pGP.AddMessage("Getting the points of a feature class...")

	sTmpDir = tempfile.gettempdir()  
	sTmpPntPath = os.path.join(sTmpDir, sTmpPntFC)
	if pGP.exists(sTmpPntPath): pGP.delete(sTmpPntPath)
	pGP.FeatureVerticesToPoints (sStudyAreaPath, sTmpPntPath)

	pStudyArea = []
	pRows = pGP.SearchCursor(sTmpPntPath)
	pRow = pRows.Next()
	while pRow <> None:
		pGeometry = pRow.shape
		sCentroid = pGeometry.TrueCentroid
		dX = float(sCentroid.split()[0])
		dY = float(sCentroid.split()[1])
		pStudyArea.append((dX, dY))
		pRow = pRows.Next()
	
	del pRows
	del pRow
	return pStudyArea	

def near_membership_function(x, a, r):
	"""The term near is considered as a linguistic value of
	the linguistic variable proximity or distance."""

	if (x >= 0 and x < a):
		near = 1.0
	elif (x >= a and x < (a + r) / 2.0):
		near = 1.0 - (2.0 * (x - a) * (x - a) / (r - a) / (r - a))
	elif (x >= (a + r) / 2.0 and x < r):
		near = 2.0 * (x - r) * (x - r) / (r - a) / (r - a)
	else:
		near = 0.0

	return near

def close_to_membership_function(x, a1, r1, a2, r2):
	"""The preference of the screening criteria falls within a certain range."""
	if (0.0 <= x and x < a1):
		close_to = 0.0
	elif (a1 <= x and x < (a1 + r1) / 2.0):
		close_to = 2.0 * (x - a1) * (x - a1)  / (r1 - a1) / (r1 - a1)
	elif ((a1 + r1) / 2.0 <= x and x < r1):
		close_to = 1.0 - (2.0 * (x - r1) * (x - r1) / (r1 - a1) / (r1 - a1))
	elif (r1 <= x and x < a2):
		close_to = 1.0
	elif (a2 <= x and x < (a2 + r2) / 2.0):
		close_to = 1.0 - (2.0 * (x - a2) * (x - a2) / (r2 - a2) / (r2 - a2))
	elif ((a2 + r2) / 2.0 <= x and x < r2):
		close_to = 2.0 * (x - r2) * (x - r2) / (r2 - a2) / (r2 - a2)
	else:
		close_to = 0.0

	return close_to

#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Checking Functions --   Functions that perform field and data validation.
#
#   check_fields_properties -  parses through the user provided arguments
#						  and ensures that they meet the requiremensts 
#						  (fields exist, have the right type, etc.)
#   check_numeric_properties - parses through numeric arguments and ensures
#						  that they meet requirements (positive, within
#						  an appropriate range, etc.)
#   validate_standardization - makes sure each feature has at least one
#							  neighbor for row standardization; makes sure
#							  sum of all weights is greater than zero
#							  for global standardization
#   check_progress - provides status report for functions that may take
#					a long time to complete.
#--------------------------------------------------------------------------
def check_field_properties(inputs, properties):
	"""Make sure user specified field properties meet tool requirements."""
	lsNumTypes = ['SmallInteger', 'Integer', 'Single', 'Double']
	try:
		if inputs.sCaseField:
			if not properties.dcFields.has_key(inputs.sCaseField):
				sMessage = msgMissingCaseErr % (inputs.sCaseField, inputs.sInputFC)
				raise ReportError(sMessage)
			if properties.dcFields[inputs.sCaseField] == 'SmallInteger':
				inputs.sFieldType = 'SHORT'
			elif properties.dcFields[inputs.sCaseField] == 'Integer':
				inputs.sFieldType = 'LONG'
			else: inputs.sFieldType = 'TEXT'
	except AttributeError: pass
	try:
		if inputs.sWeightField:
			if not properties.dcFields.has_key(inputs.sWeightField):
				sMessage = msgMissingWtErr % (inputs.sWeightField, inputs.sInputFC)
				raise ReportError(sMessage)
			if not (properties.dcFields[inputs.sWeightField] in lsNumTypes):
				sMessage = msgWtTypeErr % (inputs.sWeightField, properties.dcFields[inputs.sWeightField])
				raise ReportError(sMessage)
	except AttributeError: pass
	try:
		if inputs.sDimField:
			if not properties.dcFields.has_key(inputs.sDimField):
				sMessage = msgMissingDimErr % (inputs.sDimField, inputs.sInputFC)
				raise ReportError(sMessage)
			if not (properties.dcFields[inputs.sDimField] in lsNumTypes):
				sMessage = msgDimTypeErr % (inputs.sDimField, properties.dcFields[inputs.sDimField])
				raise ReportError(sMessage)
	except AttributeError: pass
	try:
		if inputs.sZField:
			if not properties.dcFields.has_key(inputs.sZField):
				sMessage = msgMissingFldErr % (inputs.sZField, inputs.sInputFC)
				raise ReportError(sMessage)
			if not (properties.dcFields[inputs.sZField] in lsNumTypes):
				sMessage = msgFldTypeErr % (inputs.sZField, properties.dcFields[inputs.sZField])
				raise ReportError(sMessage)
	except AttributeError: pass
	try:
		if inputs.sSelfPotential:
			if not properties.dcFields.has_key(inputs.sSelfPotential):
				sMessage = msgMissingSelfErr % (inputs.sSelfPotential, inputs.sInputFC)
				raise ReportError(sMessage)
			if not (properties.dcFields[inputs.sSelfPotential] in lsNumTypes):
				sMessage = msgSelfTypeErr % (inputs.sSelfPotential, properties.dcFields[inputs.sSelfPotential])
				raise ReportError(sMessage)
	except AttributeError: pass
	try:
		if inputs.sSpaceConcept:
			if not inputs.sSpaceConcept.find(sFromFile) >= 0:
				try:
					if inputs.sWeights:
						pGP.AddWarning (msgIgnoringWtsWrn)
						inputs.sWeights = None
				except: pass
				if inputs.sSpaceConcept.find(sFixedDst) >= 0:
					if not inputs.dDistance > 0.0:
						raise ReportError (msgMissingDstErr)
					if not inputs.dDistance < properties.dMaxExtent:
						raise ReportError (msgDstBandTooBig)
				elif inputs.sSpaceConcept.find(sIndifference) >= 0:
					if not (inputs.dDistance > 0.0):
						raise ReportError (msgMissingThrshErr)
				elif inputs.sSpaceConcept.find(sContiguity) >= 0:
					if not (properties.sShapeType == "polygon"):
						raise ReportError (msgPolyConceptOnly)
					if (inputs.dDistance > 0.0):
						pGP.AddWarning (msgIgnoringDstWrn)
			else:   # user specified weights
				if not inputs.sWeights:
					raise ReportError(msgMissingWMatrixErr)				
	except AttributeError: pass
	try:
		if inputs.sStudyAreaMethod:
			if inputs.sStudyAreaMethod == sUserSA:
				if not inputs.sStudyAreaFC:
					raise ReportError (msgMissingSAParam)
			else:
				if inputs.sStudyAreaFC:
					pGP.AddWarning (msgIgnoringStyAreaWrn)
					inputs.sStudyAreaFC = None
	except AttributeError: pass
			
	return inputs

def check_numeric_properties (inputs):
	"""Make sure numeric arguments meet tool requirements."""
	try:
		if inputs.dArea < 0.0: raise ReportError(msgAreaErr)
	except AttributeError: pass
	try:
		if inputs.dRadius < 0.0: raise ReportError (msgDstRadiusErr)
	except AttributeError: pass
	try:
		if inputs.dDistance < 0.0: raise ReportError(msgDstBandErr)
	except AttributeError: pass
	return 1

def validate_standardization (inputs, dcRowSum, dDistAllSum, sKeys, dcID):
	""" Make sure every feature has at least one neighbor, for row standardization
	Make sure sum of all weights is greater than 0.0 for global standardization."""
	if inputs.sStandardization == sRow:		 # Row standardization
		iMinRowSum = min(dcRowSum.values())
		bKeysMatch = iTrue
		if len(dcID) > 0:
			lsRowSumKeys = dcRowSum.keys()
			lsRowSumKeys.sort()
			lsIDKeys = dcID.values()
			lsIDKeys.sort()
			bKeysMatch = (lsRowSumKeys == lsIDKeys)
			
		if ((not iMinRowSum > 0.0) or (not bKeysMatch)):
			if not bKeysMatch: raise ReportError (msgIDMismatchErr)
			else:
				if inputs.dDistance > 0.0: pGP.AddWarning (msgSuggestions)
				if inputs.sWeights: pGP.AddWarning (msgCheckWMatrix)
				raise ReportError (msgNeedNeighborsErr)
			
	else:									   # Global standardization
		if not abs(dDistAllSum) > 0.0:
			raise ReportError (msgNoNeighborsErr)
	return 1

def check_progress (fInterval, fMore, iComplete):
	sMessage = "				   " + `iComplete` + sComplete
	pGP.AddMessage (sMessage)
	fInterval = fInterval + fMore
	iComplete = iComplete + 20
	return fInterval, iComplete

#--------------------------------------------------------------------------
#General utilities --   
#
#   create_poly_fc -  creates an output polygon feature class from a list
#					 of ordered points.
#   clean_up	   -  attempts to clean up files created during execution,
#					 if a tool fails 
#--------------------------------------------------------------------------

def create_point_fc (sPath, sName, pPnts, properties):

	sPoint = os.path.join(sPath, sName)
	
	try:
		pGP.CreateFeatureClass (sPath, sName, "POINT", "", "", "", properties.pSpatialRef)
		pRows = pGP.InsertCursor(sPoint)
		pPnt = pGP.CreateObject("Point")
		iPntID = 1
		for p in pPnts:  
			pPnt.id = iPntID
			pPnt.x = p[0]
			pPnt.y = p[1]
			pFeat = pRows.NewRow()
			pFeat.shape = pPnt
			pRows.InsertRow(pFeat)
			iPntID = iPntID + 1
	except:
		sErrors = pGP.GetMessages(2)
		raise ReportError (sErrors)

	del pRows
	del pFeat

def create_line_fc (sPath, sName, pLinePnts, properties):

	sLine = os.path.join(sPath, sName)
	
	try:
		pGP.CreateFeatureClass (sPath, sName, "POLYLINE", "", "", "", properties.pSpatialRef)
		#pGP.AddField_management(sLine, "SRCPTID", "long", 9)
		#pGP.AddField_management(sLine, "DESTPTID", "long", 9)
		
		pRows = pGP.InsertCursor(sLine)
		pPnt = pGP.CreateObject("Point")
		pLine = pGP.CreateObject("Array")
		iPntID = 1
		pFeat = pRows.NewRow()
		lNumObs = len(pLinePnts)
		for i in range(0, lNumObs):
			pPnt.id = iPntID
			pPnt.x = pLinePnts[i][0]
			pPnt.y = pLinePnts[i][1]
			iPntID = iPntID + 1
			pLine.add(pPnt)

			if (i % 2 != 0):
				pFeat.shape = pLine
				pRows.InsertRow(pFeat)
				pLine.RemoveAll()
			
	except:
		sErrors = pGP.GetMessages(2)
		raise ReportError (sErrors)

	del pRows
	del pFeat
	
	return sLine  

def create_poly_fc (sPath, sName, pPolyPnts, properties):

	sPoly = os.path.join(sPath, sName)
	
	try:
		pGP.CreateFeatureClass (sPath, sName, "POLYGON", "", "", "", properties.pSpatialRef)
		pRows = pGP.InsertCursor(sPoly)
		pPnt = pGP.CreateObject("Point")
		pPoly = pGP.CreateObject("Array")
		iPntID = 1
		pFeat = pRows.NewRow()
		for p in pPolyPnts:  
			pPnt.id = iPntID
			pPnt.x = p[0]
			pPnt.y = p[1]
			iPntID = iPntID + 1
			pPoly.add(pPnt)

		pFeat.shape = pPoly
		pRows.InsertRow(pFeat)
		pPoly.RemoveAll()
	except:
		sErrors = pGP.GetMessages(2)
		raise ReportError (sErrors)

	pRows = None
	return sPoly  

def clean_up (lsFiles):
	# this function takes a list of files and attempts to delete each item in the list.
	for f in lsFiles:
		try:
			pGP.Delete(f)
		except:
			pass
#--------------------------------------------------------------------------
