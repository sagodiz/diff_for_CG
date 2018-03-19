#ifndef LOADER_GOUSIOSG_H
#define LOADER_GOUSIOSG_H

#include "Loader.h"

class Loader_gousiosg : public virtual Loader {
  
  public:
    Loader_gousiosg(std::string filepath, std::string name);
    ~Loader_gousiosg();
    std::vector<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif