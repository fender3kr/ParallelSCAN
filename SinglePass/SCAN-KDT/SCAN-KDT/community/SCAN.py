'''
Created on Sep 30, 2017

@author: Seokyong Hong
'''
import kdt
import sys
import time
import math

class SCAN(object):
    def __init__(self):
        pass

    def detect(self, input, epsilon, mu, debug = False):
        start = time.time()
        matrix = kdt.Mat.load(fname = input, element = True, par_IO = False)
        if kdt.master():
            print '- Matrix Loading Time: ' + str(time.time() - start)
            if debug:
                print 'Input Matrix: '
                print matrix
        
        # Recover symmetricity
        t0 = time.time()
        temp = matrix.copy()
        temp.transpose()
        distanceMatrix = matrix.eWiseApply(temp, op = (lambda e1, e2: e1 if e1 >= 0 else e2), allowANulls = True, allowBNulls = True, doOp = (lambda e1, e2: e1 >= 0 or e2 >= 0), inPlace = False, ANull = -1, BNull = -1)
        
        matrix = distanceMatrix.copy()
        matrix.apply(op = (lambda e: 1))
        degrees = matrix.count(dir = kdt.Mat.Column, pred = (lambda e: e >= 0))
        if debug and kdt.master():
            print 'Degrees: '
            print degrees
        
        blankMatrix = kdt.Mat.eye(n = matrix.nrow(), m = matrix.ncol())
        blankMatrix.removeMainDiagonal()
        
        distanceMatrix = matrix.SpGEMM(matrix, semiring = kdt.sr_plustimes, inPlace = False)
        distanceMatrix.removeMainDiagonal()
        distanceMatrix.eWiseApply(matrix, op = (lambda e1, e2: e1 + 2.0 if e1 != kdt.NONE else 2.0), allowANulls = True, allowBNulls = False, inPlace = True, ANull = kdt.NONE, BNull = kdt.NONE)
        temp = matrix.copy()
        temp.scale(degrees, op = (lambda e1, e2: e2 + 1), dir = kdt.Mat.Row)
        temp.scale(degrees, op = (lambda e1, e2: math.sqrt(e1 * (e2 + 1))), dir = kdt.Mat.Column)
        distanceMatrix.eWiseApply(temp, op = (lambda e1, e2: e1 / e2), allowANulls = False, allowBNulls = True, inPlace = True)
        epsilonMatrix = blankMatrix.eWiseApply(distanceMatrix, op = (lambda e1, e2: e2), allowANulls = True, allowBNulls = False, doOp = (lambda e1, e2: e2 >= epsilon), inPlace = False)
        if kdt.master():
            print '- Computing Epsilon Matrix Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Epsilon Matrix: '
            print epsilonMatrix
        
        t0 = time.time()
        cores = epsilonMatrix.count(dir = kdt.Mat.Row)
        cores.apply(op = (lambda e: 1 if e >= mu else 0))
        if kdt.master():
            print '- Computing Core Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Cores: '
            print cores
        
        t0 = time.time()
        temp.scale(cores, dir = kdt.Mat.Row)
        temp.scale(cores, dir = kdt.Mat.Column)
        coreMatrix = temp.eWiseApply(temp, op = (lambda e1, e2: 1), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e1 > 0 and e2 > 0), allowIntersect = True)
        coreMatrix.eWiseApply(epsilonMatrix, op = (lambda e1, e2: e1), allowANulls = False, allowBNulls = False, inPlace = True)
        if kdt.master():
            print '- Computing Core Matrix: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Core Matrix: '
            print coreMatrix

        t0 = time.time()
        sourceIndex, targetIndex, valueIndex = coreMatrix.toVec()
        graph = kdt.DiGraph(sourceIndex, targetIndex, valueIndex, matrix.nrow())
        components = graph.connComp()
        if kdt.master():
            print '- Computing Component Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Components: '
            print components
        
        t0 = time.time()
        frequencies = components.hist()
        frequencies.eWiseApply(cores, op = (lambda e1, e2: 0), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e2 == 1), inPlace = True)
        if kdt.master():
            print '- Computing Frequency Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Frequencies: '
            print frequencies
        
        t0 = time.time()
        solitaries = frequencies.eWiseApply(cores, op = (lambda e1, e2: 1), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e1 == 1 and e2 != 1), inPlace = False)
        if kdt.master():
            print '- Computing Solitary Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Solitaries: '
            print solitaries
        
        t0 = time.time()
        # Set all solitary nodes as outliers
        components.eWiseApply(solitaries, op = (lambda e1, e2: -1), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e2 == 1), inPlace = True)
        # Find borders    
        temp = epsilonMatrix.copy()
        temp.apply(op = (lambda e: 1))
        temp.scale(cores, dir = kdt.Mat.Column)
        temp.scale(components, dir = kdt.Mat.Column)
        coreMatrix = blankMatrix.eWiseApply(temp, op = (lambda e1, e2: e2), allowANulls = True, allowBNulls = False, doOp = (lambda e1, e2: e2 > 0), inPlace = False)
        borders = coreMatrix.max(dir = kdt.Mat.Row, init = -1)
        if kdt.master():
            print '- Computing Border Time: ' + str(time.time() - t0)
        if debug and kdt.master():
            print 'Borders: '
            print borders
            
        t0 = time.time()
        # Assign maximum labels to borders
        components.eWiseApply(borders, op = (lambda e1, e2: e2), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e2 >= 0), inPlace = True)
        if kdt.master():
            print '- Assigning Border Label Time ' + str(time.time() - t0)

        t0 = time.time()
        # Find hubs
        solitaries.eWiseApply(borders, op = (lambda e1, e2: 1 if e1 * e2 < 0 else 0), allowANulls = False, allowBNulls = False, inPlace = True)
        matrix.scale(solitaries, op = (lambda e1, e2: e1 if e2 > 0 else 0), dir = kdt.Mat.Row)
        neighborMatrix = blankMatrix.eWiseApply(matrix, op = (lambda e1, e2: e2), allowANulls = True, allowBNulls = False, doOp = (lambda e1, e2: e2 > 0), inPlace = False)
        neighborMatrix.scale(components, op = (lambda e1, e2: e2 if e1 > 0 else 0), dir = kdt.Mat.Column)
        neighborMatrix = blankMatrix.eWiseApply(neighborMatrix, op = (lambda e1, e2: e2), allowANulls = True, allowBNulls = False, doOp = (lambda e1, e2: e2 >= 0), inPlace = False)
       
        def check_cluster(current, previous):
            if previous == -2:
                return current
            elif previous == -1:
                return -1
            else:
                if current == -2:
                    return previous
                else:
                    if previous != current:
                        return -1
                    else:
                        return current
        
        neighbor_clusters = neighborMatrix.reduce(dir = kdt.Mat.Row, op = check_cluster, init = -2)
        components.eWiseApply(neighbor_clusters, op = (lambda e1, e2: -3), allowANulls = False, allowBNulls = False, doOp = (lambda e1, e2: e2 == -1), inPlace = True)
        if kdt.master():
            print 'Finding Hub Time: ' + str(time.time() - t0)
        
        if kdt.master():
            print 'Community Detection Time: ' + str(time.time() - start)

        clusters = set()
        outlier = 0
        hub = 0
        for cluster in components:
            if cluster == -1:
                outlier += 1
            elif cluster == -3:
                hub += 1
            else:
                clusters.add(cluster)

        if kdt.master():
            print 'Clusters: ' + str(len(clusters))
            print 'Hubs: ' + str(hub)
            print 'Outliers: ' + str(outlier)
            
        #components.save('/home/phantom/Desktop/SCAN-KDT/Output/Facebook_combined.txt')
        #sys.exit()