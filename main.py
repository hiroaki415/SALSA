# encoding: utf-8

import sys

def print_help():
    print 'help'

argvs = sys.argv

if argvs[1]=='start':
    print 'start!'

elif argvs[1]=='debug':
    print 'debug!'

elif argvs[1]=='gui':
    print 'gui!'

else:
    print_help()
