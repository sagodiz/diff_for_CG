#ifndef LOADER_TRACE_H
#define LOADER_TRACE_H

#include "Loader.h"

class Loader_trace : public virtual Loader {
	static const std::string entry_node;
	std::string entry_representation;

public:
	Loader_trace(std::string filepath, std::string name);
	~Loader_trace();
	std::vector<Record> load();
	std::set<std::pair<int, int>> transformConnections();
};

#endif