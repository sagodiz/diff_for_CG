#include "../inc/Option.h"

using namespace std;

Option::Option(string def, void (*fooA)(char**,int) ) : definer(def), fooP(fooA) {
}

Option::~Option() {
}

void Option::foo(char** argV, int argI) {
  
  if ( NULL == fooP )
    return;
  
  (*fooP)(argV, argI);
}

bool Option::operator==(const char* str) const {
  
  if ( definer == str )
    return true;
  return false;
}