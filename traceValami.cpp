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
    
    cerr << "Usage: ./" << argv[0] << " commonConnections.tsv commonMethods.tsv" << endl;
    return 1;
  }
  
  map<int, int> connections;
  map<int, int> methods;
  
  
  ifstream commonConnections;
  ifstream commonMethods;
  
  commonConnections.open(argv[1]);
  if ( !commonConnections.is_open() ) {
    
    cerr << "Could not open commonConnections.tsv" << endl;
    return 2;
  }
  
  string transformed, soot, osa, spoon, jcg, wala, trace;
  int section;
  int matching;
  
  commonConnections >> transformed >> matching >> soot >> osa >> spoon >> jcg >> wala >> trace >> section;  //get header.
  
  while ( commonConnections >> transformed >> matching >> soot >> osa >> spoon >> jcg >> wala >> trace >> section ) {  //process every row.
    
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
    
    commonConnectionsOut << sectionAsString(it->first) << "\t" << it->second << endl;
  }
  
  
  commonMethods.open(argv[2]);
  if ( !commonMethods.is_open() ) {
    
    cerr << "Could not open commonMethods.tsv" << endl;
    return 4;
  }
  
  commonMethods >> transformed >> matching >> soot >> osa >> spoon >> jcg >> wala >> trace >> section;  //get header.
  
  while ( commonMethods >> transformed >> matching >> soot >> osa >> spoon >> jcg >> wala >> trace >> section ) {  //process every row.
    
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
    
    commonMethodsOut << sectionAsString(it->first) << "\t" << it->second << endl;
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