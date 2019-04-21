'''
Created on Sep 30, 2017
@author: Seokyong Hong
'''
import itertools
import numpy as np
from collections import deque

class SCAN(object):
    def __init__(self):
        pass
    
    def detect(self, graph, epsilon = 0.7, mu = 2):
        v = graph.shape[0]
        vertex_labels = -np.ones(v)
        except_labels = np.zeros(v)
        cluster_id = 0
        
        for vertex in xrange(v):
            if vertex_labels[vertex] != -1:
                continue
             
            N, vcols = self.neighborhood(graph, graph[vertex,:], epsilon)
          
            if len(N) >= mu:
                cluster_id += 1
                vertex_labels[vertex] = cluster_id
                while N:
                    y = N.pop()
                    R , ycols = self.neighborhood(graph, graph[y,:], epsilon)
                   
                    vertex_labels[y] = cluster_id
                    if len(R) >= mu:
                        while R:
                            r = R.pop()
                            label = vertex_labels[r]
                            
                            if label == -1 or label == 0: 
                                vertex_labels[r] = cluster_id

                            if label == -1:
                                N.appendleft(r)
            else:
                vertex_labels[vertex] = 0
        
        for index in np.where(vertex_labels == 0)[0]:
            ncols = graph[index,:].tocoo().col
            
            label = -1
            for a, b in itertools.combinations(ncols, 2):
                if vertex_labels[a] > 0 and vertex_labels[b] > 0 and vertex_labels[a] != vertex_labels[b]:
                    label = -3
                    break
            
            except_labels[index] = label  
    
        for index in range(len(except_labels)):
            if except_labels[index] < 0:
                vertex_labels[index] = except_labels[index] 
    
        return vertex_labels
    
    def struct_similarity(self, vcols, wcols):
        count = [index for index in wcols if (index in vcols)]
        ans = (len(count) + 2) / (((vcols.size + 1) * (wcols.size + 1)) ** .5)
       
        return ans

    def neighborhood(self, G, vertex_v, eps):
        N = deque()
        
        vcols = vertex_v.tocoo().col
        
        for index in vcols:
            wcols = G[index,:].tocoo().col
            if self.struct_similarity(vcols, wcols) >= eps:
                N.append(index)
                
        return N, vcols