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

void calcUnionGraphMethod(char** argV, int argI) {
  if (!strcmp(argV[argI + 1], "1")) {
    //calc ratios with union graph
    common::options::calculateUnionGraph = 1;
  }
  else {
    common::options::calculateUnionGraph = 0;
  }
  
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


void lineInfoPairingMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //false
    common::options::lineInfoPairing = false;
  }
  else if ( !strcmp(argV[argI + 1], "false") ) {
    //false
    common::options::lineInfoPairing = false;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //false
    common::options::lineInfoPairing = true;
  }
  else if ( !strcmp(argV[argI + 1], "true") ) {
    //false
    common::options::lineInfoPairing = true;
  }
  else {
    
    common::options::lineInfoPairing = false;
  }
}


void helpMethod(char** argV, int argI) {
  
  std::cout << "Usage: " << argV[0] << " [-loader file]* [-option]* [-option value]*" << std::endl;
  
  std::cout << "Loaders: " << std::endl 
  << "\t-s\t Soot" << std::endl 
  << "\t-osa\t OSA" << std::endl 
  << "\t-sp\t SPOON" << std::endl 
  << "\t-j\t JCG" << std::endl 
  << "\t-w\t WALA" << std::endl 
  << "\t-t\t Trace (It is the dynamic tool of F.)" << std::endl;
  
  std::cout << "Options with required value" << std::endl 
  << "\t-projectName name\t Name is the name of the project. If it is not provided \"Default\" will be used without quotes." << std::endl 
  << "\tfilterLevel level\t Level is a numer. It defines the filtering level:" << std::endl 
  << "\t\t0 No filtering" << std::endl 
  << "\t\t1 TODO: Filter calls if the caller or the calle is a java library method." << std::endl
  << "\t\t2 TODO: Filter calls. Only method of the projects remain. projectPath ought to be given." << std::endl 
  << "\t-projectPath path\t TODO:Path is the path where the project is located." << std::endl 
  << "\t-anonymTransformation level\t Level identifies how anonym parts of the nodes should be resolved:" << std::endl 
  << "\t\t0 No transformation (Default)" << std::endl 
  << "\t\t1 Transform every anonym member into a unified method name \"UNIFIEDMETHODNAME\" without quotes" << std::endl 
  << "\t\t higher levels are TODOs" << std::endl 
  << "\t-CHPtransformation level\t CHP generic methods are transformed. TODO:levels CHP is not used..." << std::endl
  << "\t-calcUnionGraph level\t Calculates a graf that contains every method and edge collected by every tool and includes it in stat. Level is 1 or 0" << std::endl
  << "\t-lineInfoPairing value\t Sets on or off the pairing based on lineinfo. Value for turning on pairing: {1, true} for turning off {0, false}. False is default value." << std::endl;
  
  std::cout << "Options without required values" << std::endl 
  << "\t-transformToGraphDB\t TODO:The output is transformed to the format used by the graph comparer tool" << std::endl 
  << "\t-h\t Well, it is not really an option, it just shows the help message." << std::endl;
  
}
