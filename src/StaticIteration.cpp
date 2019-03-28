#include <string>

#include "../inc/StaticIteration.h"
#include "../inc/Labels.h"

using namespace std;


/**
* This method creates a transitive closure graph from the given graph.
* \param start The graph that should be transitive closured.
* \param limit This number defines how far from the original node in the graph should the transitive closure connect nodes. If it is -1 all the "child" nodes are connected otherwise all nodes till the limit depth child
* \return a graph with the extra (transitive) connections added.
*/
set<pair<int, int>> createTransClosure(const set<pair<int, int>>& start, const int limit) {
  
  //TODO
  return start;
}

/**
* This method calculates difference between two graphs. It counts the difference in calls.
* \param trace The graph of the trace tool, it is taken as base.
* \param staticGraph The graph of a static tool. Its difference is measured from trace graph.
* \return Returns an integer. The number of calls missing from static graph that are in trace graph.
*/
int createGraphDiff(const set<pair<int, int>>& trace, const set<pair<int, int>>& staticGraph ) {
  
  int difference = 0;
  
  for (auto it : trace) {

    if (staticGraph.find(it) == staticGraph.end()) {
      //found
      ++difference;
    }
    else {

      //some debug. maybeeeeee
    }
  }
  
  return difference;
}

/**
* This method creates a transitive closure graph from the given graph.
* \param start The graph that should be transitive closured.
* \param limit This number defines how far from the original node in the graph should the transitive closure connect nodes. If it is -1 all the "child" nodes are connected otherwise all nodes till the limit depth child
* \return a graph with the extra (transitive) connections added.
*/
void createTransClosure(EdgeMatrix& start, const int limit) {

  for (int l = 0; l < limit; l++) { //iteration depts

    EdgeMatrix tmp(start.getSize());

    for (int i = 0; i < start.getSize(); i++) { //rows

      for (int j = 0; j < start.getSize(); j++) { //columns

        if (1 == start.getCell(i, j)) {
         
          for (int e = 0; e < start.getSize(); e++) {

            if (1 == start.getCell(j, e)) { //so the callee became caller
              tmp.setCell(j, e);
            }
          }
        }
      }
    }

    start += tmp;
  }
}

/**
* This method calculates difference between two graphs. It counts the difference in calls.
* \param trace The graph of the trace tool, it is taken as base.
* \param staticGraph The graph of a static tool. Its difference is measured from trace graph.
* \return Returns an integer. The number of calls missing from static graph that are in trace graph.
*/
int createGraphDiff(const EdgeMatrix& trace, const EdgeMatrix& staticGraph) {

  int difference = 0;
//TODO
  return difference;
}

/**
* This method creates an EdgeMatrix from a set of edges
* \param edges this param contains the set of edges that are inserted to the matrix
* \param size it is optional. By default it is -1. It is the size of the matrix that should be converted. If this size is smaller than the possible matrix indexes the behavior is undefined. If it is -1, the biggest value is set as size.
* \return Returns a pointer to an EdgeMatrix object that contains all the calls that were in the param edges.
*/
EdgeMatrix* createEdgeMatrixPointer(std::set<std::pair<int, int>>& edges, int size) {
  
  EdgeMatrix* matrix = NULL;
  if ( -1 != size ) {
    matrix = new EdgeMatrix(size);
  }
  else {
    cout << "Why are you even using it?" << endl;
    long int biggest = -1;
    for ( auto it : edges ) {
      
      if ( it.first > biggest )
        biggest = it.first;
      if ( it.second > biggest )
        biggest = it.second;
    }
    
    if ( -1 == biggest )
      throw Labels::UNKNOWN_ERROR_BIGGEST_EDGEID_MINUS + to_string(biggest);
    
    matrix = new EdgeMatrix(biggest);
  }
  
  for ( auto it : edges ) {
    
    *matrix += it;
  }
  
  return matrix;
}