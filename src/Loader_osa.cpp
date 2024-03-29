#include "../inc/Loader_osa.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>


#ifdef OSA_DEBUG
  #define OSA_PRINT(a) cout << "Loaded osa: " << a << endl;
#else
  #define OSA_PRINT(a) ;
#endif

using namespace std;

Loader_osa::Loader_osa( string filepath, string name ) : Loader(filepath, name) {
}
Loader_osa::~Loader_osa() {
}

vector<Record> Loader_osa::load() {

cout << "OSA loader" << endl;
  
  
  
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
      getline(iss, pckgClassMethod , '(');
      getline(iss, paramsReturn , '(');


      notFilteredMethodNames.insert(infoMine);
      
      //it is a node
      ++methodNum;

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
      unsigned char arrayType = 0;
      
      while ( paramsReturn[i] != ')' ) {
        //process the params
        
        string typeStr = "";
        switch ( paramsReturn[i] ) {
          case '['://array
                  arrayType++;
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
                    while ( arrayType-- ) {
                      qualifiedClassname += '[';
                      qualifiedClassname += ']';
                    }
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
                  
                  arrayType = 0;
                  }
                  break;
          case 'D'://double
                  //.....
                  typeStr = "double";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'F'://float
                    //.....
                  typeStr = "float";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'J'://long
                    //.....
                  typeStr = "long";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'I'://int
                    //.....
                  typeStr = "int";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'S'://short
                  //.....
                  typeStr = "short";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'C'://char
                    //.....
                  typeStr = "char";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'B'://byte
                   //.....
                  typeStr = "byte";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'Z'://boolean
                   //.....
                  typeStr = "boolean";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
                  break;
          case 'V'://it is void
            /*
             //.....
                  typeStr = "void";
                  while ( arrayType-- ) {
                    typeStr += '[';
                    typeStr += ']';
                  }
                  parameterVector.push_back(typeStr);
                  
                  arrayType = 0;  //it's just for safety
            */
                  break;
          default: //throw a new exception
                  throw Labels::FORMAT_NOT_FOUND_ERROR;
        }
        
        ++i;
      } //end of while
      
      while( paramsReturn[i] != ':' ) {
        
        ++i;  //go to the first colon
      }
      ++i;
      
      string number = "";
      while( paramsReturn[i] != ':' ) {
        
        number += paramsReturn[i];
        ++i;
      }
      ++i;
      
      int startLine = atoi(number.c_str());
      
      while( paramsReturn[i] != ':' ) {
        
        ++i;  //pass the second number.
      }
      ++i;
      
      number = "";  //clear it.
      while( paramsReturn[i] != ':' ) {
        
        number += paramsReturn[i];
        ++i;
      }
      ++i;
      
      int endLine = atoi(number.c_str());
      
      
      
      if ( 0 == pckgClass.length() || 0 == method.length() )
        throw Labels::UNINITIALIZED_RECORD;
       
      if ( common::options::anonymClassNameTransform > 0 ) {
        //there is a kind of transformation
        if ( 1 == common::options::anonymClassNameTransform ) {
          //turn every anonym class into a constant anonym class
          common::unifyeAnonymClasses(pckgClass);
          common::unifyeAnonymMethods(method);
        }
        else {
          
          throw Labels::ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN;
        }
      }
   
      string pckgStr, classStr;
      common::cutPckgClass(pckgClass, pckgStr, classStr);
      
      Record r(pair<string, string>(representation, name), pckgStr, classStr, method, parameterVector, pair<string, string>(infoMine, name), startLine, endLine);
      if ( find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end() )  //put it only if not here
        tmpRecords.push_back( r );
      
      if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
        //so this record is not found in the vector
        common::storedIds.push_back(r);
        ++uniqueMethodNum;
      }
      else {

        auto it = find( common::storedIds.begin(), common::storedIds.end(), r );
        if ( *it == pair<string, string>(representation, name) ) {
          //contains this representation
        }
        else {
          ++uniqueMethodNum;
          *it += pair<string, string>(representation, name);  //add this representation
        }
      }
      OSA_PRINT(r)
      
    } //end of processing label
  }//end of processing line
  
  input.clear();
  input.seekg(0, ios::beg);
  
  printNotFilteredMethodNames();

  return tmpRecords;
}

set<pair<int, int>> Loader_osa::transformConnections() {

cout << "OSA transform" << endl;
  
  
  
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