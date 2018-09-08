#ifndef OPTION_METHODS_H
#define OPTION_METHODS_H

/*
* These methods are used to handle command line options
*/


void projectNameMethod(char **argVector, int argIndex); //sets the project name
void filterLevelMethod(char** argV, int argI);  //sets the filter level
void cHPTransformationMethod(char** argVector, int argIndex); //sets the level of chp transformation (in case of chp generics were difficult to handle)
void anonymClassNameTransformationMethod(char** argVector, int argIndex); //sets how anonym classes should be handled.
void transformToGraphDB(char** argV, int argI); //makes transformation
void projectPathMethod(char **argVector, int argIndex); //sets the project path variable (in filtering path is used)
void calcUnionGraphMethod(char** argV, int argI); //makes the program to calculate stats. with the unnion graph
void lineInfoPairingMethod(char** argV, int argI);  //sets whether the lineinfo should be used in pairing.
void methodUnio(char** argV, int argI); //sets if methods that has multiple pairs should be paired to every math.
void jdtGeneric(char** argV, int argI); //sets how JDT loader should transform generics
void helpMethod(char** argV, int argI); //shows help message

#endif