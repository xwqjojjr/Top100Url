#!/usr/bin/python
# -*- coding: UTF-8 -*-
import random
import time
import string
import sys
import getopt


if __name__ == "__main__":
        try:
                opts, args = getopt.getopt(sys.argv[1:], "hf:s:", ["help", "file=", "size="])
        except getopt.GetoptError:
                print 'makeData.py -f <inputfile> -s <fileSize GB>'
                sys.exit(2)
        
	for opt, arg in opts:
                if opt == '-h':
                        print 'makeData.py -f <inputfile> -s <size >(GB)'
                        sys.exit()
                elif opt in ("-f", "--file"):
                        inputfile = arg
                elif opt in ("-s", "--size"):
                        filesize = arg
	# Number of URLs of 1GB size
	loop_count = 1*1024*1024*1024/400
	loop_count_2 = int(filesize)*10
	f = open(inputfile, 'w')
	l = []
	#Splicing URLs
    	begin_time = time.time()
        chars = 'AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789'
    	for i in range(loop_count_2):
    		for x in range(loop_count):
        		url1 = string.join(random.sample(chars, random.randint(4,6)), '')
			url2 = string.join(random.sample(chars, random.randint(2,4)), '')
			url3 = string.join(random.sample(chars, random.randint(3,8)), '')
			url = url1+'.'+url2+'/'+url3+'\n'
        		l.append(url)
    		f.writelines(l)
    		f.flush()
		print ("...")
		l = []

    	end_time = time.time()
    	total_sec = end_time - begin_time
    	qps = loop_count*loop_count_2/total_sec
    	print "总共耗时(s): " + str(total_sec)
    	print "QPS: " + str(qps)
    	f.close()
