#include "../inc/Loader_gousiosg.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

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
    
    methodNum += 2; //as it has 2 methods in a row
    
    string pckgClassMethod = member1;
    member1.erase(0,2);
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
    
    
    if ( common::options::anonymClassNameTransform > 0 ) {
      //there is a kind of transformation
      if ( 1 == common::options::anonymClassNameTransform ) {
        //turn every anonym class into a constant anonym class
        common::unifyeAnonymClasses(f_classWithPckg);
        common::unifyeAnonymMethods(method);
      }
      else if ( 2 == common::options::anonymClassNameTransform ) {
        //continue numbering in inner anonym classes
        //TODO!!! 
      }
      else {
        
        throw Labels::ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN;
      }
    }
 
    Record r(pair<string, string>(member1, "gous"), f_classWithPckg, method, parameterVector);
    if ( find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end() )  //put it only if not here
      tmpRecords.push_back( r );
    
  if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
      //so this record is not found in the vector
      ++uniqueMethodNum;
    //cout << r << "??" << member1 << endl;
      common::storedIds.push_back(r);
    }
    else {

      auto it = find( common::storedIds.begin(), common::storedIds.end(), r );
      if ( *it == pair<string, string>(member1, "gous") ) {
        //contains this representation
      }
      else {

        *it += pair<string, string>(member1, "gous");  //add this representation
        ++uniqueMethodNum;
        //cout << r << "?" << member1 << endl;
      }
    }
    
    //here comes the next node in the line
    string pckgClassMethod2 = member2;
    member2.erase(0,3);
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
    
    if ( common::options::anonymClassNameTransform > 0 ) {
      //there is a kind of transformation
      if ( 1 == common::options::anonymClassNameTransform ) {
        //turn every anonym class into a constant anonym class
        common::unifyeAnonymClasses(f_classWithPckg2);
        common::unifyeAnonymMethods(method2);
      }
      else if ( 2 == common::options::anonymClassNameTransform ) {
        //continue numbering in inner anonym classes
        //TODO!!! 
      }
      else {
        
        throw Labels::ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN;
      }
    }
      
    Record r2(pair<string, string>(member2, "gous"), f_classWithPckg2, method2, parameterVector2);
    if ( find(tmpRecords.begin(), tmpRecords.end(), r2) == tmpRecords.end() )  //put it only if not here
      tmpRecords.push_back( r2 );

    if ( find( common::storedIds.begin(), common::storedIds.end(), r2 ) == common::storedIds.end() ) {
      //so this record is not found in the vector
      ++uniqueMethodNum;
      //cout << r2 << "!" << member2 << endl;
      common::storedIds.push_back(r2);
    }
    else {

      auto it = find( common::storedIds.begin(), common::storedIds.end(), r2 );
      if ( *it == pair<string, string>(member2, "gous") ) {
        //contains this representation
      }
      else {
//cout << r2 << "!!" << member2 << endl ;
        *it += pair<string, string>(member2, "gous");  //add this representation
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
  
  string member1, member2;
  
  while ( input >> member1 >> member2 ) {
    
    member1.erase(0,2);
    member2.erase(0,3);
    
    ++callNum;
    string caller = member1;
    string callee = member2;
    int callerId = -1, calleeId = -1;
    bool check = false;
    
    for (unsigned i = 0; i < common::storedIds.size(); i++ ) {

      if ( common::storedIds[i] == pair<string, string>(caller, "gous") ) {

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

      if ( common::storedIds[i] == pair<string, string>(callee, "gous") ) {

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
  
  return connections;
}
