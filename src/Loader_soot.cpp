#include "../inc/Loader_soot.h"
#include <set>

using namespace std;

Loader_soot::Loader_soot( string filepath ) : Loader(filepath) {
}
Loader_soot::~Loader_soot() {
}

bool Loader_soot::load() {
  //TODO
  //store the methods int the common::storedIds vector
  return true;//TODO
}

set<pair<int, int>> Loader_soot::transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  
  return connections;
}