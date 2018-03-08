#ifndef LOADER_CALLERHIERARCHY_H
#define LOADER_CALLERHIERARCHY_H

#include "Loader.h"

class Loader_callerhierarchy : public virtual Loader {
  
  public:
    Loader_callerhierarchy(std::string filepath);
    ~Loader_callerhierarchy();
    std::set<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif