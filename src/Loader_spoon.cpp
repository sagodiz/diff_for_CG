#include "../inc/Loader_spoon.h"
#include "../inc/common.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Loader_spoon::Loader_spoon( string filepath ) : Loader(filepath) {
}
Loader_spoon::~Loader_spoon() {
}

vector<Record> Loader_spoon::load() {
  
  vector<Record> tmpRecords;  //TODO
  input.clear();
  input.seekg(0, ios::beg);
  
  return tmpRecords;
}

set<pair<int, int>> Loader_spoon::transformConnections() {

  set<pair<int, int>> connections;
  
  return connections;
}