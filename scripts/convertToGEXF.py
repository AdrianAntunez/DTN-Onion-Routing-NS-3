#!/usr/bin/python

# converts Adrian's graph format to GEXF dynamic graph format so it can be imported 
# by gephi and similar packages
#
# Uses pygexf (can be installed by pip)
# https://pythonhosted.org/pygexf/users.html
#

import gexf


src_file = "../simulations/data/graphs/seattle-busses-contacts-86400h-1180n.txt"
out_file= "../simulations/data/graphs/seattle-busses-contacts-86400h-1180n.gexf"

ge = gexf.Gexf("guille", "Seattle bus contacts")
graph = ge.addGraph("undirected","dynamic","seattle")

#nodes from 0 to 1179

for node in range(1180):
    graph.addNode(str(node), str(node))

print("Graph created, reading edges...")
    
with open(src_file, "r") as f:
    edge_id = 0
    #skip header
    next(f)
    for line in f:
        n1, n2, start_time, duration = line.split(":")
        end_time = int(start_time) + int(duration)
        graph.addEdge(edge_id, n1, n2, start=str(start_time), end=str(end_time))
        edge_id += 1

print("Done with edges: " + str(edge_id))

output = open(out_file, "w")
ge.write(output)

