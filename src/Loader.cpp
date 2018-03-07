#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include <iostream>

using namespace std;

Loader::Loader( string filepath ) : filepath(filepath) {
  
  input.open(filepath);
  if ( !input.is_open() )
    throw Labels::FILE_READ_ERROR + filepath;
}

Loader::~Loader() {
  
  input.close();
}

//friend
ostream& operator<<(ostream& o, Loader* l ) {
  
  o << l->filepath;
  return o;
}