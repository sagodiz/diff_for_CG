#ifndef LOADER_SOOT_H
#define LOADER_SOOT_H

#include "Loader.h"

class Loader_soot : public virtual Loader {
  
  public:
    Loader_soot(std::string filepath);
    ~Loader_soot();
    bool load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif