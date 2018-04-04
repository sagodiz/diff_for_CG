#python3 json2gremlin.py -i "samples\totinfo.dynamic.json" -os "ws://localhost:8182/gremlin" -ots "g"
# http://tinkerpop.apache.org/docs/current/reference/#vertex-properties
# https://stackoverflow.com/questions/44163563/gremlin-adding-edges-between-nodes-having-the-same-property/44170022

from gremlin_python import statics
from gremlin_python.structure.graph import Graph
from gremlin_python.process.graph_traversal import __
from gremlin_python.process.strategies import *
from gremlin_python.process.traversal import P
from gremlin_python.driver.driver_remote_connection import DriverRemoteConnection
import networkx as nx

import pdb
import argparse as ap

clap = ap.ArgumentParser(description = 'This script load JSON graph formats to Apache TinkerPop Gremlin server.');
clap.add_argument('-os', '--output-server', dest='output_server', action='store', help='URL of the output Gremlin server')
clap.add_argument('-ots', '--output-source', dest='output_source', action='store', help='name of the output Gremlin traversal source')
clap.add_argument('-pr1', '--project_name1', dest='project_name1', action='store', default="default", help='source_name label value for graph 1')
clap.add_argument('-pr2', '--project_name2', dest='project_name2', action='store', default="default", help='source_name label value for graph 2')
clap.add_argument('-q', '--quiet', dest='verbose', action='store_false', help='do not print messages except fatal errors')

clargs = clap.parse_args()

def printX(obj=""):
	if clargs.verbose:
		print(obj)
		
def printSet(a_set):
    for element in a_set:
	    printX(element)

printX("output Gremlin server: %s, %s" % (clargs.output_server, clargs.output_source))
output_graph = Graph().traversal().withRemote(DriverRemoteConnection(clargs.output_server, clargs.output_source))


printX()

nodesInOne = output_graph.V().has("source_name", clargs.project_name1).values("label").toList()
printX("total nodes in %s graph: %d" % (clargs.project_name1, len(nodesInOne)))
edgesInOne = output_graph.V().has("source_name", clargs.project_name1).as_("a").outE().inV().as_("b").select("a", "b").by("label").toList()
printX("total edges in %s graph: %d" % (clargs.project_name1, len(edgesInOne)))
printX()
nodesInTwo = output_graph.V().has("source_name", clargs.project_name2).values("label").toList()
printX("total nodes in %s graph: %d" % (clargs.project_name2, len(nodesInTwo)))
edgesInTwo = output_graph.V().has("source_name", clargs.project_name2).as_("a").outE().inV().as_("b").select("a", "b").by("label").toList()
printX("total edges in %s graph: %d" % (clargs.project_name2, len(edgesInTwo)))


nodesInOneSet = set(nodesInOne)
nodesInTwoSet = set(nodesInTwo)

unmachedInTwo = nodesInTwoSet - nodesInOneSet
unmatchedInOne = nodesInOneSet - nodesInTwoSet
pairedNodes = set.intersection(nodesInTwoSet, nodesInOneSet)
printX()
printX("Number of paired nodes: %d" % len(pairedNodes))
printX("Number of unpaired nodes in %s: %d" % (clargs.project_name1, len(unmatchedInOne)))
printX("Number of unpaired nodes in %s: %d" % (clargs.project_name2, len(unmachedInTwo)))

printX()
printX("Unmatched nodes in %s:" % clargs.project_name2)
printSet(unmachedInTwo)

printX()
printX("Unmatched nodes in %s:" % clargs.project_name1)
printSet(unmatchedInOne)

edgesInOneSet = set()
edgesInTwoSet = set()

def createSetFromDict(dict, dictSet):
    for element in dict:
        edge = ""
        for key, value in element.items():
	        if key == "b":
		        edge += " -> "
	        edge += value
        dictSet.add(edge)

createSetFromDict(edgesInOne, edgesInOneSet)
createSetFromDict(edgesInTwo, edgesInTwoSet)

unmatchededgesInOne = edgesInOneSet - edgesInTwoSet
unmatchededgesInTwo = edgesInTwoSet - edgesInOneSet

printX()
printX("Unmatched edges in %s graph:" % clargs.project_name1)
printSet(unmatchededgesInOne)

printX()
printX("Unmatched edges in %s graph:" % clargs.project_name2)
printSet(unmatchededgesInTwo)


