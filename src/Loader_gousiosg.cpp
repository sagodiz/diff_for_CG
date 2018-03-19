#include "../inc/Loader_gousiosg.h"
#include "../inc/common.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Loader_gousiosg::Loader_gousiosg( string filepath, string name ) : Loader(filepath, name) {
}
Loader_gousiosg::~Loader_gousiosg() {
}

vector<Record> Loader_gousiosg::load() {
  
  vector<Record> tmpRecords; 
  //TODO
  input.clear();
  input.seekg(0, ios::beg);
  
  return tmpRecords;
}

set<pair<int, int>> Loader_gousiosg::transformConnections() {
  
  set<pair<int, int>> connections;  //TODO
  return connections;
}