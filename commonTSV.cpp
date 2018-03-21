#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Record {
  public:
    string transformed;
    string soot;
    string sm;
    string spoon;
    string chp;
    string gous;
    
    Record(string t) : transformed(t) {
      
      soot = "x";
      sm = "x";
      spoon = "x";
      chp = "x";
      gous = "x";
    }
  
    int commonNum() {
      
      int num = 0;
      if ( "x" != soot )
        ++num;
      if ( "x" != sm )
        ++num;
      if ( "x" != spoon )
        ++num;
      if ( "x" != chp )
        ++num;
      if ( "x" != gous )
        ++num;
      
      return num;
    }
    
    bool operator==(const string& str ) const {
      
      if ( str == transformed )
        return true;
      false;
    }
};


int main(int argc, char** argv) {
  
  if ( 6 != argc ) {
    
    cerr << "Meg kell adni az 5 toolnak a fájljait ebben a sorrendben: soot SM spoon CHP g..." << endl;
    return 1;
  }
  
  vector<Record> methods;
  
  ofstream out("common.tsv");
  ifstream soot(argv[1]);
  ifstream sm(argv[2]);
  ifstream spoon(argv[3]);
  ifstream chp(argv[4]);
  ifstream gous(argv[5]);
  
  string tool, trans, rep;
  string line;
  soot >> tool >> trans >> rep; //get the header
  cout << "soot" << endl;
  
  getline(soot, line);
  cout << line << endl;
  while( getline(soot, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    cout << tool << " " << trans << " " << rep << endl;
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->soot = rep;
    }
    else {
      Record r(trans);
      r.soot = rep;
      methods.push_back(r);
    }
  }
  //----
  cout << "sm" << endl;
  sm >> tool >> trans >> rep; //get the header
  getline(sm, line);
  cout << line << endl;
  while( getline(sm, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    cout << tool << " " << trans << " " << rep << endl;
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->sm = rep;
    }
    else {
      Record r(trans);
      r.sm = rep;
      methods.push_back(r);
    }
  }
  //-------
  cout << "spoon" <<endl;
  spoon >> tool >> trans >> rep; //get the header
  getline(spoon, line);
  cout << line << endl;
  while( getline(spoon, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    cout << tool << " " << trans << " " << rep << endl;
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->spoon = rep;
    }
    else {
      Record r(trans);
      r.spoon = rep;
      methods.push_back(r);
    }
  }
  //-------
  chp >> tool >> trans >> rep; //get the header
  cout << "chp" << endl;
  getline(chp, line);
  cout << line << endl;
  while( getline(chp, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    //cout << tool << " " << trans << " " << rep << endl;
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->chp = rep;
    }
    else {
      Record r(trans);
      r.chp = rep;
      methods.push_back(r);
    }
  }
  
  
  //-------
  cout << "gous" << endl;
  gous >> tool >> trans >> rep; //get the header
  getline(gous, line);
  cout << line << endl;
  while( getline(gous, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    cout << tool << " " << trans << " " << rep << endl;
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->gous = rep;
    }
    else {
      Record r(trans);
      r.gous = rep;
      methods.push_back(r);
    }
  }
  //-------

  out << "Transformed" << "\t" << "matching" << "\t" << "soot.rep" << "\t" << "sm.rep" << "\t" << "spoon.rep" << "\t" << "chp.rep" << "\t" << "gous.rep" << endl;
  
  for ( int i = 0; i < methods.size(); i++ ) {
    
    out << methods[i].transformed << "\t" << methods[i].commonNum() << "\t" << methods[i].soot << "\t" << methods[i].sm << "\t" << methods[i].spoon << "\t" << methods[i].chp << "\t" << methods[i].gous << endl;
  }
  
  return 0;
}