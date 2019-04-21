'''
Created on Sep 30, 2017

@author: Seokyong Hong
'''
import os
import sys
import kdt
import time
from community.SCAN import SCAN

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: mpirun -np <#processes> python Test.py <input> <mu> <epsilon>")
        sys.exit()
        
    start = time.time()
    input_path = sys.argv[1]
    mu = int(sys.argv[2])
    epsilon = float(sys.argv[3])
    scan = SCAN()
    scan.detect(input = input_path, epsilon = epsilon, mu = mu, debug = False)
    if kdt.master():
        print 'Time: ' + str(time.time() - start)