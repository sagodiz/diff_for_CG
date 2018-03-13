#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include <iostream>

using namespace std;

Loader::Loader( string filepath, string name ) : filepath(filepath), methodNum(0), callNum(0), uniqueMethodNum(0), name(name) {
  
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

string Loader::getFilePath() {
  
  return filepath;
}

unsigned long long Loader::getUniqueMethodNum() const {
  
  return uniqueMethodNum;
}

string Loader::getName() const {
  
 return name; 
}

//friend
ostream& operator<<(ostream& o, Loader* l ) {
  
  o << l->filepath;
  return o;
}