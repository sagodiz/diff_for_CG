#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include "../inc/common.h"
#include <iostream>

using namespace std;

const std::set<std::string> Loader::excludes = { "java.", "sun.", "javax." };

Loader::Loader( string filepath, string name ) : filepath(filepath), methodNum(0), callNum(0), uniqueMethodNum(0), name(name) {
  
  input.open(filepath);
  if ( !input.is_open() )
    throw Labels::FILE_READ_ERROR + filepath;
}

Loader::~Loader() {
  
  input.close();
}


void Loader::printNotFilteredMethodNames() {
	std::ofstream of("non_filtered_methods_"+name);
	if (!of.is_open()) {
		return;
	}
	for (const auto& meth : notFilteredMethodNames) {
		of << meth << std::endl;
	}
	of.close();
}

bool Loader::isJavaLib(const std::string& method) {
	for (const std::string& anExclude : excludes) {
		if (method.find(anExclude) == 0) {
			return true;
		}
	}
	if (Labels::PROJECT_PATH.length() > 0 && method.find(Labels::PROJECT_PATH) != 0) {
		return true;
	}

	return false;
}

bool Loader::isExcludableInit(const std::string& name) {
	static const std::set<std::string> excludedInits = { "<init>", "<clinit>", "<initblock>" };
	for (const std::string& anExclude : excludedInits) {
		if (name.find(anExclude) != string::npos) {
			return true;
		}
	}
	return false;
}

bool Loader::isExclude(const std::string& method) {
	switch (common::options::filterLevel) {
	case 0:
		return false;
	case 1: 
		return isJavaLib(method);
	case 2: 
		return isJavaLib(method) || isExcludableInit(method);
	default: 
		return false;
	}


}

unsigned long long Loader::getMethodNum() const {
  
  return methodNum;
}
unsigned long long Loader::getCallNum() const {
  
  return callNum;
}

string Loader::getFilePath() {
  
  return filepath;
}

unsigned long long Loader::getUniqueMethodNum() const {
  
  return uniqueMethodNum;
}

string Loader::getName() const {
  
 return name; 
}

//friend
ostream& operator<<(ostream& o, Loader* l ) {
  
  o << l->filepath;
  return o;
}