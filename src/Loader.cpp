#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include <iostream>

using namespace std;

Loader::Loader( string filepath ) : filepath(filepath), methodNum(0), callNum(0) {
  
  input.open(filepath);
  if ( !input.is_open() )
    throw Labels::FILE_READ_ERROR + filepath;
}

Loader::~Loader() {
  
  input.close();
}

unsigned long long Loader::getMethodNum() const {
  
  return methodNum;
}
unsigned long long Loader::getCallNum() const {
  
  return callNum;
}


//friend
ostream& operator<<(ostream& o, Loader* l ) {
  
  o << l->filepath;
  return o;
}