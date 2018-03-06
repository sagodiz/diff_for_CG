#include "../inc/Loader_sourcemeter.h"
#include "../inc/common.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Loader_sourcemeter::Loader_sourcemeter( string filepath ) : Loader(filepath) {
}
Loader_sourcemeter::~Loader_sourcemeter() {
}

bool Loader_sourcemeter::load() {
  //TODO
  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line
  
  while ( getline(input, line) ) {
    
    if ( line.find("label") != string::npos ) {
      //it is a node
      string representation;
      string infoMine;
      
      stringstream input_stringstream(line);
      getline(input_stringstream, representation, ' ');
      getline(input_stringstream, infoMine, ' ');
      
      infoMine.erase(0, 8); //[label=" --> 8 chars
      infoMine.erase(infoMine.length() - 2, 2); //"] at the end
      
      string pckgClassMethod;
      string paramsReturn;
      
      stringstream iss(infoMine);
      getline(iss, pckgClassMethod , '(');
      getline(iss, paramsReturn , '(');
      
      size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes
      if ( lastDotPos != string::npos ) {
        
        string method = pckgClassMethod.substr(lastDotPos + 1);
        string pckgClass = pckgClassMethod.substr(0, lastDotPos);
        
      }
      else {
        //TODO hibakezelés
      }
      
      //TODO: paramsReturn szétszedése, infó kiszedése
      
    }
  }
  
  return true;
}

set<pair<int, int>> Loader_sourcemeter::transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  return connections;
}