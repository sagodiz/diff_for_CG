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
                  //.....
                  string qualifiedClassname;
                  
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
                  break;
          case 'D'://double
                  //.....
                  parameterVector.push_back("double");
                  arrayType = false;
                  break;
          case 'F'://float
                    //.....
                  parameterVector.push_back("float");
                  arrayType = false;
                  break;
          case 'J'://long
                    //.....
                  arrayType = false;
                  break;
          case 'I'://int
                    //.....
                  parameterVector.push_back("int");
                  arrayType = false;
                  break;
          case 'S'://short
                  //.....
                  parameterVector.push_back("short");
                  arrayType = false;
                  break;
          case 'C'://char
                    //.....
                  parameterVector.push_back("char");
                  arrayType = false;
                  break;
          case 'B'://byte
                   //.....
                  parameterVector.push_back("byte");
                  arrayType = false;
                  break;
          case 'Z'://boolean
                   //.....
                  parameterVector.push_back("boolean");
                  arrayType = false;
                  break;
          default://throw a new exception
                  throw Labels::FORMAT_NOT_FOUND_ERROR;
        }
        
        ++i;
        
      }
      
    }
  }
  
  return true;
}

set<pair<int, int>> Loader_sourcemeter::transformConnections() {
  
  set<pair<int, int>> connections;
  //TODO
  return connections;
}