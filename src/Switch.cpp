#include "../inc/Switch.h"

using namespace std;

Switch::Switch( string activationString, Loader& loader ) : definer(activationString), loader(loader) {
}

bool Switch::operator==( const string str ) const {
  
  if ( str == definer )
    return true;
  
  return false;
}

bool Switch::operator==(const char* str ) const {
  
  if ( str == definer )
    return true;
  
  return false;
}

Loader& Switch::getLoader() const {
  
  return loader;
}

//friend

ostream& operator<<( ostream& o, Switch s ) {
  
  o << s.definer;
  return o;
}