#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "inc/Labels.h"
#include "inc/Loader.h"
#include "inc/Loader_soot.h"
#include "inc/Loader_callerhierarchy.h"
#include "inc/Loader_sourcemeter.h"
#include "inc/Switch.h"
#include "inc/common.h"
#include "inc/Record.h"
#include "inc/Factory.h"
#include "inc/OptionMethods.h"
#include "inc/Option.h"

#if defined(VERBOSE)
  #define VERBOSE1 \
    cout << "------" << loaders[i] << "--------" << endl;\
    for ( pair<int, int> it : connections[i] ) {\
      \
      cout << it.first << " " << it.second << endl;\
    }\
    cout << "-------------------------------------" << endl;\
    cout << loaders[i]->getMethodNum() << " method has been processed and " << endl << loaders[i]->getCallNum() << "call has been transformed." << endl;\
    cout << "-------end of " << loaders[i] << "--------" << endl;
#else
  #define VERBOSE1 ;
#endif


using namespace std;

static void makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Loader* l1, Loader* l2, vector<Record> r1, vector<Record> r2);

static void writeTSV(vector<Record>, string, string);

int main( int argc, char** argv ) {

  if ( argc < 3 ) {
    
    cout << "At least 1 tool have to be given." << endl;
    return 1;
  }
  
  cout << "Starting transforming and making stat..." << endl;
  
  try { 
  
  Factory factory = Factory::createFactory();
  
  Switch* switches[] = {
                          new Switch("-s", factory ),
                          new Switch("-c", factory ),
                          new Switch("-sm", factory ),
                          new Switch("-sp", factory ),
                          NULL
                        };
  
  Option* options[] = {
                          new Option("-projectName", &projectNameMethod),
                          new Option("-CHPtransformation", &cHPTransformationMethod),
                          NULL
                      };
    
  //need pointer otherwise vector do not accept as Loader is abstract
  vector<Loader*> loaders;
  
  unsigned char j = -1;
  while( switches[++j] ) {
    
    for ( int i = 1; i < argc - 1; i++ ) {
      
      if ( *(switches[j]) == argv[i] ) {

        switches[j]->init(argv[++i]);
        loaders.push_back( switches[j]->getLoaderPointer() );
      }
    }
  }
  j = -1;
  while( options[++j] ) {
    
    for ( int i = 1; i < argc - 1; i++ ) {
      
      if ( *(options[j]) == argv[i] ) {

        options[j]->foo(argv, i);
      }
    }
  }

  //create an array for the transformed connections
  std::vector<set<pair<int, int>>> connections;
  connections.resize(loaders.size());
  std::vector<vector<Record>> records;
  records.resize(loaders.size());
  
  for (unsigned i = 0; i < loaders.size(); ++i ) {
    
    records[i] = loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
VERBOSE1
  }
  
  for ( unsigned i = 0; i < records.size(); i++ ) {
    
    writeTSV(records[i], loaders[i]->getName(), loaders[i]->getName());
  }
  
  for (unsigned i = 0; i < loaders.size() - 1; i++ ) {
    
    for (unsigned j = i + 1; j < loaders.size(); j++ ) {
      
      makeStat( connections[i], connections[j], loaders[i], loaders[j], records[i], records[j] );
    }
  }
  
  } catch( const string e ) {
    
    cerr << "An error has occurred: " << e << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}
//########################################################################x
//########################################################################x
//########################################################################x
//########################################################################x

static void writeTSV( vector<Record> records, string name, string tool ) {
  
  ofstream TSV(Labels::PROJECT_NAME + tool + "loadedMethods.tsv");
  
  if ( !TSV.is_open() )
    throw Labels::COULD_NOT_WRITE_TSV;
  
  TSV << "name" << "\t" << "transformed rep." << "\t" << "tool. rep" << endl;
  
  for ( unsigned i = 0; i < records.size(); i++ ) {
    
    TSV << name << "\t" << records[i] << "\t";
    
    if ( records[i].getSameMethods().size() > 1 )
      throw Labels::TOOL_HAS_MORE_THAN_ONE_REP + name;
    
    TSV << records[i].getSameMethods().at(0) + records[i].getSecondaryRepresentation() << endl;
  }
}

static void makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Loader* l1, Loader* l2, vector<Record> r1, vector<Record> r2 ) {
  
  unsigned long long commonCalls = 0;
  unsigned long long commonCallsCheck = 0;
  unsigned long long commonMethods = 0;
  unsigned long long commonMethodsCheck = 0;
  
  vector<Record> onlyFirst;
  vector<Record> onlySecond;
  
  vector<pair<int, int>> onlyFirstCall;
  vector<pair<int, int>> onlySecondCall;
  
  ofstream statOut(Labels::PROJECT_NAME + l1->getName() + "-" + l2->getName() + "-common-calls.txt");
  
  //check calls
  if ( !statOut.is_open() )
    throw Labels::COULD_NOT_WRITE_OUTPUT;

  for ( auto it1 : compareSet1 ) {
    
    if ( compareSet2.find(it1) != compareSet2.end() ) {
      //found
      ++commonCalls;
    }
    else {
      
      onlyFirstCall.push_back(it1);
    }
  }
  
  for ( auto it2 : compareSet2 ) {
    
    if ( compareSet1.find(it2) != compareSet1.end() ) {
      //found
      ++commonCallsCheck;
    }
    else {

      onlySecondCall.push_back(it2);
    }
  }
  
  if ( commonCalls != commonCallsCheck )
    cerr << "The search for common calls failed" << endl;
   
  //check the methods
  for ( unsigned i = 0; i < r1.size(); i++ ) {
    
    if ( find(r2.begin(), r2.end(), r1[i]) != r2.end() ) {
      
      ++commonMethods;
    }
    else {
      //this method is not in the second tool's vector
      onlyFirst.push_back(r1[i]);
    }
  }
  
  for ( unsigned i = 0; i < r2.size(); i++ ) {
    
    if ( find(r1.begin(), r1.end(), r2[i]) != r1.end() ) {
      
      ++commonMethodsCheck;
    }
    else {
      //this method is not in the second tool's vector
      onlySecond.push_back(r2[i]);
    }
  }
  
  if ( commonMethodsCheck != commonMethods )
    cerr << "The search for common methods failed" << endl;
  
  statOut << l1->getFilePath() << " has " << l1->getCallNum() << " calls" << " and " << l1->getMethodNum() << " methods. " << l1->getUniqueMethodNum() << " unique method." << endl;
  statOut << l2->getFilePath() << " has " << l2->getCallNum() << " calls" << " and " << l2->getMethodNum() << " methods. " << l2->getUniqueMethodNum() << " unique method." << endl;
  statOut << commonCalls << " common calls and " << commonMethods << " common methods." << endl;
  
  //write the differences
  statOut << "Only the " << l1->getName() << " contains this/these method(s):" << endl;
  
  for ( unsigned i = 0; i < onlyFirst.size(); i++ ) {
    
    statOut << onlyFirst[i] << endl;
  }
  
  statOut << "Only the " << l2->getName() << " contains this/these method(s):" << endl;
  
  for ( unsigned i = 0; i < onlySecond.size(); i++ ) {
    
    statOut << onlySecond[i] << endl;
  }
  
  statOut << "Only the " << l1->getName() << " contains this/these call(s):" << endl;
  
  for ( unsigned i = 0; i < onlyFirstCall.size(); i++ ) {
    
    statOut << onlyFirstCall[i].first << " [" << common::getMethodById(onlyFirstCall[i].first) << "] " << onlyFirstCall[i].second << " [" << common::getMethodById(onlyFirstCall[i].second) << " ]" << endl;
  }
  
  statOut << "Only the " << l2->getName() << " contains this/these call(s):" << endl;
  
  for ( unsigned i = 0; i < onlySecondCall.size(); i++ ) {
    
    statOut << onlySecondCall[i].first << " [" << common::getMethodById(onlySecondCall[i].first) << "] " << onlySecondCall[i].second << " [" << common::getMethodById(onlySecondCall[i].second) << " ]" << endl;
  }
  
  statOut.close();
}
