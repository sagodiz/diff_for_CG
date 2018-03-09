#include "../inc/Loader_callerhierarchy.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

Loader_callerhierarchy::Loader_callerhierarchy( string filepath ) : Loader(filepath) {
}
Loader_callerhierarchy::~Loader_callerhierarchy() {
}

vector<Record> Loader_callerhierarchy::load() {
  
  //TODO
  vector<Record> tmpRecords;
  
  string prefix = "Method call hierarchy callees of ";
  bool readyToProcess = false;
  string line;
  string representation;
  
  //clearInput();//TODO: remove the unneccessary texts and tabs.
  /*
  * Result should look like this:
  * Method
  * [Callee]*
  * <Closes with empty Line>
  */
  
  while ( getline(input, line) ) {
    
    representation = line;
    readyToProcess = false;
    
    if ( 0 == line.length() ) {
      //empty line
    }
    else {
      //caller or calle, but a node
      string pckgClassMethod, params, method, pckgClass;
      stringstream input_stringstream(line);
      
      getline(input_stringstream, pckgClassMethod , '(');
      getline(input_stringstream, params , '(');
      params.erase(params.size() - 1, 1); //remove ')'
      
      size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes
      if ( lastDotPos != string::npos ) {
        
        method = pckgClassMethod.substr(lastDotPos + 1);
        pckgClass = pckgClassMethod.substr(0, lastDotPos);
        
      }
      else {

        throw Labels::METHOD_NOT_FOUND_ERROR;
      }
      
      vector<string> parameterVector;
      stringstream iss(params);
      string parameter;
      while( getline(iss, parameter, ',') ) {
        
        parameterVector.push_back(parameter);
      }
      
      if ( 0 == pckgClass.length() || 0 == method.length() )
        throw Labels::UNINITIALIZED_RECORD;
      
      Record r(representation, pckgClass, method, parameterVector);
      tmpRecords.push_back( r );
      
      if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
        //so this record is not found in the vector
        common::storedIds.push_back(r);
        ++uniqueMethodNum;
      }
      else {
        
        auto it = find( common::storedIds.begin(), common::storedIds.end(), r );
        if ( *it == representation ) {
          //contains this representation
        }
        else {
          ++uniqueMethodNum;
          *it += representation;  //add this representation
        }
      }
    }
  }
  
  return tmpRecords;
}

set<pair<int, int>> Loader_callerhierarchy::transformConnections() {
  
  set<pair<int, int>> connections;
  
  //TODO
  return connections;
}