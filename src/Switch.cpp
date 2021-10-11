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
  
  filenames.push_back(filePath);
}

int Switch::init(char** parameters, int index ) {
  
  int alter_index = 1;
  std::string param1 = parameters[index + alter_index];
  
  if ( param1[0] == ':' ) {
    // name it
    nameToLoader = param1.substr(1);
    ++alter_index;
  }

  std::string filePath = parameters[index + (alter_index++)];
  filenames.push_back(filePath);

  return alter_index;
}

bool Switch::operator==(const char* str ) const {
  
  if ( str == definer )
    return true;

  return false;
}


Loader* Switch::getLoaderPointer(unsigned counter) const {
  Loader* rv = factory.getLoaderPointer(definer, filenames[counter], counter);
  if ( !nameToLoader.empty() ) {
    rv->set_name(nameToLoader);
    nameToLoader = ""; // if the name is used empty it as the next loader may have no name.
  }
  return rv;
}

//friend
ostream& operator<<( ostream& o, Switch s ) {
  
  o << s.definer;
  return o;
}