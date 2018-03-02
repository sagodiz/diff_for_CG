#include<iostream>
#include<string>
#include<set>
#include<vector>

#include "inc/Loader.h"
#include "inc/Loader_soot.h"

namespace common {
  
  std::vector<std::vector<std::string>> storedIds; 
}

using namespace std;

int main( int argc, char** argv ) {

  cout << "Starting transforming and making stat..." << endl;
  
  try {
  Loader* loaders[] = {
                      new Loader_soot("todo"),
                      NULL
                    };
  
  //get the amount of the loaders
  unsigned char i = 0;
  while( loaders[i++] );
  
  //create an array for the transformed connections
  set<pair<int, int> > connections[i];
  
  i = -1;
  while( loaders[++i] ) {
    
    loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
  }
  
  
  }
  catch(...) {
    cerr << "An error has occured." << endl;
  }

  cout << "End of program." << endl;
  
  return 0;
}
