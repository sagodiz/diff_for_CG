#include "../inc/Record.h"

using namespace std;

Record::Record( string package, string methodClass, string methodName, vector<string> parameters ) : package(package), methodClass(methodClass), methodName(methodName), parameters(parameters) {
}

bool Record::operator==(const Record& r ) const {
  
  if ( r.getPackage() == package
      && r.getClass() == methodClass
      && r.getMethodName() == methodName
      && r.getParameters() == parameters
      ) {
    
    return true;
  }
  return false;
}

Record& Record::operator+( const string nWOR ) {
  
  parameters.push_back(nWOR);
  
  return *this;
}

string Record::getPackage() const {
  
  return package;
}
string Record::getClass() const {
  
  return methodClass;
}
string Record::getMethodName() const {
  
  return methodName;
}
vector<string> Record::getParameters() const {
  
  return parameters;
}