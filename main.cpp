#include<iostream>
#include<string>
#include<set>
#include<vector>

#include "inc/Loader.h"
#include "inc/Loader_soot.h"

using namespace std;

int main( int argc, char** argv ) {

  cout << "Starting transforming and making stat..." << endl;
  
  try {
    //TODO: kapcsolókkal addjam hozzá a loader-t s akkor beállítható, hogy melyik fusson le
    
  Loader* loaders[] = {
                      new Loader_soot("soot.out"),
                      NULL
                    };
  
  //get the amount of the loaders
  unsigned char i = 0;
  while( loaders[i++] );
  
  //create an array for the transformed connections
  set<pair<int, int>> connections[i];
  
  i = -1;
  while( loaders[++i] ) {
    
    loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
  }
  
  
  }
  catch(const string e) {
    cerr << "An error has occured: " << e << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}
