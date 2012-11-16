#!/usr/bin/env python
from HelperFunctions import *

class Shape:
	Point = 'point'
	Line = 'line'
	Polygon = 'polygon'
	
	def __init__(self, type):
		self.type_ = type
		
	def ShapeType(self):
		return self.type_
	
class Point(Shape):
	@staticmethod
	def FromArcGISPoint(agsPt):
		return Point(agsPt)
	
	@staticmethod
	def FromXY(x, y):
		retPt = Point(None)
		retPt.SetCoord(x, y)
		return retPt
	
	@staticmethod
	def FromFeature(feat):
		#if not isinstance(feat, Feature): return None
		if feat.ShapeTypeName() != "point": return None
		shape = feat.Shape()
		return Point.FromShape(shape)
	
	@staticmethod
	def FromShape(shape):
		agsPt = shape.GetPart()
		return Point(agsPt)
	
	def __init__(self, agsPt):
		Shape.__init__(self, Shape.Point)
			
		if agsPt:
			self.ID = agsPt.id
			self.X = agsPt.X
			self.Y = agsPt.Y
		else:
			self.ID = None
			self.X = None
			self.Y = None
			
	def Coord(self):
		return (self.X, self.Y)
	
	def SetCoord(self, x = None, y = None):
		if x:
			self.X = x
		if y:
			self.Y = y
		return self
	
	def ArcGISPoint(self):
		pt = pGP.CreateObject("Point")
		if self.ID:
			pt.ID = self.ID
		if self.X:
			pt.X = self.X
		if self.Y:
			pt.Y = self.Y
		return pt
	
class Line(Shape):
	@staticmethod
	def FromSegmentPairs(segmentPairsList):
		retLine = Line()
		retLine.segmentList_ = segmentPairsList
		return retLine
		
	@staticmethod
	def FromSegment(segment):
		retLine = Line()
		retLine.segmentList_ = [(segment, None)]
		return retLine
	
	@staticmethod
	def FromArcGISLine(line):
		return Line(line)
	
	@staticmethod
	def FromShape(shape):
		return Line(shape)
	
	@staticmethod
	def FromFeature(feat):
		#if not isinstance(feat, Feature): return None
		shapeType = feat.ShapeTypeName()
		if not (shapeType == 'line' or shapeType == 'polyline' or shapeType == "polygon"):
			return None
		return Line.FromShape(feat.Shape())
	
	
	def __init__(self, agsLine):
		Shape.__init__(self, Shape.Line)
		
		self.segmentList_ = []
		
		if agsLine:
			segmentCount = agsLine.PartCount
			segmentIdx = 0
			
			while segmentIdx < segmentCount:
				pointIter = agsLine.GetPart(segmentIdx)
				segmentPair = self._ReadPointsFromIterator(pointIter)
				self.segmentList_.append(segmentPair)
				segmentIdx += 1
			
	def _ReadPointsFromIterator(self, iter):
		outeriorSegment = []
		interiorSegment = None
		
		currentSegment = outeriorSegment
		
		pt = iter.next()
		while pt:
			currentSegment.append(Point(pt))
			pt = iter.next()
			
			if not pt:
				pt = iter.next()
				if pt:
					interiorSegment = []
					currentSegment = interiorSegment
		
		return (outeriorSegment, interiorSegment)
	
	def OuteriorSegments(self):
		return zip(*self.segmentList_)[0]
	
	def InteriorSegments(self):
		return zip(*self.segmentList_)[1]
	
	def AddSegments(self, outeriorSegment, interiorSegment = None):
		self.segmentList_.append((outeriorSegment, interiorSegment))
		
	def ArcGISLine(self):
		line = pGP.CreateObject("Array")
		agsSegment = pGP.CreateObject("Array")
		
		for segPair in self.segmentList_:
			outeriorSegment = segPair[0]
			for pt in outeriorSegment:
				agsPt = pt.ArcGISPoint()
				agsSegment.add(agsPt)
			interiorSegment = segPair[1]
			if interiorSegment:
				agsPt = None
				agsSegment.add(agsPt)
				for pt in interiorSegment:
					agsPt = pt.ArcGISPoint()
					agsSegment.add(agsPt)
			line.add(agsSegment)
			agsSegment.RemoveAll()
		return line