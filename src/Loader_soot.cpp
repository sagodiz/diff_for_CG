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
  getline(input, line); //get the "header" line
  
  while ( getline(input, line) ) {
    //TODO: create a record get the info from the line if it's a node. And not the closure of the file.
    if ( line.find("->") == string::npos && line != "}" ) {
      //the line doesn't contains the "->" sub-string so it is not a caller-calle connection but a node
      line.erase(0, 6); //remove the '<4 spaces>"<' beginning
      line.erase(line.length()-2, 2); //remove the '">' ending
      cout << line << endl;
      
      //get the needed info. for a Record then algorithm::find(.., r) can be used...
    }
  }
  input.clear();
  input.seekg(0, ios::beg);
  
  return true;
}

set<pair<int, int>> Loader_soot::transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  
  return connections;
}