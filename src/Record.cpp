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

Record::Record( string rep, string methodClass, string methodName, vector<string> parameters ) : methodClass(methodClass), methodName(methodName), parameters(parameters) {
  sameMethods.push_back(rep);
}

//-----------------------------For those where rep is not the line but an ID e.g. SourceMeter---------------------------------------
Record::Record( string rep, string methodClass, string methodName, vector<string> parameters, string secondaryRep ) : methodClass(methodClass), methodName(methodName), parameters(parameters), secondaryRep(secondaryRep) {
  sameMethods.push_back(rep);
}
//----------------------------------------------------------------------------------------------------------------
bool Record::operator==(const Record& r ) const {

DDD

  if ( r.getClass() == methodClass
      && r.getMethodName() == methodName
      && r.getParameters() == parameters
      ) {
        
    return true;
  }
  return false;
}

bool Record::operator==( const string method ) const {
  
  if ( find( sameMethods.begin(), sameMethods.end(), method ) != sameMethods.end() ) {

    return true;
  }
  
  return false;
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

Record& Record::operator+=( const string nWOR ) {
  
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
vector<string> Record::getSameMethods() const {
  
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
  
  return o;
}