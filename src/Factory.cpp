#include "../inc/Factory.h"
#include "../inc/Loader.h"
#include "../inc/GraphDBCommon.h"
#include "../inc/Loader_soot.h"
#include "../inc/Loader_sourcemeter.h"
#include "../inc/Loader_callerhierarchy.h"
#include "../inc/Loader_spoon.h"
#include "../inc/Loader_gousiosg.h"
#include "../inc/Loader_wala.h"
#include "../inc/Loader_trace.h"
#include "../inc/Labels.h"

using namespace std;

bool Factory::factoryExist = false;
Factory* Factory::factory = NULL;
Factory::Factory() {
}

Loader* Factory::getLoaderPointer( string str, string filePath ) const {
  
  if ( "-s" == str ) {
    
    return new Loader_soot(filePath, "soot");
  }
  else if ( "-sm" == str ) {
    return new Loader_sourcemeter(filePath, "sourceMeter");
  }
  else if ( "-c" == str ) {
    return new Loader_callerhierarchy(filePath, "CHP");
  }
  else if ( "-sp" == str ) {
    return new Loader_spoon(filePath, "spoon");
  }
  else if ( "-g" == str ) {
    return new Loader_gousiosg(filePath, "gousiosg");
  }
  else if ( "-w" == str ) {
    return new Loader_wala(filePath, "wala");
  }
  else if ("-t" == str) {
	  return new Loader_trace(filePath, "trace");
  }
  else { 
    throw Labels::UNRECOGNIZED_SWITCH + str;
  }
}

Factory& Factory::createFactory() {
  
  if ( factoryExist )
    return *factory;
  
  Factory::factory = new Factory();
  factoryExist = true;
  
  return *factory;
  
}