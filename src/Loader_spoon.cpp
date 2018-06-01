//TODO: sorvégek!!!! most éppen jó. SPOON windows-os sorvéggel dolgozik

#include "../inc/Loader_spoon.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <array>

using namespace std;

Loader_spoon::Loader_spoon(string filepath, string name) : Loader(filepath, name) {
}
Loader_spoon::~Loader_spoon() {
}

vector<Record> Loader_spoon::load() {

	vector<Record> tmpRecords;


	string line;
	getline(input, line); //get the "header" line
	getline(input, line); //get the "header" line

	while (getline(input, line)) {

		if (line.find("label=") != string::npos) {

			string representation;
			string pckgClass;
			string className;
			string method;
			string infoMine;

			stringstream input_stringstream(line);
			getline(input_stringstream, representation, ' ');
			getline(input_stringstream, infoMine);

			infoMine.erase(0, 8); //[label=" --> 8 chars
			size_t ending = infoMine.rfind("\"]");
			if (ending != string::npos)
				infoMine.erase(ending);


			std::string default_pck = "root.";
			if (infoMine.length() > default_pck.length() && infoMine.substr(0, default_pck.length()).compare(default_pck) == 0) {
				infoMine.erase(0, default_pck.length());
			}




			string pckgClassMethod;
			string paramsReturn;

			stringstream iss(infoMine);
			getline(iss, pckgClassMethod, '(');
			getline(iss, paramsReturn, '(');


			if (Loader::isExclude(pckgClassMethod)) {
				excludedIds.insert(representation);
				continue;
			}
			else {
				notFilteredMethodNames.insert(infoMine);
			}

			//it is a node
			++methodNum;

			size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes
			if (lastDotPos != string::npos) {

				method = pckgClassMethod.substr(lastDotPos + 1);
				pckgClass = pckgClassMethod.substr(0, lastDotPos);


				lastDotPos = pckgClass.rfind(".");
				if (lastDotPos != string::npos) {
					className = pckgClass.substr(lastDotPos + 1);
				}
				else {
					className = pckgClass;
				}


			}
			else {

				throw Labels::METHOD_NOT_FOUND_ERROR;
			}

			if (className.compare(method) == 0) {
				method = "<init>";
			}

			vector<string> parameterVector;
			std::string delimiter = ",", generic_delimiter = " extends ";

			size_t close_pos = paramsReturn.rfind(")");
			if (close_pos != string::npos)
				paramsReturn.erase(close_pos); // )


			size_t pos = 0;
			std::string token;
			while ((pos = paramsReturn.find(delimiter)) != std::string::npos || paramsReturn.length() > 0) {
				token = paramsReturn.substr(0, pos);

				size_t generic_pos = token.find(generic_delimiter);
				if (generic_pos != string::npos) {
					token.erase(0, generic_pos + generic_delimiter.length());
				}
				if (token.length() == 1) {//generikus parameterek
					token = "java.lang.Object";
				}
				else if (token.length() == 3 && token.substr(1).compare("[]") == 0) {
					token = "java.lang.Object[]";
				}

				parameterVector.push_back(token);
				if (pos == std::string::npos) {
					break;
				}
				else {
					paramsReturn.erase(0, pos + delimiter.length());
				}

			}



			if (0 == pckgClass.length() || 0 == method.length())
				throw Labels::UNINITIALIZED_RECORD;

      
      if ( common::options::anonymClassNameTransform > 0 ) {
        //there is a kind of transformation
        if ( 1 == common::options::anonymClassNameTransform ) {
          //turn every anonym class into a constant anonym class
          common::unifyeAnonymClasses(pckgClass);
        }
        else if ( 2 == common::options::anonymClassNameTransform ) {
          //continue numbering in inner anonym classes
          //TODO!!! 
        }
        else {
          
          throw Labels::ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN;
        }
      }
      
			Record r(pair<string, string>(representation, "spoon"), pckgClass, method, parameterVector, infoMine);
      if ( find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end() )  //put it only if not here
        tmpRecords.push_back(r);

			if (find(common::storedIds.begin(), common::storedIds.end(), r) == common::storedIds.end()) {
				//so this record is not found in the vector
				common::storedIds.push_back(r);
				++uniqueMethodNum;
			}
			else {

				auto it = find(common::storedIds.begin(), common::storedIds.end(), r);
				if (*it == pair<string, string>(representation, "spoon") ) {
					//contains this representation
				}
				else {
					++uniqueMethodNum;
					*it += pair<string, string>(representation, "spoon");  //add this representation
				}
			}

		}
	}


	input.clear();
	input.seekg(0, ios::beg);

	printNotFilteredMethodNames();

	return tmpRecords;
}

set<pair<int, int>> Loader_spoon::transformConnections() {

	set<pair<int, int>> connections;

	string line;
	getline(input, line); //get the "header" line
	getline(input, line); //get the "header" line

	while (getline(input, line)) {

		if (line.find("label=") == string::npos && line[0] != '}') {

			std::string delimiter = "->";
			size_t delimiter_pos = line.find(delimiter);
			string caller = line.substr(0, delimiter_pos);  //left part
			common::trim(caller);
			string callee = line.substr(delimiter_pos + delimiter.length());  //right part
			common::trim(callee);

			if (excludedIds.find(caller) != excludedIds.end() || excludedIds.find(callee) != excludedIds.end()) {
				continue;
			}

			//it is a connection
			++callNum;

			int callerId = -1, calleeId = -1;

			if (!common::checkAndSetId(caller, callerId, "spoon")) {
				common::checkAndSetId(caller, callerId, "spoon");
				cerr << "Method couldn't be resolved: " << caller << endl;
			}

			if (!common::checkAndSetId(callee, calleeId, "spoon")) {

				cerr << "Method couldn't be resolved: " << callee << endl;
			}

			connections.insert(pair<int, int>(callerId, calleeId));
		}
	}

	return connections;
}