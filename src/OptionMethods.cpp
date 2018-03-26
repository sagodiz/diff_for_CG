#include "../inc/OptionMethods.h"
#include "../inc/Labels.h"
#include "../inc/common.h"

#include <cstring>

void projectNameMethod( char** argV, int argI ) {
  
  Labels::PROJECT_NAME = argV[argI + 1];
}

void cHPTransformationMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //do not do any transformation
    common::options::CHPTransform = 0;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //transform the class name and no more
    common::options::CHPTransform = 1;
  }
  else if ( !strcmp(argV[argI + 1], "2") ) {
    //transform the classname, and remove generic signature in params
    common::options::CHPTransform = 2;
  }
  else if ( !strcmp(argV[argI + 1], "3") ) {
    //change every generic param type to object
    common::options::CHPTransform = 3;
  }
  else {
    
    common::options::CHPTransform = 0;
  }
}