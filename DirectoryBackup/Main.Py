import os, sys, DirectoryBackup

if __name__ == "__main__":
	
	src_dir = raw_input("Input Source Directory:")
	inputList = []
	dirCmper = None
	
	try:
		while True:
			destDir = str(raw_input("Input Destination Directory:"))
			if dirCmper == None:
				dirCmper = DirectoryBackup.dirBackupList(src_dir, destDir)
			else:
				dirCmper.add_right_dir(destDir)
	except:
		pass
		
	print dirCmper.right_only
	
