#ifndef LOADER_SOURCEMETER_H
#define LOADER_SOURCEMETER_H

#include "Loader.h"

class Loader_sourcemeter : public virtual Loader {
  
  public:
    Loader_sourcemeter(std::string filepath);
    ~Loader_sourcemeter();
    std::vector<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif