#include "../inc/Loader.h"

using namespace std;

Loader::Loader( string filepath ) {
  
  out.open(filepath);
  if ( !out.is_open() )
    throw "File couldn't be loaded.";
}

Loader::~Loader() {
  out.close();
}