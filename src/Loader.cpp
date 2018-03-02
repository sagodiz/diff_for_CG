#include "../inc/Loader.h"
#include "../inc/Labels.h"
using namespace std;

Loader::Loader( string filepath ) {
  
  out.open(filepath);
  if ( !out.is_open() )
    throw Labels::FILE_READ_ERROR;
}

Loader::~Loader() {
  out.close();
}
