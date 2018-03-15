#include "../inc/Loader_sourcemeter.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

Loader_sourcemeter::Loader_sourcemeter( string filepath, string name ) : Loader(filepath, name) {
}
Loader_sourcemeter::~Loader_sourcemeter() {
}

vector<Record> Loader_sourcemeter::load() {

  vector<Record> tmpRecords;  //TODO
  
  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line
  
  while ( getline(input, line) ) {
    
    if ( line.find("label") != string::npos ) {
      //it is a node
      ++methodNum;
      
      string representation;
      string pckgClass;
      string method;
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
        
        method = pckgClassMethod.substr(lastDotPos + 1);
        pckgClass = pckgClassMethod.substr(0, lastDotPos);
        
      }
      else {

        throw Labels::METHOD_NOT_FOUND_ERROR;
      }
      
      vector<string> parameterVector;
      unsigned int i = 0;
      bool arrayType = false;
      
      while ( paramsReturn[i] != ')' ) {
        //process the params
        switch ( paramsReturn[i] ) {
          case '['://array
                  arrayType = true;
                  break;
          case 'L'://class
                  {
                  //.....
                  string qualifiedClassname;
                  ++i;//get rid of the leading 'L'
                  if ( arrayType ) {
                    
                    while( paramsReturn[i] != ';' ) {
                      
                      if ( paramsReturn[i] == '/' )
                        qualifiedClassname += '.';
                      else
                        qualifiedClassname += paramsReturn[i];
                      
                      ++i;
                    }
                    qualifiedClassname += '[';
                    qualifiedClassname += ']';
                  }
                  else {
                    
                    while( paramsReturn[i] != ';' ) {
                      
                      if ( paramsReturn[i] == '/' )
                        qualifiedClassname += '.';
                      else
                        qualifiedClassname += paramsReturn[i];
                      
                      ++i;
                    }
                  }
            
                  parameterVector.push_back(qualifiedClassname);
                  
                  arrayType = false;
                  }
                  break;
          case 'D'://double
                  //.....
                  if ( arrayType )
                    parameterVector.push_back("double[]");
                  else
                    parameterVector.push_back("double");
                  
                  arrayType = false;
                  break;
          case 'F'://float
                    //.....
                  if ( arrayType )
                    parameterVector.push_back("float[]");
                  else
                    parameterVector.push_back("float");
                  arrayType = false;
                  break;
          case 'J'://long
                    //.....
                  if ( arrayType )
                    parameterVector.push_back("long[]");
                  else
                    parameterVector.push_back("long");
                  arrayType = false;
                  break;
          case 'I'://int
                    //.....
                  if ( arrayType )
                    parameterVector.push_back("int[]");
                  else
                    parameterVector.push_back("int");
                  arrayType = false;
                  break;
          case 'S'://short
                  //.....
                  if ( arrayType )
                    parameterVector.push_back("short[]");
                  else
                    parameterVector.push_back("short");
                  arrayType = false;
                  break;
          case 'C'://char
                    //.....
                  if ( arrayType )
                    parameterVector.push_back("char[]");
                  else
                    parameterVector.push_back("char");
                  arrayType = false;
                  break;
          case 'B'://byte
                   //.....
                  if ( arrayType )
                     parameterVector.push_back("byte[]");
                  else
                    parameterVector.push_back("byte");
                  arrayType = false;
                  break;
          case 'Z'://boolean
                   //.....
                  if ( arrayType )
                    parameterVector.push_back("boolean[]");
                  else
                    parameterVector.push_back("boolean");
                  arrayType = false;
                  break;
          default: //throw a new exception
                  throw Labels::FORMAT_NOT_FOUND_ERROR;
        }
        
        ++i;
      } //end of while
      
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
    } //end of processing label
  }//end of processing line
  
  input.clear();
  input.seekg(0, ios::beg);
  
  return tmpRecords;
}

set<pair<int, int>> Loader_sourcemeter::transformConnections() {

  set<pair<int, int>> connections;

  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line

  while ( getline(input, line) ) {
    
  if ( line.find("label") == string::npos && line[0] != '}' ) {
      //it is a connection
      ++callNum;
      
	  std::string delimiter = "->";
	  size_t delimiter_pos = line.find(delimiter);
	  string caller = line.substr(0, delimiter_pos);  //left part
	  common::trim(caller);
	  string callee = line.substr(delimiter_pos + delimiter.length());  //right part
	  common::trim(callee);
      
      int callerId = -1, calleeId = -1;
      
      bool check = false; //to check if the method do be found.
      
      for (unsigned i = 0; i < common::storedIds.size(); i++ ) {
        
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
      for (unsigned i = 0; i < common::storedIds.size(); i++ ) {
        
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
    else {
      //do nothing
    }
  }

  return connections;
}