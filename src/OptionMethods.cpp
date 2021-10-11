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

void anonymClassNameTransformationMethod( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //do not do any transformation
    common::options::anonymClassNameTransform = 0;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //turn every anonym class into a common anonymclass
    common::options::anonymClassNameTransform = 1;
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
    //true
    common::options::lineInfoPairing = true;
  }
  else if ( !strcmp(argV[argI + 1], "true") ) {
    //true
    common::options::lineInfoPairing = true;
  }
  else {
    
    common::options::lineInfoPairing = false;
  }
}

void methodUnio( char** argV, int argI ) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    
    common::options::resolve = common::enums::methodRes::unio;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    
    common::options::resolve = common::enums::methodRes::section;
  }
  else if ( !strcmp(argV[argI + 1], "2") ) {
    
    common::options::resolve = common::enums::methodRes::nothing;
  }
  else {
    
    common::options::resolve = common::enums::methodRes::unio;
  }
}

void jdtGeneric(char** argV, int argI) {

  if (!strcmp(argV[argI + 1], "0")) {

    common::options::JDT_generics = common::enums::JDTGenerics::JDT_nothing;
  }
  else if (!strcmp(argV[argI + 1], "1")) {

    common::options::JDT_generics = common::enums::JDTGenerics::JDT_onlyClass;
  }
  else if (!strcmp(argV[argI + 1], "2")) {

    common::options::JDT_generics = common::enums::JDTGenerics::JDT_onlyParameters;
  }
  else if (!strcmp(argV[argI + 1], "3")) {

    common::options::JDT_generics = common::enums::JDTGenerics::JDT_classAndParameters;
  }
  else {

    common::options::JDT_generics = common::enums::JDTGenerics::JDT_nothing;
  }
}

void onlyAnonymWithLineinfo(char** argV, int argI) {
  
  common::options::onlyAnonymWithLineinfo = true;
}

void genericParameterTypesNames(char** argV, int argI) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //false
    common::options::genericParameterTypesNames = false;
  }
  else if ( !strcmp(argV[argI + 1], "false") ) {
    //false
    common::options::genericParameterTypesNames = false;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //true
    common::options::genericParameterTypesNames = true;
  }
  else if ( !strcmp(argV[argI + 1], "true") ) {
    //true
    common::options::genericParameterTypesNames = true;
  }
  else {
    
    common::options::genericParameterTypesNames = false;
  }
}

void initblock2initMethod(char** argV, int argI) {
  
  if ( !strcmp(argV[argI + 1], "0") ) {
    //false
    common::options::initblock2init = false;
  }
  else if ( !strcmp(argV[argI + 1], "false") ) {
    //false
    common::options::initblock2init = false;
  }
  else if ( !strcmp(argV[argI + 1], "1") ) {
    //true
    common::options::initblock2init = true;
  }
  else if ( !strcmp(argV[argI + 1], "true") ) {
    //true
    common::options::initblock2init = true;
  }
  else {
    
    common::options::initblock2init = true;
  }
}

void taggingMethod(char** argV, int argI) {
  
  if ( !strcmp(argV[argI + 1], "soot") ) {
    //soot tagging
    common::sootTagging = argV[argI + 2];
  }
  else if ( !strcmp(argV[argI + 1], "jdt") ) {
    //JDT tagging
    common::jdtTagging = argV[argI + 2];
  }
  else {
    throw Labels::UNRECOGNIZED_SWITCH + argV[argI] + " " + argV[argI + 1];
  }
}

void approx(char** argV, int argI) {
  std::string tools = argV[argI + 1];
  std::string delimiter = "&";

  size_t pos = 0;
  std::string tool;
  while ((pos = tools.find(delimiter)) != std::string::npos) {
      tool = tools.substr(0, pos);
      common::approxTools.push_back(tool);
      tools.erase(0, pos + delimiter.length());
  }
  common::options::calculateApprox = true;
}

void approxLimit(char** argV, int argI) {
  try {
    common::options::filterNumber = std::stoi(argV[argI + 1]);
    common::options::approxAddedMethods = std::stoi(argV[argI + 1]);
  } catch(const std::out_of_range& e) {
    throw e.what();
  } catch( const std::invalid_argument& e) {
    throw e.what();
  }
}

void helpMethod(char** argV, int argI) {
  
  std::cout << "Usage: " << argV[0] << " [-loader file]... [-option]... [-option value]..." << std::endl << std::endl;
  
  std::cout << "Loaders: " << std::endl 
    << "\t" << Labels::SOOT_CL << "\t Soot" << std::endl 
    << "\t" << Labels::OSA_CL << "\t OSA" << std::endl 
    << "\t" << Labels::SPOON_CL << "\t SPOON" << std::endl 
    << "\t" << Labels::JCG_CL << "\t JCG" << std::endl 
    << "\t" << Labels::WALA_CL << "\t WALA" << std::endl 
    << "\t" << Labels::JDT_CL << "\t JDT" << std::endl
    << "\t" << Labels::TRACE_CL << "\t Trace (It is the dynamic tool of F.)" << std::endl << std::endl;
  
  std::cout << "Options with required value" << std::endl
    << "\t-projectName name\t Name is the name of the project. If it is not provided \"Default\" will be used without quotes." << std::endl
    << "\t-filterLevel level\t Level is a numer. It defines the filtering level:" << std::endl
    << "\t\t0 No filtering" << std::endl
    << "\t\t1 TODO: Filter calls if the caller or the calle is a java library method." << std::endl
    << "\t\t2 TODO: Filter calls. Only method of the projects remain. projectPath ought to be given." << std::endl
    << "\t-projectPath path\t TODO:Path is the path where the project is located." << std::endl
    << "\t-anonymTransformation level\t Level identifies how anonym parts of the nodes should be resolved:" << std::endl
    << "\t\t0 No transformation (Default)" << std::endl
    << "\t\t1 Transform every anonym member into a unified method name \"UNIFIEDMETHODNAME\" without quotes" << std::endl
    << "\t-calcUnionGraph level\t Calculates a graf that contains every method and edge collected by every tool and includes it in stat. Level is 1 or 0" << std::endl
    << "\t-lineInfoPairing value\t Sets on or off the pairing based on lineinfo. Value for turning on pairing: {1, true} for turning off {0, false}. False is default value." << std::endl
    << "\t-methodUnio value\t How method pairing should be \"counted\"." << std::endl
    << "\t\t0 Union. (Default) Find all matches." << std::endl
    << "\t\t1 Section. Find all matches A in B and B in A and get the common methods of this two." << std::endl
    << "\t\t2 Nothing. It does nothing. The difference in number of matches is not resolved." << std::endl
    << "\t-JDTGenerics value\tHow JDT loader should transform generics" << std::endl
    << "\t\t0: no transformation" << std::endl
    << "\t\t1: transform only class generics" << std::endl
    << "\t\t2: transform only parameters" << std::endl
    << "\t\t3: transform both class and method generics." << std::endl
    << "\t-genericParameterTypeNames value \tSets on or off if generic pairing should consider tipical names: E, K, N, T, V. considered as generic parameters. Value for turnong on: {1, true} for turning off {0, false}. False is default." << std::endl
    << "\t-initblock2init value\tTurns off or on the pairing of initblocks and inits (constructors) Values: {1, ture} (default) turns on {0, false} turns off" << std::endl
    << "\t-tagging tool file\tThe tool thats tagging set should be used (it can be used multiple times) the file where taggings are placed" << std::endl
    << "\t\tsoot Tagging using Soot" << std::endl 
    << "\t\tjdt Tagging using JDT" << std::endl
    << "\t-approx config-string\tSets the approximation to true and accepts a string that sets what tools should be used during approximation. This string contains the names of the tools separated by '&'. If no name is provided for the tools the default is used. Always the first tool's calls are filtered and combined with the second tool's calls." << std::endl
    << "\t-approxLimits int1 int2\tSets how many methods are needed to consider similar calls \"exploded graph\" and how many methods should be inserted from the second tool." << std::endl
    << std::endl;
  
  std::cout << "Options without required values" << std::endl 
    << "\t-onlyAnonym\t It sets that only anonym elements should be compared by lineinfo." << std::endl
    << "\t-h\t Well, it is not really an option, it just shows the help message." << std::endl;
  
}
