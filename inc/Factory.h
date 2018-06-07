#ifndef FACTORY_H
#define FACTORY_H

#include "Loader.h"

class Factory {
  
    static bool factoryExist;
    static Factory* factory;
    Factory();
    
  public:
    static Factory& createFactory();
    Loader* getLoaderPointer(std::string definer, std::string filePath, unsigned counter) const;
	Named* getUnionGraphPointer() const;
};

#endif