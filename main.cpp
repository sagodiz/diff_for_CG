#include<iostream>
#include<string>
#include<set>
#include<vector>

#include "inc/Loader.h"
#include "inc/Loader_soot.h"
#include "inc/Switch.h"

using namespace std;

int main( int argc, char** argv ) {

  cout << "Starting transforming and making stat..." << endl;
  
  try {
  
  Switch* switches[] = {
                          new Switch("-s", *(new Loader_soot("soot.out"))),
                          NULL
                        };
  
  //need pointer otherwise vector do not accept as Loader is abstract
  vector<Loader*> loaders;
  
  unsigned char j = -1;
  while( switches[++j] ) {
    
    for ( int i = 1; i < argc; i++ ) {
      
      if ( *(switches[j]) == argv[i] ) {
        
        loaders.push_back(&(switches[j]->getLoader()));
      }
    }
  }
  
  //create an array for the transformed connections
  set<pair<int, int>> connections[loaders.size()];
  
  for ( int i = 0; i < loaders.size(); ++i ) {
    
    loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
  }
  
  }
  catch(const string e) {
    cerr << "An error has occurred: " << e << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}
