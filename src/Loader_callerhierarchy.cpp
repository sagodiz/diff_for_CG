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
  
  vector<Record> tmpRecords;
  
  string line;
  string representation;
  
  while ( getline(input, line) ) {
    
    representation = line;
    
    if ( 0 == line.length() ) {
      //empty line
    }
    else {
      //caller or calle, but a node
      
      if ( '\t' == line[0] ) {
        
        line.erase(0, 1);
        representation.erase(0, 1);
      }
      else {
        
        line.erase(0, prefix.length());
        representation.erase(0, prefix.length());
      }
      
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
  
  bool changeCaller = false;
  
  string line;
  string caller;
  string callee;
  
  unsigned int callerId = -1;
  unsigned int calleeId = -1;
  
  while ( getline(input, line) ) {
    
    if ( 0 == line.length() ) {
      //empty line
    }
    else {
      //caller or calle, but a node so in a connection, set the 
      
      if ( '\t' == line[0] ) {
        
        line.erase(0, 1);
        callee = line;
      }
      else {
        
        line.erase(0, prefix.length());
        caller = line;
        changeCaller = true;
      }
      
      if ( changeCaller ) {
        //do nothing as here comes a new "list" os connections
      }
      else {
        //the remaining caller calls the callees
        bool check = false; //to check if the method do be found.
      
        for ( int i = 0; i < common::storedIds.size(); i++ ) {

          if ( common::storedIds[i] == caller ) {

            check = true;
            callerId = i;
            break;
          }
        }
        if ( !check ) {

          cerr << "Method couldn't be resolved: " << caller << endl;
        }

        check = false;
        for ( int i = 0; i < common::storedIds.size(); i++ ) {

          if ( common::storedIds[i] == callee ) {

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
    }
  }

  
  return connections;
}