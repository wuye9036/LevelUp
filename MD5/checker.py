import sig
from sig import signature
import sys

if __name__ == "__main__":
	if signature.check_and_update_md5file('.md5', [sys.argv[0]]):
		print 'unchanged'
	else:
		print 'changed'