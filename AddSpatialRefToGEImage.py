import sys, os
import arcgisscripting
import re

def get_geo_coords( coord_file_path ):
	ret_coords = []
	f = open( coord_file_path, 'r' )
	coord_lines = f.readlines()
	for coord_line in coord_lines[0:3]:
		coord_str = coord_line.split(':')[1]
		coord_xy = coord_str.split(',')
		ret_coords.append( float(coord_xy[0]) )
		ret_coords.append( float(coord_xy[1]) )
	f.close()
	return tuple(ret_coords)
	
def warp( image_file_path, coords ):
	image_extent = gp.Describe(image_file_path).Extent.split(' ')
	print image_extent
	org_coord_strings = " '%(minx)s %(miny)s';'%(minx)s %(maxy)s';'%(maxx)s %(maxy)s' " % {"minx" : image_extent[0], "miny" : image_extent[1], "maxx" : image_extent[2], "maxy" : image_extent[3]}
	geo_coord_strings = "'%f %f';'%f %f';'%f %f'" % coords
	image_file_basename = os.path.splitext( os.path.basename(image_file_path) )[0]
	image_file_dir = os.path.dirname(image_file_path)
	out_image = os.path.join(image_file_dir, "w_" + image_file_basename +' .img')
	gp.defineprojection_management(image_file_path, "Coordinate Systems/Geographic Coordinate Systems/World/WGS 1984.prj")
	gp.Warp_management(image_file_path, org_coord_strings, geo_coord_strings, out_image, "POLYORDER1", "BILINEAR")
	
	print image_file_path
	print org_coord_strings
	print geo_coord_strings
	
	return out_image

def add_spatial_reference( image_file_path ):
	gp.defineprojection_management(image_file_path, "Coordinate Systems/Geographic Coordinate Systems/World/WGS 1984.prj")
	return

if __name__ == "__main__":
	gp = arcgisscripting.create()
	image_folder = sys.argv[1];
	image_files = []
	for root, dirs, files in os.walk(image_folder):
		for fname in files:
			if os.path.splitext(fname)[1] == ".txt":
				image_files.append( os.path.splitext(fname)[0] )
	
	for image_file in image_files:
		image_file_path = os.path.join( image_folder, image_file + ".jpg" )
		coord_file_path = os.path.join( image_folder, image_file + ".txt" )
		
		coords = get_geo_coords( coord_file_path )
		add_spatial_reference( warp( image_file_path, coords ) )
		
		print image_file_path + " ... ... ... ... ...     OK"
		