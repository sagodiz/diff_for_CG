#ifndef GRAPHDB_COMMON_H
#define GRAPHDB_COMMON_H

#include <vector>
#include <set>
#include <utility>
#include "Record.h"

class GraphDBCommon {
public:
	static void writeUnifiedGraphToGraphml(std::string filename, const std::vector<Record>& records, const std::set<std::pair<int, int>>& connections);
	static bool convertGraphmlToJson(const std::string& in_filename, const std::string& o_filename);

};

#endif
