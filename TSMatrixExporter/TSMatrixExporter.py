# -*- coding: cp936 -*-

import sys, os
import arcgisscripting
from GPHelper.Workspace import *
from GPHelper.FeatureClass import *
from GPHelper.Shape import *

def split( lst, is_split_point ):
	ret = []
	cur_list = []
	for item in lst:
		if is_split_point(item):
			ret.append( cur_list )
			cur_list = []
		else:
			cur_list.append( item )
	return ret

def is_split_point( item ):
	if len(item) == 1 and item[0] == '\n':
		return True

class block:
	def __init__( self, block_data ):
		self.block_desc = block_data[0].strip()
		self.data = [ [ float(v_str) for v_str in data_line.strip().split(',') if len(v_str.strip()) > 0 ] for data_line in block_data[1:] if len(data_line[0].strip()) > 0 ]
		self.width = len( self.data[0] )
		self.height =len( self.data )
		return
	
	def ExportToPointFeatureClass(self, ws_path):
		"""
		Export Data as Point Feature Clas
		"""

		print "Begin Exporting %s ..." % self.block_desc
		ws = Workspace( ws_path )
		featcls = FeatureClass( ws.CreateFeatureClass( self.block_desc, "POINT" ) )
		featcls.AddField( "VALUE", "FLOAT" )
		featSet = featcls.Features(OpenMode.WriteOnly)

		for y in range(self.height):
			for x in range(self.width):
				pt = Point.FromXY(x, y)
				curFeat = featSet.next()
				curFeat.SetShape(pt.ArcGISPoint())
				curFeat["VALUE"] = self.data[y][x]
		featcls.Flush()
		return
	
if __name__ == "__main__":
	file_name = sys.argv[1]
	output_workspace = sys.argv[2]
			  
	f = open( file_name, "r" )
	lines = f.readlines()
	f.close()
	
	blocks = split( lines, is_split_point )
	
	for block_data in blocks:
		b = block( block_data )
		b.ExportToPointFeatureClass( output_workspace )
