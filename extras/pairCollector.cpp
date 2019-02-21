#include<iostream>
#include<fstream>
#include<set>

using namespace std;

int main(int argc, char** argv) {
  
  if ( argc < 2 ) {
    cout << "File to collect pairs from needed. [separator] by default it is \"---\"" << endl;
    cout << "This file collects distinct method pairs. (A-B B-A duplications are removed)" << endl;
    return 1;
  }
  
  ifstream input(argv[1]);
  if ( !input.is_open() ) {
    cerr << "File megnyitás nem sikerült: " << argv[1] << endl;
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
    if ( line[0] != '(' ) { //ugye az első karakter ( kell, hog ylehyen
      cerr << "Parse error ( '(' ): " << line << endl;  
      return 3;
    }
    
    int i = 1;
    while ( line[i] <= '9' && line[i] >= '0' ) {//hozzáadom a számokat sorban
      number1 += line[i];
      ++i;
    }
    
    //size_t separator = line.find("---");  //megkeresem ezt
    size_t separator = line.find(sep);
    if ( separator == string::npos ) {
      cerr << "Parse error: " << line << endl;
      return 4;
    }
    
    //separator += 4; //átugrom
    
    separator += sep.length() + 1;
    
    i = separator;
    
    if ( line[i] != '(' ) { //megnézem, hogy tényleg jó dolog következik-e
      cerr << "Parse error ( '(' ): " << line << endl;
      return 5;
    }
    
    i++;
    string number2;
    
    while ( line[i] <= '9' && line[i] >= '0' ) {  //ismét kiszedem a számokat
      number2 += line[i];
      ++i;
    }
    
    pair<string, string> par(number1, number2); //a rendes "A-B" pár
    pair<string, string> rpar(number2, number1);// a fordított "B-A"
    
    if ( pairs.find(par) == pairs.end() && pairs.find(rpar) == pairs.end() ) {//ha egyik sincs benne, akkor új.
      pairs.insert(par);
      cout << line << endl;
    }
  }
  
  
  cout << "Number of actual pairs: " << pairs.size() << endl;
  return 0;
  
}
