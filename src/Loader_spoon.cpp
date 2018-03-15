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

	vector<Record> tmpRecords;  //TODO


	string line;
	getline(input, line); //get the "header" line
	getline(input, line); //get the "header" line

	while (getline(input, line)) {

		if (line.find("label=") != string::npos) {

			++methodNum;

			string representation;
			string pckgClass;
			string method;
			string infoMine;

			stringstream input_stringstream(line);
			getline(input_stringstream, representation, ' ');
			getline(input_stringstream, infoMine);

			infoMine.erase(0, 8); //[label=" --> 8 chars
			infoMine.erase(infoMine.length() - 2, 2); //"] at the end

			std::array<std::string, 2> trash{ "<cinit>", "<init>" };

			bool trashline = false;

			for (unsigned i = 0; i < trash.size(); ++i) {
				if (infoMine.find(trash[i]) != string::npos) {
					trashline = true;
					trashedIds.insert(representation);
					break;
				}
			}

			if (trashline) {
				continue;
			}

			std::string default_pck = "root.";
			if (infoMine.length() > default_pck.length() && infoMine.substr(0, default_pck.length()).compare(default_pck) == 0) {
				infoMine.erase(0, default_pck.length());
			}


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
			std::string delimiter = ",", generic_delimiter = " extends ";
			paramsReturn.erase(paramsReturn.length() - 1, 1); // )

			size_t pos = 0;
			std::string token;
			while ((pos = paramsReturn.find(delimiter)) != std::string::npos || paramsReturn.length() > 0) {
				token = paramsReturn.substr(0, pos);

				size_t generic_pos = token.find(generic_delimiter);
				if (generic_pos != string::npos) {
					token.erase(0, generic_pos + generic_delimiter.length());
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

			Record r(representation, pckgClass, method, parameterVector);
			tmpRecords.push_back(r);

			if (find(common::storedIds.begin(), common::storedIds.end(), r) == common::storedIds.end()) {
				//so this record is not found in the vector
				common::storedIds.push_back(r);
				++uniqueMethodNum;
			}
			else {

				auto it = find(common::storedIds.begin(), common::storedIds.end(), r);
				if (*it == representation) {
					//contains this representation
				}
				else {
					++uniqueMethodNum;
					*it += representation;  //add this representation
				}
			}

		}
	}


	input.clear();
	input.seekg(0, ios::beg);

	return tmpRecords;
}

set<pair<int, int>> Loader_spoon::transformConnections() {

	set<pair<int, int>> connections;

	string line;
	getline(input, line); //get the "header" line
	getline(input, line); //get the "header" line

	while (getline(input, line)) {

		if (line.find("label=") == string::npos && line[0] != '}') {
			//it is a connection
			++callNum;

			std::string delimiter = "->";
			size_t delimiter_pos = line.find(delimiter);
			string caller = line.substr(0, delimiter_pos);  //left part
			common::trim(caller);
			string callee = line.substr(delimiter_pos + delimiter.length());  //right part
			common::trim(callee);
			if (trashedIds.find(caller) != trashedIds.end() || trashedIds.find(callee) != trashedIds.end()) {
				continue;
			}

			int callerId = -1, calleeId = -1;

			if (!common::checkAndSetId(caller, callerId)) {
				common::checkAndSetId(caller, callerId);
				cerr << "Method couldn't be resolved: " << caller << endl;
			}

			if (!common::checkAndSetId(callee, calleeId)) {

				cerr << "Method couldn't be resolved: " << callee << endl;
			}

			connections.insert(pair<int, int>(callerId, calleeId));
		}
	}

	return connections;
}