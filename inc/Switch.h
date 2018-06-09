#ifndef SWITCH_H
#define SWITCH_H

#include "Loader.h"
#include "Factory.h"
#include <iostream>

class Switch {
    std::string definer; //the switch string that activates this one

  std::vector<std::string> filenames;
    Factory& factory;
  public:
    Switch( std::string activationString, Factory& f );
    void init(std::string filePath );
    bool operator==( const std::string str ) const; //returns true if the given string is the activation string for the object.
    bool operator==( const char* str ) const;
    Loader* getLoaderPointer(unsigned counter) const;
    
    friend std::ostream& operator<<( std::ostream& o, Switch s );
  
};

#endif