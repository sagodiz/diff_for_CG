#include "../inc/Switch.h"

using namespace std;

Switch::Switch( string activationString, Factory& factory ) : definer(activationString), factory(factory) {
}

bool Switch::operator==( const string str ) const {
  
  if ( str == definer )
    return true;
  
  return false;
}

void Switch::init(string filePath) {
  
  //loader = factory.getLoaderPointer( definer, filePath );
	filenames.push_back(filePath);
}

bool Switch::operator==(const char* str ) const {
  
  if ( str == definer )
    return true;
  
  return false;
}

/*Loader& Switch::getLoader() const {
  
 // return *loader;
}*/

Loader* Switch::getLoaderPointer(unsigned counter) const {
  
  return factory.getLoaderPointer(definer, filenames[counter], counter);
}

//friend

ostream& operator<<( ostream& o, Switch s ) {
  
  o << s.definer;
  return o;
}