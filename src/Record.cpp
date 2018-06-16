#ifdef DEBUG
#define DDD cout << "records are compared...: " << endl; \\
  cout << "records compared " << r << "and:" << *this << endl;

#else
#define DDD ;  
#endif

#include "../inc/Record.h"

#include <algorithm>
#include <iostream>

using namespace std;



string Record::createUnifiedMethodName() {

  string params = "";
  auto parameters = getParameters();
  for (unsigned i = 0; i < parameters.size(); i++) {

    params += parameters[i] + ",";
  }
  //params.erase(params.length() - 1, 1); //the closing ','
  if (params.length() > 0 && ',' == params[params.length() - 1])
    params[params.length() - 1] = ')';
  else
    params += ")";
  return getClass() + "." + getMethodName() + "(" + params;// + ")";
}



//----------------------------------------------public methods----------------------------------------------------

Record::Record( pair<string, string> rep, string methodClass, string methodName, vector<string> parameters ) : methodClass(methodClass), methodName(methodName), parameters(parameters) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();
}

//-----------------------------For those where rep is not the line but an ID e.g. SourceMeter---------------------------------------
Record::Record( pair<string, string> rep, string methodClass, string methodName, vector<string> parameters, string secondaryRep ) : methodClass(methodClass), methodName(methodName), parameters(parameters), secondaryRep(secondaryRep) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();
}
//----------------------------------------------------------------------------------------------------------------
bool Record::operator==(const Record& r ) const {

DDD
//TODO: ha meglesz az unifiedRep, elég lesz azt összevetni
  if ( r.getClass() == methodClass
      && r.getMethodName() == methodName
      && r.getParameters() == parameters
      ) {
        
    return true;
  }
  return false;
}

bool Record::operator==( const pair<string, string> method ) const {
  
  if ( find( sameMethods.begin(), sameMethods.end(), method ) != sameMethods.end() ) {

    return true;
  }
  
  return false;
}

bool Record::operator==(const string& unifiedNode) const {

  bool found = false;
  if ( unifiedNode == unifiedRep )
    found = true;
  
  return found;
}

bool Record::operator>>=(const Record& r ) const {

DDD
//TODO: ha meglesz az unifiedRep rendesen, akkor elég lesz azt összevetni
  string classStr = r.getClass();
  replace( classStr.begin(), classStr.end(), '$', '.'); // replace all '$' to '.'

  if ( classStr == methodClass
      && r.getMethodName() == methodName
      && r.getParameters() == parameters
      ) {
        
    return true;
  }
  return false;
}

Record& Record::operator+=( const pair<string, string> nWOR ) {
  
  sameMethods.push_back(nWOR);
  
  return *this;
}

Record& Record::operator+=( const Record& r ) {
  
  
  if ( *this == r ) {
    
    for ( auto it = r.getSameMethods().begin(); it != r.getSameMethods().end(); ++it ) {
      
      sameMethods.push_back(*it);
    }
  }
  
  return *this;
}

bool Record::operator<( const Record& r ) const {
  
  if ( r.getClass().length() < methodClass.length() )
    return true;
  
  return false;
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
vector<pair<string, string>> Record::getSameMethods() const {
  
  return sameMethods;
}

string Record::getSecondaryRepresentation() const {
  
  return secondaryRep;
}


//friend
ostream& operator<<(ostream& o, const Record& r) {
      
  o << r.methodClass << "|" << r.methodName << "|";
  for ( auto it : r.parameters ) {
    
    o << it << "|";
  }
  //o << r.unifiedRep;  okay, ez lesz majd, de az csak egy újabb refaktorálás után! Konstruktorban legyen a unified Összerakása
  
  return o;
}