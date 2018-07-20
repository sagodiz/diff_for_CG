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

      string representation;
      string pckgClass;
      string method;
      string infoMine;

      stringstream input_stringstream(line);
      getline(input_stringstream, representation, ' ');
      getline(input_stringstream, infoMine, ' ');

      infoMine.erase(0, 8); //[label=" --> 8 chars
      size_t ending = infoMine.rfind("\"]");
      if (ending != string::npos)
        infoMine.erase(ending);

      string pckgClassMethod;
      string paramsReturn;

      stringstream iss(infoMine);
      getline(iss, pckgClassMethod, '(');
      getline(iss, paramsReturn, '(');


      notFilteredMethodNames.insert(infoMine);

      //it is a node
      ++methodNum;

      size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes
      if (lastDotPos != string::npos) {

        method = pckgClassMethod.substr(lastDotPos + 1);
        pckgClass = pckgClassMethod.substr(0, lastDotPos);

      }
      else {

        throw Labels::METHOD_NOT_FOUND_ERROR;
      }

      vector<string> parameterVector;

      //delete everything after '(' as it is the return value
      size_t paramEnd = paramsReturn.rfind(")");
      if (paramEnd != string::npos) {

        paramsReturn.erase(paramEnd);
      }
      else {

        throw Labels::METHOD_PARAMETER_WRONG_FORMAT;
      }

      //split it on ';'
      stringstream paramStream(paramsReturn);
      string parameter;
      while ( getline(paramStream, parameter, ';') ) {

        parameterVector.push_back(parameter);
      }
      
      //TODO: transformations and stuff like that
      //TODO: create new record.


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