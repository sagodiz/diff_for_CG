#ifdef DEBUG
#define DDD cout << "records are compared...: " << endl; \
  cout << "records compared " << r << "and:" << *this << endl;

#else
#define DDD ;  
#endif

#ifdef DEBUGINFO
  #define DEBUG_EQUALITY cout << *this << " equals to " << r << endl;
#else
  #define DEBUG_EQUALITY ;
#endif

#ifdef DEBUGINFO
  #define DEBUG_COMPARE cout << *this << " is equals? " << r << endl;
#else
  #define DEBUG_COMPARE ;
#endif


#include "../inc/Record.h"
#include "../inc/common.h"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

bool anonym( string str ) {

  //an anonym is a number.
  for ( unsigned int i = 0; i < str.length(); i++ ) {

    if ( str[i] > '9' || str[i] < '0' )
    return false;
  }

  return true;
}


bool inner(string str) {

  stringstream input_stringstream(str);
  string part;
  cout << "being checked: " << str << endl;
  while ( getline(input_stringstream, part , '$') ) {

    if ( anonym(part) ) //if there is a total number part(an anonym) it is an anonym
      return true;
  }

  cout << "false" << endl;

  return false;
}

bool anonymEqual( string str, string str2 ) {
  
  bool isAnonym = false;
  vector<string> parts1;
  vector<string> parts2;
  string part;

  stringstream input_stringstream(str);

  while ( getline(input_stringstream, part , '$') ) {

    parts1.push_back(part);
  }

  stringstream input_stringstream2(str2);

  while ( getline(input_stringstream2, part , '$') ) {

    parts2.push_back(part);
  }

  if ( parts1.size() != parts2.size() )
    return false;

  for ( unsigned int i = 0; i < parts1.size(); i++ ) {

    if ( ( anonym(parts1[i]) && anonym(parts2[i]) ) || parts1[i] == parts2[i] ) {

      //everything is similar
    }
    else {
      //might not be equal
      return false;
    }

    return true;
  }

  return isAnonym;
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
  return getPackage() + "." + getClass() + "." + getMethodName() + "(" + params;// + ")";
}



//----------------------------------------------public methods----------------------------------------------------

Record::Record( pair<string, string> rep, string package, string methodClass, string methodName, vector<string> parameters, int startLine, int endLine ) : package(package), methodClass(methodClass), methodName(methodName), parameters(parameters), startLine(startLine), endLine(endLine) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();

  if ( -1 != startLine && -1 == endLine ) {

    this->endLine = startLine;
  }
}

//-----------------------------For those where rep is not the line but an ID e.g. SourceMeter---------------------------------------
Record::Record( pair<string, string> rep, string package, string methodClass, string methodName, vector<string> parameters, string secondaryRep, int startLine, int endLine ) : package(package), methodClass(methodClass), methodName(methodName), parameters(parameters), secondaryRep(secondaryRep), startLine(startLine), endLine(endLine) {
  sameMethods.push_back(rep);
  unifiedRep = createUnifiedMethodName();
  
  if ( -1 != startLine && -1 == endLine ) {
    
    this->endLine = startLine;
  }
}
//----------------------------------------------------------------------------------------------------------------
bool Record::operator==(const Record& r ) const {

DDD
  if ( r.unifiedRep == unifiedRep )
    return true;
  
  bool isEquals = false;

  if ( common::options::lineInfoPairing ) {
    
    if ( r.package == package && //the same package. It must not differ!
        ( anonymEqual(methodClass, r.methodClass) ) &&  //class names are the same or both of them is anonym
        ( anonymEqual(methodName, r.methodName) ) ) {  //the same method or both of them is anonym.
         cout << "------------------------------------------------------------------------" << endl;
//DEBUG_COMPARE
      if ( (!inner(methodClass) && !inner(methodName) && parameters.size() == r.parameters.size()) || parameters == r.parameters ) {   //if it is an anonym method (the other must be too, have to compare parameters too!)
       //if it is an inner, the first part is false so have to check the equality of the parameters
       //if it is not an inner, it is false, so the expr. is true so no need for checking param equality as generics may be differenit in params
        
        cout << (parameters == r.parameters) << endl;
        if ( startLine == -1 && r.startLine != -1 ) {
          isEquals = true;  //if one of them is without lineinfo but everything is matching it means it is a generic or anonym...
  DEBUG_EQUALITY
        }
        if ( r.startLine == -1 && startLine != -1 ) {
          isEquals = true;
  DEBUG_EQUALITY
        }
        if ( startLine != -1 && //this is a real information
          ( (startLine <= r.startLine && endLine >= r.endLine) || (startLine >= r.startLine && endLine <= r.endLine) ) //a total interception, a in b or b in a
          ) {
          isEquals = true;
  DEBUG_EQUALITY
        }
      }
    }
  }
  
  return isEquals;
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
vector<pair<string, string>> Record::getSameMethods() const {
  
  return sameMethods;
}

string Record::getSecondaryRepresentation() const {
  
  return secondaryRep;
}


//friend
ostream& operator<<(ostream& o, const Record& r) {
  
  o << r.unifiedRep;
#ifdef DEBUG_LINEINFO
  o << " lineinfo: " << r.startLine << " " << r.endLine;
#endif
  
  return o;
}