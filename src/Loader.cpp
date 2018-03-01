#include "../inc/Loader.h"

using namespace std;

Loader::Loader( string filepath ) {
  
  fp = fopen( filepath.c_str(), "r");
  if ( !fp )
    throw "File couldn't be loaded."
}

