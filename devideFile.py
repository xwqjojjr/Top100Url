#Split files so that small files can be loaded into memory
#-*-coding:utf-8-*-
import time
import string
import resource
import sys,getopt
# Limit system resource
"""
import sys
soft,hard=resource.getrlimit(resource.RLIMIT_AS)
size_hint = 9*1024*1024
resource.setrlimit(resource.RLIMIT_AS,(size_hint,size_hint))
"""
if __name__ == "__main__":
	try:
		opts, args = getopt.getopt(sys.argv[1:], "hf:n:", ["help","file=", "number="])
	except getopt.GetoptError:
		print 'devideFile.py -n number of file to split, -f filepath'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'devideFile.py -n number of file to split, -f filepath'
			sys.exit()
		elif opt in ("-n", "--number"):
			n = arg
		elif opt in ("-f","--file"):
			filename = arg
	n = int(n)
	file_name_list = []
	try:
		for i in range(n):
			file_name = str(i)+'.txt'
			file_name = open(file_name,'a+')
			file_name_list.append(file_name)
			
		with open(filename, 'r') as flie:
			for line in flie:
				target_file_name = hash(line)%n
				file_name_list[target_file_name].write(line)        

		for i in range(len(file_name_list)):
			file_name_list[i].close()
	except Exception, e:
		print e
		raise
	flie.close()
