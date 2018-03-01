#include<iostream>


/*
* paramétereknek: feldolgozandó tool neve; feldolgozandó file
*/
int main( int argc, char** argv ) {
  
  Loader** loaders = {
                      new Loader_A(),
                      new Loader_B(),
                      ....
                      null
                    };
  
  unsigned char i = -1;
  while( loaders[++i] ) {
    
    loaders[i]->load();
  }
  
  
  
  return 0;
}