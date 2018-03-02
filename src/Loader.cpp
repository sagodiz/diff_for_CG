#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include <iostream>

using namespace std;

Loader::Loader( string filepath ) {
  
  input.open(filepath);
  if ( !input.is_open() )
    throw Labels::FILE_READ_ERROR + filepath;
}

Loader::~Loader() {
  
  input.close();
}
