#ifndef LOADER_H
#define LOADER_H

#include "Record.h"
#include<fstream>
#include <iostream>
#include<set>

class Loader {
  
    std::string filepath;
  
  protected:
    std::ifstream input;
    unsigned long long methodNum;
    unsigned long long callNum;
  
  public:
    Loader( std::string filepath );
    
    /**
    * Loads the nodes to the method store, if no matching method is found creates a new one with a new id
    */
    virtual std::set<Record> load() = 0;
  
    /**
    * Uses the ids (ones that is used by every other tool) instead of it's own method names
    * @return Returns a set of connections a connection is represented as a pair<caller, calle>
    */
    virtual std::set<std::pair<int, int>> transformConnections() = 0;
  
    virtual ~Loader();
  
    unsigned long long getMethodNum() const;
    unsigned long long getCallNum() const;
    std::string getFilePath();
    
  friend std::ostream& operator<<(std::ostream& o, Loader* l );
  
};

#endif