'''
Created on Sep 30, 2017
@author: Seokyong Hong
'''
import os
import time
import networkx
from community.SCAN import SCAN

input_path = '/Input/Com-Amazon.txt'

if __name__ == '__main__':
    start = time.time()
    
    digraph = networkx.read_edgelist(path = input_path, delimiter = '\t', create_using = networkx.DiGraph())
    graph = networkx.to_scipy_sparse_matrix(digraph.to_undirected())
    
    t0 = time.time() 
    labels = SCAN().detect(graph = graph, epsilon = 0.7, mu = 2)
    print 'Community Detection Time: ' + str(time.time() - t0)

    '''
    community_labels = set()
    community_count = 0
    hub_count = 0
    outlier_count = 0
    community = {}
    max_label = int(max(labels)) + 1
  
    for index in range(len(labels)):
        if labels[index] >= 0:
            community[list(digraph.nodes(data = False))[index]] = int(labels[index])
            if int(labels[index]) not in community_labels:
                community_count += 1
                community_labels.add(int(labels[index]))
        else:
            community[list(digraph.nodes(data = False))[index]] = int(labels[index])
            #community[digraph.nodes(data = False)[index]] = max_label
            #max_label = max_label + 1
            if int(labels[index]) == -2:
                hub_count += 1
            elif int(labels[index]) == -3:
                outlier_count += 1
    
    #networkx.set_node_attributes(digraph, 'community', community)
    
    print 'Computing community done.'
    print 'Number of Communities: ' + str(len(community_labels))
    print 'Number of Hubs: ' + str(hub_count)
    print 'Number of Outlier: ' + str(outlier_count)
    print 'Total Execution Time: ' + str(time.time() - start)
    '''
