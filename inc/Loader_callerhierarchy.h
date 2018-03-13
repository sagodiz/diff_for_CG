#ifndef LOADER_CALLERHIERARCHY_H
#define LOADER_CALLERHIERARCHY_H

#include "Loader.h"

class Loader_callerhierarchy : public virtual Loader {
  
  std::string prefix = "Method call hierarchy callees of ";
  
  public:
    Loader_callerhierarchy(std::string filepath, std::string name);
    ~Loader_callerhierarchy();
    std::vector<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif