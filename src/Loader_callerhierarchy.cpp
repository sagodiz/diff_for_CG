#include "../inc/Loader_callerhierarchy.h"
#include "../inc/common.h"
#include "../inc/Labels.h"

#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

Loader_callerhierarchy::Loader_callerhierarchy( string filepath, string name ) : Loader(filepath, name) {
}
Loader_callerhierarchy::~Loader_callerhierarchy() {
}

vector<Record> Loader_callerhierarchy::load() {
  
  vector<Record> tmpRecords;
  
  string line;
  string representation;
  vector<string> genericStrings;
  
  while ( getline(input, line) ) {
    
    if ( 1 == line.length() ) {
      //empty line
    }
    else {
      //caller or callee, but a node
      ++methodNum;
      
      if ( '\t' == line[0] ) {
        
        line.erase(0, 1);
      }
      else {
        
        line.erase(0, prefix.length());
      }
      
      if ( 0 == line.length() )
        continue;
      
      representation = line;
    
      string pckgClassMethod, params, method, pckgClass;
        
      stringstream input_stringstream(line);
      //if no parameter is given there is no '(' so we get back the whole line
      getline(input_stringstream, pckgClassMethod , '(');
      
      if ( pckgClassMethod == line ) {
        //there were no '('
        params = "";
        
      }
      else {
        
        getline(input_stringstream, params , '(');
        params.erase(params.length() - 1, 1); //remove ')'
      }
        
      size_t lastDotPos = pckgClassMethod.rfind("."); //find the last dot. From that point method name comes

      if ( lastDotPos != string::npos ) {
        
        method = pckgClassMethod.substr(lastDotPos + 1);
        pckgClass = pckgClassMethod.substr(0, lastDotPos);
        
        //check if it is a constructor, so method equals the className that is after the "remaining" lastDot
        //if it is make it an init method
        
        size_t genPos = pckgClass.find("<");
        if ( common::options::CHPTransform > 0 && genPos != string::npos ) {

          //it is a generic class
          string generics = pckgClass.substr(genPos);
          pckgClass.erase(genPos, pckgClass.length() - genPos + 1);
          generics.erase(0,1);  //<
          generics.erase(generics.length() - 1, 1); //>

          stringstream giss(generics);
          string Genparameter;
          while ( getline(giss, Genparameter, ',') ) {

            if ( ' ' == Genparameter[0] ) {
              Genparameter.erase(0,1);
              
            }
            genericStrings.push_back(Genparameter);
          }
        }
        
        if ( method == pckgClass.substr(pckgClass.rfind(".") + 1) )
          method = "<init>";
        
      }
      else {

        throw Labels::METHOD_NOT_FOUND_ERROR + pckgClassMethod;
      }
      
      vector<string> parameterVector;
      stringstream iss(params);
      string parameter;
      while( getline(iss, parameter, ',') ) {
        
        if ( ' ' == parameter[0] )
          parameter.erase(0, 1);
        
        if ( find(genericStrings.begin(), genericStrings.end(), parameter) != genericStrings.end() ) {
          //so this parameter !MAY! come from generic params.
          switch( common::options::CHPTransform ) {
            
            case 1://class is alread transormed
                  break;
            case 2://remove generic signature from param
                  parameter.erase(parameter.find("<"));
                  break;
            case 3://change ecery generic param type to object
                  parameter = "java.lang.Object";
                  break;
            default: //mst not happen
                    throw Labels::CHP_TRANSFORMATION_OPTION_ERROR;
          } 
        }
        
        parameterVector.push_back(parameter);
      }
      
      if ( 0 == pckgClass.length() || 0 == method.length() )
        throw Labels::UNINITIALIZED_RECORD;
      
      
      if ( common::options::anonymClassNameTransform > 0 ) {
        //there is a kind of transformation
        if ( 1 == common::options::anonymClassNameTransform ) {
          //turn every anonym class into a constant anonym class
          common::unifyeAnonymClasses(pckgClass);
        }
        else if ( 2 == common::options::anonymClassNameTransform ) {
          //continue numbering in inner anonym classes
          //TODO!!! 
        }
        else {
          
          throw Labels::ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN;
        }
      }
      
      Record r(representation, pckgClass, method, parameterVector);

      //tmpRecords.push_back( r ); TODO: ne ezt adja hozzá, mert mi van ha a transzformált dolog van benne $->. Azt honnan veszem?
      //mert ide nem tudom berakni a $ jeleket, azonban ha megtaláltam, hogy melyik lenne, akkor annak le tudom kérni az osztály nevét
      //és azzal már tudok csinálni egy új rekordot.
      //ez a nesteed osztályok fixálására van. Az anonymokat majd valahogy máshogy fogjuk.

      if ( find( common::storedIds.begin(), common::storedIds.end(), r ) == common::storedIds.end() ) {
        
        bool finallyFound = false;
        unsigned index = -1;
        for ( unsigned i = 0; i < common::storedIds.size(); i++ ) {

          if ( r >>= common::storedIds[i] ) {//TODO ? operator
            //after replacing '$' s found it
            common::storedIds[i] += representation;
            index = i;
            finallyFound = true;
          }
        }
        
        if ( finallyFound ) {
          //new record is pushed back as it is used later.. no other way to create the appropiate class name only by copying it.
          Record r2(representation, common::storedIds[index].getClass(), common::storedIds[index].getMethodName(), parameterVector);
          if ( find(tmpRecords.begin(), tmpRecords.end(), r2) == tmpRecords.end() )
            tmpRecords.push_back(r2);
        }
        else {
          //so this record is not found in the vector
          if ( find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end() ) //here it should always happen but who knows
            tmpRecords.push_back(r);
          common::storedIds.push_back(r);
          ++uniqueMethodNum;
        }
      }
      else {
        
        if ( find(tmpRecords.begin(), tmpRecords.end(), r) == tmpRecords.end() )
          tmpRecords.push_back(r);
        auto it = find( common::storedIds.begin(), common::storedIds.end(), r );
        if ( *it == representation ) {
          //contains this representation
        }
        else {
          ++uniqueMethodNum;
          *it += representation;  //add this representation
        }
      }
    }
  }
  
  input.clear();
  input.seekg(0, ios::beg);
  
  return tmpRecords;
}

set<pair<int, int>> Loader_callerhierarchy::transformConnections() {
  
  set<pair<int, int>> connections;
  
  bool changeCaller = false;
  
  string line;
  string caller;
  string callee;
  
  unsigned int callerId = -1;
  unsigned int calleeId = -1;
  
  while ( getline(input, line) ) {
    
    changeCaller = false;
    
    if ( 0 == line.length() ) {
      //empty line
    }
    else {
      //caller or callee, but a node so in a connection, set the 
      
      if ( '\t' == line[0] ) {
        
        line.erase(0, 1);
        callee = line;
      }
      else {
        
        line.erase(0, prefix.length());
        caller = line;
        changeCaller = true;
      }
      
      if ( changeCaller ) {
        //do nothing as here comes a new "list" os connections
      }
      else {
        //the remaining caller calls the callees
        ++callNum;
        
        bool check = false; //to check if the method do be found.
      
        for (unsigned i = 0; i < common::storedIds.size(); i++ ) {

          if ( common::storedIds[i] == caller ) {

            check = true;
            callerId = i;
            break;
          }
        }
        if ( !check ) {

          cerr << "Method couldn't be resolved: " << caller << endl;
        }

        check = false;
        for (unsigned i = 0; i < common::storedIds.size(); i++ ) {

          if ( common::storedIds[i] == callee ) {

            check = true;
            calleeId = i;
            break;
          }
        }
        if ( !check ) {

          cerr << "Method couldn't be resolved: " << callee << endl;
        }

        connections.insert(pair<int, int>(callerId, calleeId));
      }
    }
  }

  
  return connections;
}