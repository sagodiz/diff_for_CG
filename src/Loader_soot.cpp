#include "../inc/Loader_soot.h"
#include "../inc/common.h"

#include <set>
#include<iostream>

using namespace std;

Loader_soot::Loader_soot( string filepath ) : Loader(filepath) {
}
Loader_soot::~Loader_soot() {
}

bool Loader_soot::load() {
  //TODO
  //store the methods int the common::storedIds vector
  
  string line;
  while ( getline(input, line) ) {
    cout << line << endl;
    //TODO: create a record get the info from the line if it's a node.
  }
  
  return true;
}

set<pair<int, int>> Loader_soot::transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  
  return connections;
}