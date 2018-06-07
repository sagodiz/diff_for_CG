#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#ifdef DEBUG
  #define DDD cout << line << endl;
#else
  #define DDD ;
#endif

#define SOOT_NUM 1
#define SM_NUM 2
#define SPOON_NUM 4
#define JCG_NUM 8
#define WALA_NUM 16


class Record {
  public:
    string transformed;
    string soot;
    string sm;
    string spoon;
    string gous;
    string wala;
    int metszet;
    
    Record(string t) : transformed(t) {
      
      soot = "x";
      sm = "x";
      spoon = "x";
      gous = "x";
      wala = "x";
      metszet = 0;
    }
  
    int commonNum() {
      
      int num = 0;
      if ( "x" != soot ) {
        ++num;
      }
      if ( "x" != sm ) {
        ++num;
      }
      if ( "x" != spoon ) {
        ++num;
      }
      if ( "x" != gous ) {
        ++num;
      }
      if ( "x" != wala ) {
        ++num;
      }
      
      return num;
    }
  
    int getMetszet() {
      
      if ( "x" != soot ) {
        metszet |=  SOOT_NUM;
      }
      if ( "x" != sm ) {
        metszet |=  SM_NUM;
      }
      if ( "x" != spoon ) {
        metszet |=  SPOON_NUM;
      }
      if ( "x" != gous ) {
        metszet |=  JCG_NUM;
      }
      if ( "x" != wala ) {
        metszet |=  WALA_NUM;
      }
      
      return metszet;
    }

	std::string getMetszetAsString() {
		std::string metszet = "";
		if ("x" != soot) {
			metszet += transformed;
		}
		metszet += ";";
		if ("x" != sm) {
			metszet += transformed;
		}
		metszet += ";";
		if ("x" != spoon) {
			metszet += transformed;
		}
		metszet += ";";
		if ("x" != gous) {
			metszet += transformed;
		}
		metszet += ";";
		if ("x" != wala) {
			metszet += transformed;
		}
		return metszet;
	}
    
    bool operator==(const string& str ) const {
      
      if ( str == transformed )
        return true;
      
      return false;
    }
};

class RecordConn {
  
  public:
    string connection;
    string soot;
    string spoon;
    string sm;
    string gous;
    string wala;
    int metszet;
    
    RecordConn( string str ) : connection(str) {
      
      soot = "";
      spoon = "";
      sm = "";
      gous = "";
      wala = "";
      metszet = 0;
    }
    
    int commonNum() {
      
      int num = 0;
      if ( "" != soot ) {
        ++num;
      }
      if ( "" != sm ) {
        ++num;
      }
      if ( "" != spoon ) {
        ++num;
      }
      if ( "" != gous ) {
        ++num;
      }
      if ( "" != wala ) {
        ++num;
      }
      
      return num;
    }
  
    int getMetszet() {
      
      if ( "" != soot ) {
        metszet |=  SOOT_NUM;
      }
      if ( "" != sm ) {
        metszet |=  SM_NUM;
      }
      if ( "" != spoon ) {
        metszet |=  SPOON_NUM;
      }
      if ( "" != gous ) {
        metszet |=  JCG_NUM;
      }
      if ( "" != wala ) {
        metszet |=  WALA_NUM;
      }
      
      return metszet;
    }

	std::string getMetszetAsString() {
		std::string metszet = "";
		if ("x" != soot) {
			metszet += connection;
		}
		metszet += ";";
			if ("x" != sm) {
				metszet += connection;
			}
		metszet += ";";
			if ("x" != spoon) {
				metszet += connection;
			}
		metszet += ";";
			if ("x" != gous) {
				metszet += connection;
			}
		metszet += ";";
			if ("x" != wala) {
				metszet += connection;
			}
		return metszet;
	}
    
    bool operator==(const string& str ) const {
      
      if ( str == connection )
        return true;
      return false;
    }
};

int main(int argc, char** argv) {
  
  ifstream soot ;
  ifstream sm;
  ifstream spoon;
  ifstream gous;
  ifstream wala;
  
  ifstream sootConn;
  ifstream smConn;
  ifstream spoonConn;
  ifstream chpConn;
  ifstream gousConn;
  ifstream walaConn;
  
  if ( 3 == argc ) {
    ifstream input(argv[1]);
    string file2open;
    
    input >> file2open;
    gous.open(file2open);
    
    input >> file2open;
    soot.open(file2open);
    
    input >> file2open;
    sm.open(file2open);
    
    input >> file2open;
    spoon.open(file2open);
    
    input >> file2open;
    wala.open(file2open);
    //--------------------------------------
    input.close();
    input.open(argv[2]);
    //--------------------------------------

    input >> file2open;
    gousConn.open(file2open);
    
    input >> file2open;
    sootConn.open(file2open);
    
    input >> file2open;
    smConn.open(file2open);
    
    input >> file2open;
    spoonConn.open(file2open);
    
    input >> file2open;
    walaConn.open(file2open);
    
    input.close();
  }
  else {
    
    if ( 9 != argc ) {

      cerr << "Meg kell adni az 5 toolnak a fájljait ebben a sorrendben: JCG soot sm spoon JCGConn sootConn smConn spoonConn" << endl;
      return 1;
    }
    int index = 1;
    
    gous.open(argv[index++]);
    soot.open(argv[index++]);
    sm.open(argv[index++]);
    spoon.open(argv[index++]);
    
    
    gousConn.open(argv[index++]);
    sootConn.open(argv[index++]);
    smConn.open(argv[index++]);
    spoonConn.open(argv[index++]);
  
  }
  
//------load connections-------
  vector<RecordConn> connections;
  string linec, connStr, toolc;
  
  ofstream connout("commonConnections.tsv");

  ofstream vennC("commonConnectionsVenn.csv");
  vennC << "gous;soot;sm;spoon;wala";
  
  //-------------------------gous---------------
  gousConn >> connStr >> toolc; 
  cout << "gous connections" << endl;
  
  getline(gousConn, linec);
  
  while ( getline(gousConn, linec) ) {

    stringstream input_stringstream(linec);

    getline(input_stringstream, connStr , '\t');
    getline(input_stringstream, toolc , '\t');

    
    auto it = find(connections.begin(), connections.end(), connStr);
    if ( it != connections.end() ) {
      //megtalalta
      it->gous = "X";
    }
    else {
      RecordConn r(connStr);
      r.gous = "X";
      connections.push_back(r);
    }
  }
  //-----------------soot----------
  sootConn >> connStr >> toolc;
  cout << "soot connections" << endl;
  
  getline(sootConn, linec);
  
  while ( getline(sootConn, linec) ) {
    
    stringstream input_stringstream(linec);

    getline(input_stringstream, connStr , '\t');
    getline(input_stringstream, toolc , '\t');
    
    auto it = find(connections.begin(), connections.end(), connStr);
    if ( it != connections.end() ) {
      //megtalalta
      it->soot = "X";
    }
    else {
      RecordConn r(connStr);
      r.soot = "X";
      connections.push_back(r);
    }
  }
  //-------------sm-------------
  smConn >> connStr >> toolc; 
  cout << "sm connections" << endl;
  
  getline(smConn, linec);
  
  while ( getline(smConn, linec) ) {
    
    stringstream input_stringstream(linec);

    getline(input_stringstream, connStr , '\t');
    getline(input_stringstream, toolc , '\t');
    
    auto it = find(connections.begin(), connections.end(), connStr);
    if ( it != connections.end() ) {
      //megtalalta
      it->sm = "X";
    }
    else {
      RecordConn r(connStr);
      r.sm = "X";
      connections.push_back(r);
    }
  }
  //----------spoon-----------
  spoonConn >> connStr >> toolc; 
  cout << "spoon connections" << endl;
  
  getline(spoonConn, linec);
  
  while ( getline(spoonConn, linec) ) {
    
    stringstream input_stringstream(linec);

    getline(input_stringstream, connStr , '\t');
    getline(input_stringstream, toolc , '\t');
    
    auto it = find(connections.begin(), connections.end(), connStr);
    if ( it != connections.end() ) {
      //megtalalta
      it->spoon = "X";
    }
    else {
      RecordConn r(connStr);
      r.spoon = "X";
      connections.push_back(r);
    }
  }
  //-----wala------
  walaConn >> connStr >> toolc; 
  cout << "wala connections" << endl;
  
  getline(walaConn, linec);
  
  while ( getline(walaConn, linec) ) {
    
    stringstream input_stringstream(linec);

    getline(input_stringstream, connStr , '\t');
    getline(input_stringstream, toolc , '\t');
    
    auto it = find(connections.begin(), connections.end(), connStr);
    if ( it != connections.end() ) {
      //megtalalta
      it->wala = "X";
    }
    else {
      RecordConn r(connStr);
      r.wala = "X";
      connections.push_back(r);
    }
  }
  //-----kiiras
  connout << "Connection" << "\t" << "matching" << "\t" << "soot" << "\t" << "sm" << "\t" << "spoon" << "\t" << "gous" << "\t" << "wala" << "\t" << "metszetID" << endl;
  
  for ( unsigned i = 0; i < connections.size(); i++ ) {
    
    connout << connections[i].connection << "\t" << connections[i].commonNum() << "\t" << connections[i].soot << "\t" << connections[i].sm << "\t" << connections[i].spoon << "\t" << connections[i].gous << "\t" << connections[i].wala << "\t" << connections[i].getMetszet() << endl;
  
	vennC << connections[i].getMetszetAsString() << std::endl;
  }
  
  connout.close();
  vennC.close();
  
//-----load methods----------  
  vector<Record> methods;
  
  ofstream out("commonMethods.tsv");

  ofstream venn("commonMethodsVenn.csv");
  venn << "gous;soot;sm;spoon;wala";
  string tool, trans, rep;
  string line;
  
  //---------------------------------
  
  cout << "gous" << endl;

  gous >> tool >> trans >> rep; //get the header
  getline(gous, line);
DDD
  while( getline(gous, line) ) {
DDD    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
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
  //------------------------------------------
  
  soot >> tool >> trans >> rep; //get the header
  cout << "soot" << endl;
 
  getline(soot, line);
DDD
  while( getline(soot, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');

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
DDD
  while( getline(sm, line) ) {
    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
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
DDD
  while( getline(spoon, line) ) {
DDD
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
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

  cout << "wala" << endl;

  wala >> tool >> trans >> rep; //get the header
  getline(wala, line);
DDD
  while( getline(wala, line) ) {
DDD    
    stringstream input_stringstream(line);

    getline(input_stringstream, tool , '\t');
    getline(input_stringstream, trans , '\t');
    getline(input_stringstream, rep , '\t');
    
    auto it = find(methods.begin(), methods.end(), trans);
    if ( it != methods.end() ) {
      //megtalalta
      it->wala = rep;
    }
    else {
      Record r(trans);
      r.wala = rep;
      methods.push_back(r);
    }
  }
  
  //---kiírás
  out << "Transformed" << "\t" << "matching" << "\t" << "soot.rep" << "\t" << "sm.rep" << "\t" << "spoon.rep" << "\t" << "gous.rep" << "\t" << "wala.rep" << "\t" << "metszetID" << endl;
  
  for ( unsigned i = 0; i < methods.size(); i++ ) {
    
    out << methods[i].transformed << "\t" << methods[i].commonNum() << "\t" << methods[i].soot << "\t" << methods[i].sm << "\t" << methods[i].spoon << "\t" << methods[i].gous << "\t" << methods[i].wala << "\t" << methods[i].getMetszet() << endl;
  
	venn << methods[i].getMetszetAsString() << std::endl;
  }
  
  out.close();
  venn.close();
  
  return 0;
}
