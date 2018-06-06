#ifndef LOADER_H
#define LOADER_H

#include "Record.h"
#include<fstream>
#include <iostream>
#include<set>

class Named {
public:
	virtual std::string getName() const = 0;
	virtual std::string getFilePath() = 0;
};

class UnionGraph : public Named {
public:
	std::string getName() const {
		return "UnionGraph";
	}

	std::string getFilePath() {
		return "UnionGraph";
	}
};

class Loader : public Named {
  
    std::string filepath;
  
  protected:
    std::ifstream input;
    unsigned long long methodNum;
    unsigned long long callNum;
    unsigned long long uniqueMethodNum;
    std::string name;

	std::set<std::string> notFilteredMethodNames;

	void printNotFilteredMethodNames();

  public:

    Loader( std::string filepath, std::string name );
    
    /**
    * Loads the nodes to the method store, if no matching method is found creates a new one with a new id
    */
    virtual std::vector<Record> load() = 0;
  
    /**
    * Uses the ids (ones that is used by every other tool) instead of it's own method names
    * @return Returns a set of connections a connection is represented as a pair<caller, calle>
    */
    virtual std::set<std::pair<int, int>> transformConnections() = 0;
  
    virtual ~Loader();
  
    unsigned long long getMethodNum() const;
    unsigned long long getCallNum() const;
    std::string getFilePath();
    unsigned long long getUniqueMethodNum() const;
    std::string getName() const;
    
  friend std::ostream& operator<<(std::ostream& o, Loader* l );
  
};

#endif