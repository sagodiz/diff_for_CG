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
                          new Switch("-sp", factory),
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

  //create an array for the transformed connections
  set<pair<int, int>> connections[loaders.size()];
  vector<Record> records[loaders.size()];
  
  for ( int i = 0; i < loaders.size(); ++i ) {
    
    records[i] = loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
VERBOSE1
  }
  
  for ( int i = 0; i < loaders.size() - 1; i++ ) {
    
    makeStat( connections[i], connections[i + 1], loaders[i], loaders[i + 1], records[i], records[i + 1] );
  }
  
  } catch( const string e ) {
    
    cerr << "An error has occurred: " << e << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}

static void makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Loader* l1, Loader* l2, vector<Record> r1, vector<Record> r2) {
  
  unsigned long long commonCalls = 0;
  unsigned long long commonMethods = 0;
  
  ofstream statOut(l1->getFilePath() + "-" + l2->getFilePath() + "-common-calls.txt");
  
  if ( !statOut.is_open() )
    throw Labels::COULD_NOT_WRITE_OUTPUT;

  for ( auto it1 : compareSet1 ) {
    
    if ( compareSet2.find(it1) != compareSet2.end() ) {
      //found
      ++commonCalls;
    }
  }
  
  for ( int i = 0; i < r1.size(); i++ ) {
    
    if ( find(r2.begin(), r2.end(), r1[i]) != r2.end() ) {
      
      ++commonMethods;
    }
  }
  statOut << l1->getFilePath() << " has " << l1->getCallNum() << " calls" << " and " << l1->getMethodNum() << " methods. " << l1->getUniqueMethodNum() << " unique method." << endl;
  statOut << l2->getFilePath() << " has " << l2->getCallNum() << " calls" << " and " << l2->getMethodNum() << " methods. " << l2->getUniqueMethodNum() << " unique method." << endl;
  statOut << commonCalls << " common calls and " << commonMethods << " common methods." << endl;
  
  statOut.close();
}
