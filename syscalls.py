#!/usr/bin/env python2.7

#syscall.py

import os

os.system('strace -o searchOutput.txt search /etc') 
os.system('strace -o findOutput.txt find /etc')

with open('searchOutput.txt', 'r') as f:
	searchLines = [line.split("(", 1)[0] for line in f]

with open('findOutput.txt', 'r') as f:
	findLines = [line.split("(", 1)[0] for line in f]

#use dictionary to hold numbers and values
def putInDict(lines):
	result = dict()
	for line in lines:
		if line not in result.keys():
			result.update({line:1})
		else:
			result[line] = result[line] + 1
	return result

print("# search /etc")
searchResult = putInDict(searchLines)
for key in sorted(searchResult, key=searchResult.get, reverse=True):
	print ('\t{} {}'.format(searchResult[key], key))

print("\n#find /etc")
findResult = putInDict(findLines)
for key in sorted(findResult, key=findResult.get, reverse=True):
	print ('\t{} {}'.format(findResult[key], key))
