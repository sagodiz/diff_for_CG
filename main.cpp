#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "inc/Loader.h"
#include "inc/Loader_soot.h"
#include "inc/Loader_callerhierarchy.h"
#include "inc/Loader_sourcemeter.h"
#include "inc/Switch.h"
#include "inc/common.h"

using namespace std;

int main( int argc, char** argv ) {

  if ( argc < 2 ) {
    
    cout << "At least 1 tool have to be given." << endl;
    return 1;
  }
  
  cout << "Starting transforming and making stat..." << endl;
  
  try {
  
  Switch* switches[] = {
                          new Switch("-s", *(new Loader_soot("soot.out"))),
                          new Switch("-c", *(new Loader_callerhierarchy("callerhierarchy.out"))),
                          new Switch("-sm", *(new Loader_sourcemeter("sourcemeter.out"))),
                          NULL
                        };
  
  //need pointer otherwise vector do not accept as Loader is abstract
  vector<Loader*> loaders;
  
  unsigned char j = -1;
  while( switches[++j] ) {
    
    for ( int i = 1; i < argc; i++ ) {
      
      if ( *(switches[j]) == argv[i] ) {

        loaders.push_back( &(switches[j]->getLoader()) );
      }
    }
  }

  //create an array for the transformed connections
  set<pair<int, int>> connections[loaders.size()];
  
  for ( int i = 0; i < loaders.size(); ++i ) {
    
    loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
    
    cout << "------" << loaders[i] << "--------" << endl;
    for ( pair<int, int> it : connections[i] ) {
      
      cout << it.first << " " << it.second << endl;
    }
    cout << "------------------------------------" << endl;
  }
  
  } catch( const string e ) {
    
    cerr << "An error has occurred: " << e << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}
