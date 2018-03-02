#include "../inc/Loader_soot.h"
#include <set>

using namespace std;

Loader_soot::Loader_soot( string filepath ) : Loader(filepath) {
}
Loader_soot::~Loader_soot(){
}

bool load() {
  //TODO
  //store the methods int the common::storedIds vector
  return true;//TODO
}

set<pair<int, int>> transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  
  return connections;
}