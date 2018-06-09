#ifndef STAT_METHODS_H
#define STAT_METHODS_H

#include <set>
#include <vector>
#include "Record.h"
#include "Named.h"
#include "GraphDBCommon.h"
#include "Labels.h"
#include "common.h"
/* Gondolom ez itt egy TODO?!
struct StatData {
  unsigned methodCountForLoader1, methodCountForLoader2;
  unsigned callCountForLoader1, callCountForLoader2;
  unsigned commonMethodCount, commonCallCount;
};
*/
std::pair<unsigned long long, unsigned long long> makeStat(std::set<std::pair<int, int>> compareSet1, std::set<std::pair<int, int>> compareSet2, Named * l1, Named * l2, std::vector<Record> r1, std::vector<Record> r2);
void makeGraphDBStat(const std::vector<std::string>& labels);
void writeTSV(std::vector<Record>, std::string, std::string);
void writeConnTSV( std::set<std::pair<int, int>>, std::string);

#endif