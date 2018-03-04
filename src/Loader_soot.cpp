#ifdef DEBUG
#define DDD cout << "New record is added...: " << f_classWithPckg << " " << method << " " << endl;
#else 
#define DDD ;
#endif

#include "../inc/Loader_soot.h"
#include "../inc/common.h"

#include <set>
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

Loader_soot::Loader_soot( string filepath ) : Loader(filepath) {
}
Loader_soot::~Loader_soot() {
}

bool Loader_soot::load() {
  
  string line;
  getline(input, line); //get the "header" line
  
  while ( getline(input, line) ) {
    
    if ( line.find("->") == string::npos && line != "}" ) {
      //the line doesn't contains the "->" sub-string so it is not a caller-calle connection but a node
      
      string methodRepresentation = line; //save the line for representation
      
      line.erase(0, 6); //remove the '<4 spaces>"<' beginning
      line.erase(line.length()-2, 2); //remove the '">' ending
      
      //get the needed info. for a Record then algorithm::find(.., r) can be used...
     //----------------------------------------------------------------------------------------
     
      string f_classWithPckg, tmp, method;
      stringstream input_stringstream(line);

      getline(input_stringstream, f_classWithPckg , ' ');
      getline(input_stringstream, tmp , ' ');
      getline(input_stringstream, method , ' ');

      f_classWithPckg.erase(f_classWithPckg.length()-1, 1); //removing the ":"
      
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
      
      Record r(methodRepresentation, f_classWithPckg, method, parameterVector);
      
      if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
        //so this record is not found in the vector
DDD
        common::storedIds.push_back(r);
      }
      else {
        
        //this record is already in the vector nothing to do
      }
      
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