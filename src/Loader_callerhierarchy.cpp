#ifdef DEBUG
#define DDD cout << "New record is added...: " << f_classWithPckg << " " << method << " " << endl;
#else 
#define DDD ;
#endif

#include "../inc/Loader_callerhierarchy.h"
#include "../inc/common.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Loader_callerhierarchy::Loader_callerhierarchy( string filepath ) : Loader(filepath) {
}
Loader_callerhierarchy::~Loader_callerhierarchy() {
}

vector<Record> Loader_callerhierarchy::load() {
  
  //TODO
  vector<Record> tmp;
  return tmp;
}

set<pair<int, int>> Loader_callerhierarchy::transformConnections() {
  
  set<pair<int, int>> connections;
  
  //TODO
  return connections;
}