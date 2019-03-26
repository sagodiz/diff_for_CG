#include<iostream>
#include<fstream>
#include<set>

using namespace std;

int main(int argc, char **argv ) {
  
  if ( argc != 3 ) {
    cerr << "Give parameters: collection-of-methods file2filter " << endl;
    cout << "This program collects the calls from the file (given in first parameter) that are listed in the second parameter." << endl;
    return -1;
  }
  
  string line;
  ifstream input(argv[1]);
  if ( !input.is_open() ) {
    
    cerr << "Could not read file: " << argv[1] << endl;
    return -2;
  }
  
  set<string> methods;
  
  while ( input >> line ) {
    methods.insert(line);
  }
  
  input.close();
  input.open(argv[2]);
  if ( !input.is_open() ) {
    
    cerr << "Could not read file: " << argv[2] << endl;
    return -3;
  }
  
  ofstream output("commonMethodCalls.tsv");
  if ( !output.is_open() ) {
    
    cerr << "Could not write file: commonMethodCalls.tsv" << endl;
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
      
      output << line << endl;
    }
  }
  
  return 0;
}