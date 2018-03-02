#ifndef LOADER_H
#define LOADER_H

#include<fstream>
#include<set>

class Loader {
  
  std::ofstream out;
  
  public:
    Loader( std::string filepath );
    
    /**
    * Loads the nodes to the method store, if no matching method is found creates a new one with a new id
    */
    virtual bool load() = 0;
  
    /**
    * Uses the ids (ones that is used by every other tool) instead of it's own method names
    * @return Returns a set of connections a connection is represented as a pair<caller, calle>
    */
    virtual std::set<std::pair<int, int> > transformConnections() = 0;
  
    virtual ~Loader();
  
};

#endif