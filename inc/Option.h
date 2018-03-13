#ifndef OPTION_H
#define OPTION_H

#include <iostream>
#include <string>

class Option {
  
    std::string definer;
    void (*fooP)(char**,int);
  public:
    Option( std::string def, void (*fooA)(char**,int) );
    ~Option();
    void foo(char** argVector, int argIndex);
  
    bool operator==(const char* str) const;
};

#endif