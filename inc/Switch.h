#ifndef SWITCH_H
#define SWITCH_H

#include "Loader.h"
#include <iostream>

class Switch {
    std::string definer; //the switch string that activates this one
    Loader& loader; //this is going to be added to the loaders if the switch is activated
  public:
    Switch( std::string activationString, Loader& loader );
    bool operator==( const std::string str ) const; //returns true if the given string is the activation string for the object.
    bool operator==( const char* str ) const;
    Loader& getLoader() const;
    
    friend std::ostream& operator<<( std::ostream& o, Switch s );
  
};

#endif