#ifndef LOADER_SPOON_H
#define LOADER_SPOON_H

#include "Loader.h"

class Loader_spoon : public virtual Loader {
	bool isExcludableInit(const std::string& name);
  public:
    Loader_spoon(std::string filepath, std::string name);
    ~Loader_spoon();
    std::vector<Record> load();
    std::set<std::pair<int, int>> transformConnections();
};

#endif