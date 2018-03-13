#include "../inc/OptionMethods.h"
#include "../inc/Labels.h"

void projectNameMethod( char** argV, int argI ) {
  
  Labels::PROJECT_NAME = argV[argI + 1];
}