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

template<typename T>
void printValue(FILE * common_file, const T& value);

template<>
void printValue(FILE * common_file, const float& value) {
	fprintf(common_file, "%.4f;", value);
}

template<>
void printValue(FILE * common_file, const unsigned long long& value) {
	fprintf(common_file, "%llu;", value);
}

template<typename T>
void printMatrix(const std::vector<Named*>& loaders, const std::vector<std::vector<T>>& mat, FILE * common_file, const std::string& type) {
	fprintf(common_file, "%s;", type.c_str());
	for (unsigned i = 0; i < mat.size(); ++i) {
		fprintf(common_file, "%s;", loaders[i]->getName().c_str());
	}
	fprintf(common_file, "\n");

	for (unsigned i = 0; i < mat.size(); ++i) {
		fprintf(common_file, "%s;", loaders[i]->getName().c_str());
		for (unsigned j = 0; j < mat.size(); ++j) {
			printValue<T>(common_file, mat[i][j]);
		}
		fprintf(common_file, "\n");
	}
	fprintf(common_file, "\n");
}

void writeTSV(std::vector<Record>, std::string, std::string);
void writeConnTSV( std::set<std::pair<int, int>>, std::string);

#endif