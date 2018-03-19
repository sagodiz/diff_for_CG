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
  string member1, member2;
  
  while( input >> member1 >> member2 ) {
    
    string pckgClassMethod = member1;
    pckgClassMethod.erase(0, 2);  //erase "M:"
    
    string f_classWithPckg;
    string method;
    stringstream input_stringstream(pckgClassMethod);
    getline(input_stringstream, f_classWithPckg , ':');
    getline(input_stringstream, method, ':');
    
    
    string parameters = method.substr(method.find("("));
    method.erase(method.find("("), method.length()-method.find("("));
    parameters.erase(parameters.length()-1, 1);
    parameters.erase(0,1);

    //cut apart parameters
    vector<string> parameterVector;
    stringstream iss(parameters);
    string parameter;
    while( getline(iss, parameter, ',') ) {

      parameterVector.push_back(parameter);
    }
    
    Record r(member1, f_classWithPckg, method, parameterVector);
    tmpRecords.push_back( r );
    
  if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
      //so this record is not found in the vector
      ++uniqueMethodNum;
      common::storedIds.push_back(r);
    }
    else {

      auto it = find( common::storedIds.begin(), common::storedIds.end(), r );
      if ( *it == member1 ) {
        //contains this representation
      }
      else {

        *it += member1;  //add this representation
        ++uniqueMethodNum;
      }
    }
    
    //here comes the next node in the line
    string pckgClassMethod2 = member2;
    pckgClassMethod2.erase(0, 3);  //erase "(.)"
    
    string f_classWithPckg2;
    string method2;
    stringstream input_stringstream2(pckgClassMethod2);
    getline(input_stringstream2, f_classWithPckg2, ':');
    getline(input_stringstream2, method2, ':');
    
    
    string parameters2 = method2.substr(method2.find("("));
    method2.erase(method2.find("("), method2.length()-method2.find("("));
    parameters2.erase(parameters2.length()-1, 1);
    parameters2.erase(0,1);

    //cut apart parameters
    vector<string> parameterVector2;
    stringstream iss2(parameters2);
    string parameter2;
    while( getline(iss2, parameter2, ',') ) {

      parameterVector2.push_back(parameter2);
    }
    
    Record r2(member2, f_classWithPckg2, method2, parameterVector2);
    tmpRecords.push_back( r2 );

    if ( find( common::storedIds.begin(), common::storedIds.end(), r2 ) == common::storedIds.end() ) {
      //so this record is not found in the vector
      ++uniqueMethodNum;
      common::storedIds.push_back(r2);
    }
    else {

      auto it = find( common::storedIds.begin(), common::storedIds.end(), r2 );
      if ( *it == member2 ) {
        //contains this representation
      }
      else {

        *it += member2;  //add this representation
        ++uniqueMethodNum;
      }
    }
  }
  
  input.clear();
  input.seekg(0, ios::beg);
  
  return tmpRecords;
}

set<pair<int, int>> Loader_gousiosg::transformConnections() {
  
  set<pair<int, int>> connections;  //TODO
  
  
  return connections;
}