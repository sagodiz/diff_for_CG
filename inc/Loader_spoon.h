#ifndef LOADER_SPOON_H
#define LOADER_SPOON_H

#include "Loader.h"

class Loader_spoon : public virtual Loader {
  
  public:
    Loader_spoon(std::string filepath);
    ~Loader_spoon();
    std::vector<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif