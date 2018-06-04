#include "../inc/OptionMethods.h"
#include "../inc/Labels.h"
#include "../inc/common.h"

#include <cstring>
#include <iostream>

void projectNameMethod( char** argV, int argI ) {
  
  Labels::PROJECT_NAME = argV[argI + 1];
}

void filterLevelMethod(char** argV, int argI) {

	if (!strcmp(argV[argI + 1], "0")) {
		//no filtering at all
		common::options::filterLevel = 0;
	}
	else if (!strcmp(argV[argI + 1], "1")) {
		//filter java libs
		common::options::filterLevel = 1;
	}
	else if (!strcmp(argV[argI + 1], "2")) {
		//filter java libs and inits, constructors
		common::options::filterLevel = 2;
	}
	else {

		common::options::filterLevel = 0;
	}
}

void projectPathMethod(char** argV, int argI) {

	Labels::PROJECT_PATH = argV[argI + 1];
}

void transformToGraphDB(char** argV, int argI) {

	if (!strcmp(argV[argI + 1], "0")) {
		//do not produce graphml with unified names
		common::options::loadToGraph = 0;
	}
	else if (!strcmp(argV[argI + 1], "1")) {
		//produce graphml with unified names
		common::options::loadToGraph = 1;
	}
	else if (!strcmp(argV[argI + 1], "2")) {
		//produce graphml with unified names
		common::options::loadToGraph = 2;
	}
	else {

		common::options::loadToGraph = 0;
	}
}


void cHPTransformationMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //do not do any transformation
    common::options::CHPTransform = 0;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //clean every method even if it is not among the generic params
    common::options::CHPTransform = 1;
  }
  else if ( !strcmp(argV[argI + 1], "2") ) {
    //transform the class name and no more
    common::options::CHPTransform = 2;
  }
  else if ( !strcmp(argV[argI + 1], "3") ) {
    //transform the classname, and remove generic signature in params
    common::options::CHPTransform = 3;
  }
  else if ( !strcmp(argV[argI + 1], "4") ) {
    //change every generic param type to object
    common::options::CHPTransform = 4;
  }
  else {
    
    common::options::CHPTransform = 0;
  }
}

void anonymClassNameTransformationMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //do not do any transformation
    common::options::anonymClassNameTransform = 0;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //turn every anonym class into a common anonymclass
    common::options::anonymClassNameTransform = 1;
  }
  else if ( !strcmp(argV[argI + 1], "2") ) {  //TODO!!!!
    //anonym in anonym continue numbering, TODO!!!!!!!!!!!!!!!
    common::options::anonymClassNameTransform = 2;
  }
  else {
    
    common::options::anonymClassNameTransform = 0;
  }
}