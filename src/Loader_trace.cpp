/*
* It is a tool for other comparisons. Was not used in static comparison.
*/


#include "../inc/Loader_trace.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

const std::string Loader_trace::entry_node = "ENTRY";

Loader_trace::Loader_trace(string filepath, string name) : Loader(filepath, name) {
  common::TRACE_RUN = true;
}
Loader_trace::~Loader_trace() {
}

bool Loader_trace::isTrace() const {
	return true;
}

vector<Record> Loader_trace::load() {

  vector<Record> tmpRecords;

  if(common::isTraceRun()){
	  //consider entry point as a node in case we compare trace to trace
	  Record r(pair<string, string>(entry_node, name), "", "", entry_node, {}, pair<string, string>(entry_node, name));
	  tmpRecords.push_back(r);

	  if (find(common::storedIds.begin(), common::storedIds.end(), r) == common::storedIds.end()) {
		  //so this record is not found in the vector
		  common::storedIds.push_back(r);
		  ++uniqueMethodNum;
	  }
	  else {

		  auto it = find(common::storedIds.begin(), common::storedIds.end(), r);
		  if (*it == pair<string, string>(entry_node, name)) {
			  //contains this representation
		  }
		  else {
			  *it += pair<string, string>(entry_node, name);  //add this representation
		  }
	  }
  }

  string line;
  getline(input, line); //get the "header" line
  //getline(input, line); //get the "header" line

  while (getline(input, line)) {

    if (line.find("label") != string::npos && line.compare("rankdir=\"LR\";") != 0) {

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
      if (infoMine.compare(entry_node) == 0) {
        //infoMine = "__trace.__entry()"; might be useful one day
        entry_representation = representation;
        continue;
      }

      notFilteredMethodNames.insert(infoMine);
      //it is a node
      ++methodNum;


      string pckgClassMethod;
      string paramsReturn;

      stringstream iss(infoMine);
      getline(iss, pckgClassMethod, '(');
      getline(iss, paramsReturn, '(');

      size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes
      if (lastDotPos != string::npos) {

        method = pckgClassMethod.substr(lastDotPos + 1);
        pckgClass = pckgClassMethod.substr(0, lastDotPos);

      }
      else {

        throw Labels::METHOD_NOT_FOUND_ERROR;
      }

      vector<string> parameterVector;
      unsigned int i = 0;
      unsigned char arrayType = 0;

      while (paramsReturn[i] != ')') {
        //process the params
        
        string typeStr = "";
        switch (paramsReturn[i]) {
        case '['://array
          arrayType++;
          break;
        case 'L'://class
        {
          //.....
          string qualifiedClassname;
          ++i;//get rid of the leading 'L'
          if (arrayType) {

            while (paramsReturn[i] != ';') {

              if (paramsReturn[i] == '/')
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

            while (paramsReturn[i] != ';') {

              if (paramsReturn[i] == '/')
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
        default: //throw a new exception
          throw Labels::FORMAT_NOT_FOUND_ERROR;
        }

        ++i;
      } //end of while

      if (0 == pckgClass.length() || 0 == method.length())
        throw Labels::UNINITIALIZED_RECORD;

      if (common::options::anonymClassNameTransform > 0) {
        //there is a kind of transformation
        if (1 == common::options::anonymClassNameTransform) {
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
      
      Record r(pair<string, string>(representation, name), pckgStr, classStr, method, parameterVector, pair<string, string>(infoMine, name));
      if (find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end())  //put it only if not here
        tmpRecords.push_back(r);

      if (find(common::storedIds.begin(), common::storedIds.end(), r) == common::storedIds.end()) {
        //so this record is not found in the vector
        common::storedIds.push_back(r);
        ++uniqueMethodNum;
      }
      else {

        auto it = find(common::storedIds.begin(), common::storedIds.end(), r);
        if (*it == pair<string, string>(representation, name)) {
          //contains this representation
        }
        else {
          ++uniqueMethodNum;
          *it += pair<string, string>(representation, name);  //add this representation
        }
      }
    } //end of processing label
  }//end of processing line

  input.clear();
  input.seekg(0, ios::beg);

  printNotFilteredMethodNames();

  return tmpRecords;
}

set<pair<int, int>> Loader_trace::transformConnections() {

  set<pair<int, int>> connections;

  string line;
  getline(input, line); //get the "header" line
  getline(input, line); //get the "header" line

  while (getline(input, line)) {

	std::string delimiter = "->";

    if (line.find("label") == string::npos && line.find(delimiter) != string::npos) {


      
      size_t delimiter_pos = line.find(delimiter);
      string caller = line.substr(0, delimiter_pos);  //left part
      common::trim(caller);

      if ((caller == entry_representation || caller == entry_node) && !common::isTraceRun()) {
        continue;
      }

      string callee = line.substr(delimiter_pos + delimiter.length());  //right part
      common::trim(callee);
	  if (callee[callee.length() - 1] == ';') {
		  callee = callee.substr(0, callee.length() - 1);
	  }

      //it is a connection
      ++callNum;

      int callerId = -1, calleeId = -1;

      bool check = false; //to check if the method do be found.

      for (unsigned i = 0; i < common::storedIds.size(); i++) {

        if (common::storedIds[i] == pair<string, string>(caller, name)) {

          check = true;
          callerId = i;
          break;
        }
      }
      if (!check) {

        cerr << "Method couldn't be resolved: " << caller << endl;
      }

      check = false;
      for (unsigned i = 0; i < common::storedIds.size(); i++) {

        if (common::storedIds[i] == pair<string, string>(callee, name)) {

          check = true;
          calleeId = i;
          break;
        }
      }
      if (!check) {

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