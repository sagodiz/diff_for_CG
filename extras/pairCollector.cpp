#include<iostream>
#include<fstream>
#include<set>

using namespace std;

int main(int argc, char** argv) {
  
  if ( argc < 2 ) {
    cerr << "File to collect pairs from. [separator] by default it is \"---\"" << endl;
    cout << "This file collects distinct method pairs. (A-B B-A duplications are removed)" << endl;
    return 1;
  }
  
  ifstream input(argv[1]);
  if ( !input.is_open() ) {
    cerr << "Could not read file: " << argv[1] << endl;
    return 2;
  }
  
  string sep;
  
  if ( 3 <= argc ) {
    
    sep = argv[2];
  }
  else {
    
    sep = "---";
  }
  string line;
  
  set<pair<string, string>> pairs;
  
  while ( getline(input, line) ) {
    
    string number1 = "";
    if ( line[0] != '(' ) { //the first one must be '('
      cerr << "Parse error ( '(' ): " << line << endl;  
      return 3;
    }
    
    int i = 1;
    while ( line[i] <= '9' && line[i] >= '0' ) {//add numbers one by one
      number1 += line[i];
      ++i;
    }
    
   //find separator
    size_t separator = line.find(sep);
    if ( separator == string::npos ) {
      cerr << "Parse error: " << line << endl;
      return 4;
    }
    
    //skip the separator. Its length + 1
    
    separator += sep.length() + 1;
    
    i = separator;
    
    if ( line[i] != '(' ) { //check if it is really the part it should be
      cerr << "Parse error ( '(' ): " << line << endl;
      return 5;
    }
    
    i++;
    string number2;
    
    while ( line[i] <= '9' && line[i] >= '0' ) {  //collect other number
      number2 += line[i];
      ++i;
    }
    
    pair<string, string> par(number1, number2); //A-B
    pair<string, string> rpar(number2, number1);// B-A
    
    if ( pairs.find(par) == pairs.end() && pairs.find(rpar) == pairs.end() ) {//none of them is found
      pairs.insert(par);
      cout << line << endl;
    }
  }
  
  
  cout << "Number of actual pairs: " << pairs.size() << endl;
  return 0;
  
}
