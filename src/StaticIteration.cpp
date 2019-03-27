#include "../inc/StaticIteration.h"

using namespace std;
/**
* This method creates a transitive closure graph from the given graph.
* \param start The graph that should be transitive closured.
* \param limit This number defines how far from the original node in the graph should the transitive clouser connect nodes. If it is -1 all the "child" nodes are connected otherwise all nodes till the limit depth child
* \return a graph with the extra (transitive) connections added.
*/
set<pair<int, int>> createTransClosure(set<pair<int, int>> start, int limit) {
  
  //TODO
  return start;
}

/**
* This method calculates difference between two graphs. It counts the difference in calls.
* \param trace The graph of the trace tool, it is taken as base.
* \param staticGraph The graph of a static tool. Its difference is measured from trace graph.
* \return Returns an integer. The number of calls missing from static graph that are in trace graph.
*/
int createGraphDiff(set<pair<int, int>> trace, set<pair<int, int>> staticGraph ) {
  
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