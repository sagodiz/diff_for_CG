#ifndef STATIC_ITERATION_H
#define STATIC_ITERATION_H

#include <set>
#include "../inc/EdgeMatrix.h"
/**
* This method creates a transitive closure graph from the given graph.
* \param start The graph that should be transitive closured.
* \param limit This number defines how far from the original node in the graph should the transitive clouser connect nodes. If it is -1 all the "child" nodes are connected otherwise all nodes till the limit depth child
* \return a graph with the extra (transitive) connections added.
*/
std::set<std::pair<int, int>> createTransClosure(const std::set<std::pair<int, int>>& start, const int limit);

/**
* This method calculates difference between two graphs. It counts the difference in calls.
* \param trace The graph of the trace tool, it is taken as base.
* \param staticGraph The graph of a static tool. Its difference is measured from trace graph.
* \return Returns an integer. The number of calls missing from static graph that are in trace graph.
*/
int createGraphDiff(const std::set<std::pair<int, int>>& trace, const std::set<std::pair<int, int>>& staticGraph );

/**
* This method creates a transitive closure graph from the given graph.
* \param start The graph that should be transitive closured.
* \param limit This number defines how far from the original node in the graph should the transitive clouser connect nodes. If it is -1 all the "child" nodes are connected otherwise all nodes till the limit depth child
* \return a graph with the extra (transitive) connections added.
*/
EdgeMatrix& createTransClosure(EdgeMatrix& , int limit);

/**
* This method calculates difference between two graphs. It counts the difference in calls.
* \param trace The graph of the trace tool, it is taken as base.
* \param staticGraph The graph of a static tool. Its difference is measured from trace graph.
* \return Returns an integer. The number of calls missing from static graph that are in trace graph.
*/
int createGraphDiff(EdgeMatrix& trace, EdgeMatrix& staticGraph );
#endif