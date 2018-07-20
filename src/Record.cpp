#ifdef DEBUG
#define DDD cout << "records are compared...: " << endl; \\
  cout << "records compared " << r << "and:" << *this << endl;

#else
#define DDD ;  
#endif

#include "../inc/Record.h"
#include "../inc/common.h"

#include <algorithm>
#include <iostream>

using namespace std;

bool contains_number( string str ) {
  
  return (
        str.find('0') != string::npos ||
        str.find('1') != string::npos ||
        str.find('2') != string::npos ||
        str.find('3') != string::npos ||
        str.find('4') != string::npos ||
        str.find('5') != string::npos ||
        str.find('6') != string::npos ||
        str.find('7') != string::npos ||
        str.find('8') != string::npos ||
        str.find('9') != string::npos
    );
}



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

Record::Record( pair<string, string> rep, string methodClass, string methodName, vector<string> parameters, int lineinfo ) : methodClass(methodClass), methodName(methodName), parameters(parameters), lineinfo(lineinfo) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();
}

//-----------------------------For those where rep is not the line but an ID e.g. SourceMeter---------------------------------------
Record::Record( pair<string, string> rep, string methodClass, string methodName, vector<string> parameters, string secondaryRep, int lineinfo ) : methodClass(methodClass), methodName(methodName), parameters(parameters), secondaryRep(secondaryRep), lineinfo(lineinfo) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();
}
//----------------------------------------------------------------------------------------------------------------
bool Record::operator==(const Record& r ) const {

DDD

  /*if ( r.getClass() == methodClass
      && r.getMethodName() == methodName
      && r.getParameters() == parameters
      ) {
        
    return true;
  }*/
  
  //If the two is totally the same, it is obvious
  if ( r.unifiedRep == unifiedRep )
    return true;
  
  if ( common::options::lineInfoPairing ) {
    if ( ( r.methodClass == methodClass || ( contains_number(r.methodClass) && contains_number(methodClass) ) ) &&  //class names are the same or both of them is anonym
        ( r.methodName == methodName || ( contains_number(r.methodName) && contains_number(methodName) ) ) &&  //the same method or both of them is anonym.
        ( r.parameters.size() == parameters.size() ) ) {  //same number of parameters.
      if ( lineinfo == -1 && r.lineinfo != -1 )
        return true;  //if one of them is without lineinfo but everything is matching it means it is a generic or anonym...
      if ( r.lineinfo == -1 && lineinfo != -1 )
        return true;
      if ( lineinfo != -1 && lineinfo == r.lineinfo )
        return true;
    }
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
      
  /*o << r.methodClass << "|" << r.methodName << "|";
  for ( auto it : r.parameters ) {
    
    o << it << "|";
  }*/
  o << r.unifiedRep;
#ifdef DEBUGINFO
  o << " lineinfo: " << r.lineinfo;
#endif
  
  return o;
}