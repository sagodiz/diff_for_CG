#include "../inc/Loader_jdt.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

Loader_jdt::Loader_jdt( string filepath, string name ) : Loader(filepath, name) {
}
Loader_jdt::~Loader_jdt() {
}

vector<Record> Loader_jdt::load() {

  vector<Record> tmpRecords;
  
  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line
  
  while ( getline(input, line) ) {
    
    if ( line.find("label") != string::npos ) {

    } //end of processing label
  }//end of processing line
  
  input.clear();
  input.seekg(0, ios::beg);
  
  printNotFilteredMethodNames();

  return tmpRecords;
}

set<pair<int, int>> Loader_jdt::transformConnections() {

  set<pair<int, int>> connections;

  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line

  while ( getline(input, line) ) {
    
  if ( line.find("label") == string::npos && line[0] != '}' ) {
      
      
    std::string delimiter = "->";
    size_t delimiter_pos = line.find(delimiter);
    string caller = line.substr(0, delimiter_pos);  //left part
    common::trim(caller);
    string callee = line.substr(delimiter_pos + delimiter.length());  //right part
    common::trim(callee);

    //it is a connection
    ++callNum;
      
      int callerId = -1, calleeId = -1;
      
      bool check = false; //to check if the method do be found.
      
      for (unsigned i = 0; i < common::storedIds.size(); i++ ) {
        
        if ( common::storedIds[i] == pair<string, string>(caller, name) ) {
          
          check = true;
          callerId = i;
          break;
        }
      }
      if ( !check ) {
        
        cerr << "Method couldn't be resolved: " << caller << endl;
      }
      
      check = false;
      for (unsigned i = 0; i < common::storedIds.size(); i++ ) {
        
        if ( common::storedIds[i] == pair<string, string>(callee, name) ) {
          
          check = true;
          calleeId = i;
          break;
        }
      }
      if ( !check ) {
        
        cerr << "Method couldn't be resolved: " << callee << endl;
      }
      
      connections.insert(pair<int, int>(callerId, calleeId));
    }
    else {
      //do nothing
    }
  }

  return connections;
}