#ifndef UNION_GRAPH_H
#define UNION_GRAPH_H

#include "Named.h"

class UnionGraph : public Named {
public:
	std::string getName() const {
		return "UnionGraph";
	}

	std::string getFilePath() {
		return "UnionGraph";
	}
};

#endif
