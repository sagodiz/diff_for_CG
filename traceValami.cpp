#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


#define SOOT_NUM 1
#define OSA_NUM 2
#define SPOON_NUM 4
#define JCG_NUM 8
#define WALA_NUM 16
#define TRACE_NUM 32

std::string sectionAsString(int);


using namespace std;

int main( int argc, char** argv ) {
  
  if ( argc < 3 ) {
    
    cerr << "Usage: " << argv[0] << " commonConnections.tsv commonMethods.tsv" << endl;
    return 1;
  }
  
  map<int, int> connections;
  map<int, int> methods;
  map<int, int> connectionIdNum;
  map<int, int> methodIdNum;
  
  
  ifstream commonConnections;
  ifstream commonMethods;
  
  commonConnections.open(argv[1]);
  if ( !commonConnections.is_open() ) {
    
    cerr << "Could not open commonConnections.tsv" << endl;
    return 2;
  }
  
  string transformed, matchingStr, soot, osa, spoon, jcg, wala, trace, sectionStr;
  int section;
  //int matching;
  string line;
  
  getline(commonConnections, line);  //get header.
  
  while ( getline( commonConnections, line) ) {  //process every row.
    
    stringstream input_stringstream(line);

    getline(input_stringstream, transformed, '\t');
    getline(input_stringstream, matchingStr, '\t');
    getline(input_stringstream, soot, '\t');
    getline(input_stringstream, osa, '\t');
    getline(input_stringstream, spoon, '\t');
    getline(input_stringstream, jcg, '\t');
    getline(input_stringstream, wala, '\t');
    getline(input_stringstream, trace, '\t');
    getline(input_stringstream, sectionStr, '\t');
    
    section = atoi(sectionStr.c_str());
    
    connectionIdNum[section]++;
    
    if ( section & TRACE_NUM ) {
    
      section -= TRACE_NUM;
      connections[section]++;
    }
  }
  
  commonConnections.close();
  ofstream commonConnectionsOut("commonConnections2.tsv");
  
  if ( !commonConnectionsOut.is_open() ) {
    
    cerr << "Could not write commonConnections2.tsv" << endl;
    return 3;
  }
  
  for ( auto it = connections.begin(); it != connections.end(); ++it ) {
    //cout << "Print values: " << it->first << "and " << it->second << endl;
    commonConnectionsOut << sectionAsString(it->first) << "\t" << it->second << "\t" << connectionIdNum[it->first] << endl;
  }
  
  
  commonMethods.open(argv[2]);
  if ( !commonMethods.is_open() ) {
    
    cerr << "Could not open commonMethods.tsv" << endl;
    return 4;
  }
  
  getline(commonMethods, line);  //get header.
  
  while ( getline( commonMethods, line) ) {  //process every row.
    
    stringstream input_stringstream(line);

    getline(input_stringstream, transformed, '\t');
    getline(input_stringstream, matchingStr, '\t');
    getline(input_stringstream, soot, '\t');
    getline(input_stringstream, osa, '\t');
    getline(input_stringstream, spoon, '\t');
    getline(input_stringstream, jcg, '\t');
    getline(input_stringstream, wala, '\t');
    getline(input_stringstream, trace, '\t');
    getline(input_stringstream, sectionStr, '\t');
    
    section = atoi(sectionStr.c_str());
    
    methodIdNum[section]++;
    
    if ( section & TRACE_NUM ) {
      
      section -= TRACE_NUM;
      methods[section]++;
    }
  }
  
  commonMethods.close();
  ofstream commonMethodsOut("commonMethods2.tsv");
  
  if ( !commonMethodsOut.is_open() ) {
    
    cerr << "Could not write commonMethods2.tsv" << endl;
    return 3;
  }
  
  for ( auto it = methods.begin(); it != methods.end(); ++it ) {
    
    commonMethodsOut << sectionAsString(it->first) << "\t" << it->second << "\t" << methodIdNum[it->first] << endl;
  }
  
  return 0;
}


string sectionAsString( int id ) {
  
  string section;
  
  if ( id & SOOT_NUM )
    section += "Soot";
  section += "\t";
  if ( id & OSA_NUM )
    section += "OSA";
  section += "\t";
  if ( id & SPOON_NUM )
    section += "SPOON";
  section += "\t";
  if ( id & JCG_NUM )
    section += "JCG";
  section += "\t";
  if ( id & WALA_NUM )
    section += "WALA";
    
  return section;
}