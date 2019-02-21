#include<iostream>
#include<fstream>
#include<set>

using namespace std;

int main(int argc, char **argv ) {
  
  if ( argc != 3 ) {
    cerr << "Adja meg a paramétereket: metódus_gyűjtemény szűrendő_file " << endl;
    cout << "This program collects the calls that exist only between nodes that are found by every tool." << endl;
    return -1;
  }
  
  string line;
  ifstream input(argv[1]);
  if ( !input.is_open() ) {
    
    cerr << "Nem lehetett megnyitni olvasásra a filet: " << argv[1] << endl;
    return -2;
  }
  
  set<string> methods;
  
  while ( input >> line ) {
    methods.insert(line);
  }
  //cout << "Methods are loaded." << endl;
  
  input.close();
  input.open(argv[2]);
  if ( !input.is_open() ) {
    
    cerr << "Nem lehetett megnyitni olvasásra a filet: " << argv[2] << endl;
    return -3;
  }
  
  ofstream output("commonMethodCalls.tsv");
  if ( !output.is_open() ) {
    
    cerr << "Nem lehetett megnyitni olvasásra a filet: commonMethodCalls.tsv" << endl;
    return -4;
  }
  
  getline(input, line);
  output << line << endl;
  while ( getline(input, line) ) {
    
    string id1, id2;
    
    
    int i = 1;
    do {
      
      id1 += line[i];
      i++;
    }while ( line[i] != ')' );
    
    while(line[i] != '-' || line[i+1] != '>' ) {
      i++;
    }
    i += 3;
    
    do {
      
      id2 += line[i];
      i++;
    }while ( line[i] != ')' );
    
    
    if ( methods.find(id1) != methods.end() && methods.find(id2) != methods.end() ) {
      
      output << line << endl; //endl nem biztos, hogy kell
    }
  }
  
  return 0;
}