#include "../inc/OptionMethods.h"
#include "../inc/Labels.h"
#include "../inc/common.h"

#include <cstring>
#include <iostream>
void projectNameMethod( char** argV, int argI ) {
  
  Labels::PROJECT_NAME = argV[argI + 1];
}

void cHPTransformationMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "false") || !strcmp(argV[argI + 1], "FALSE") ) {
    std::cout << "False" << std::endl;
    common::options::CHPTransform = false;
  }
}