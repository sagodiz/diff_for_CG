#!/usr/bin/python3

# DESCRIPTION

import sys
import networkx as nx
from networkx.readwrite import json_graph
import argparse as ap
import json
import os.path
import re

MAP_FILE_SEPARATOR = ':'
KNOWN_FILE_FORMATS = ['json','graphml', 'dot']

#usage
#python convert-graph-formats.py -q  -d -i graphml -o dot  -m D:\Users\epengo\Documents\diff_for_CG\bemenetek\trace\joda-time-2.9.9\joda-time-v2.9.9-trace-names.txt D:\Users\epengo\Documents\diff_for_CG\bemenetek\trace\joda-time-2.9.9\graph D:\Users\epengo\Documents\diff_for_CG\bemenetek\trace\joda-time-2.9.9\joda_time_merged.dot

def format_from_filename(fname):
    ext = os.path.splitext(fname)[-1][1:]
    if ext not in KNOWN_FILE_FORMATS:
        ext = 'json'
    return ext

def read_graph(fname):
    global clargs
    if clargs.verbose:
        print("Reading " + fname, end='\033[K\n')
    if clargs.in_format == 'json':
        with open(fname, 'r') as jsonfile:
            return nx.readwrite.json_graph.node_link_graph(json.load(jsonfile))
    elif clargs.in_format == 'graphml':
        return nx.read_graphml(fname, int)
    elif clargs.in_format == 'dot':
        print("Not supported")
        return False
    return False

def read_map():
    global clargs
    if clargs.verbose:
        print("Reading map file " + clargs.mfile, end='\033[K\n')
    mapping = {}
    with open(clargs.mfile) as mapfile:
        for line in mapfile:
            item = line.rstrip().split(MAP_FILE_SEPARATOR)
            mapping[item[0]] = item[1]
    return mapping

def map_graph(graph, mapping):
    for node in graph.node:
        label = graph.node[node]['label']
        if label in mapping:
            graph.node[node]['label'] = mapping[label]
			

def filter_graph(graph):
    global clargs
    if clargs.verbose:
        print('Applying filter "' + clargs.fregex + '"', end='\033[K\n')
    regex = re.compile(clargs.fregex)
    for node in graph.nodes():
        if regex.match(graph.node[node]['label']):
            graph.remove_node(node)

def write_graph(graph):
    global clargs
    if clargs.verbose:
        print("Writing " + clargs.ofile, end='\033[K\n')
    if clargs.out_format == 'json':
        with open(clargs.ofile, 'w') as jsonfile:
            json.dump(nx.readwrite.json_graph.node_link_data(graph), jsonfile)
    elif clargs.out_format == 'graphml':
        nx.write_graphml(graph, clargs.ofile)
    elif clargs.out_format == 'dot':
        with open(clargs.ofile, 'w') as dotfile:
            dotfile.write("digraph graphname {\nrankdir=\"LR\";\n")
            for node in graph.node:
                dotfile.write(str(node) +" [label=\""+ graph.node[node]['label']+"\"]\n")
            for edge in graph.edges:
                dotfile.write(str(edge[0]) + " -> " + str(edge[1]) + "\n")			    
            dotfile.write("}")
			
			

clap = ap.ArgumentParser(description = 'This script converts between graph formats.');
clap.add_argument('-q', '--quiet',    dest='verbose',    action='store_false',
                help='do not print messages except fatal errors')
clap.add_argument('-v', '--verbose',  dest='verbose',    action='store_true',
                help='print information messages (default)')
clap.add_argument('-i', '--input-format',  dest='in_format',  action='store', choices=KNOWN_FILE_FORMATS,
                help='select input file format')
clap.add_argument('-o', '--output-format', dest='out_format', action='store', choices=KNOWN_FILE_FORMATS,
                help='select output file format')
clap.add_argument('-m', '--map-file',      dest='mfile',      action='store',
                help='map file (contains lines in the form "A' + MAP_FILE_SEPARATOR + 'B" to change the label A to B)')
clap.add_argument('-f', '--filter-regexp', dest='fregex',     action='store',
                help='remove nodes whose labels match the regexp (after mapping)')
clap.add_argument('-d', '--directory',    dest='dir',    action='store_true',
                help='input files are given in a folder and will be merged in one output')
clap.add_argument('ifile', help='input file')
clap.add_argument('ofile', help='out file')

clap.set_defaults(in_format=False, out_format=False, verbose=True, mfile=False, fregex=False, ifile=False, ofile=False);
clargs = clap.parse_args()

if not clargs.in_format:
    if not clargs.dir:
        print("Must give an input file format in directory mode!")
        sys.exit()
    clargs.in_format = format_from_filename(clargs.ifile)
if not clargs.out_format:
    clargs.out_format = format_from_filename(clargs.ofile)
	
if  clargs.dir and clargs.out_format != 'dot':
    print("No dir mode with not dot output!")
    sys.exit()

input_list = []
if  clargs.dir:
    for file in os.listdir(clargs.ifile):
        if file.endswith(clargs.in_format):
            input_list.append(os.path.join(clargs.ifile, file))
else:
    input_list = [clargs.ifile]
	
if clargs.mfile:
    mapping = read_map()
graph_list = []
for x in input_list:
    graph = read_graph(x)
    if clargs.mfile and not clargs.dir:
        map_graph(graph, mapping)
    if clargs.fregex:
        filter_graph(graph)
    graph_list.append(graph)
    if not clargs.dir:
        write_graph(graph)
	
if clargs.dir:
    used_nodes = set()
    with open(clargs.ofile, 'w') as dotfile:
        dotfile.write("digraph graphname {\nrankdir=\"LR\";\n")
        for g in graph_list:
            for node in g.node:
                label = g.node[node]['label']
                if label not in used_nodes and label in mapping:
                    dotfile.write(str(label) +" [label=\""+ mapping[label] +"\"]\n")
                    used_nodes.add(label)
        for g in graph_list:
            for edge in g.edges:
                dotfile.write(str(g.node[edge[0]]['label']) + " -> " + str(g.node[edge[1]]['label']) + "\n")
        dotfile.write("}")

