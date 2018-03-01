#include<iostream>
#include<string>

using namespace std;

int main( int argc, char** argv ) {
  
  Loader** loaders = {
                      new Loader_A(),
                      new Loader_B(),
                      ....
                      null
                    };
  //get the amount of the loaders
  unsigned char i = 0;
  while( loaders[i++] );
  
  //create an array for the transformed connections
  set<pair<int, int> > connections[i];
  
  i = -1;
  while( loaders[++i] ) {
    
    loaders[i]->load();
    loaders[i]->transformConnections();
  }
  
  
  
  return 0;
}
