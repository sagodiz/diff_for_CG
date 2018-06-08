#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "inc/Labels.h"
#include "inc/Loader.h"
#include "inc/Loader_soot.h"
#include "inc/Loader_callerhierarchy.h"
#include "inc/Loader_sourcemeter.h"
#include "inc/Loader_gousiosg.h"
#include "inc/Loader_wala.h"
#include "inc/Switch.h"
#include "inc/common.h"
#include "inc/GraphDBCommon.h"
#include "inc/Record.h"
#include "inc/Factory.h"
#include "inc/OptionMethods.h"
#include "inc/Option.h"

#if defined(VERBOSE)
  #define VERBOSE1 \
    cout << "------" << loaders[i] << "--------" << endl;\
    for ( pair<int, int> it : connections[i] ) {\
      \
      cout << it.first << " " << it.second << endl;\
    }\
    cout << "-------------------------------------" << endl;\
    cout << loaders[i]->getMethodNum() << " method has been processed and " << endl << loaders[i]->getCallNum() << "call has been transformed." << endl;\
    cout << "-------end of " << loaders[i] << "--------" << endl;
#else
  #define VERBOSE1 ;
#endif


using namespace std;

struct StatData {
	unsigned methodCountForLoader1, methodCountForLoader2;
	unsigned callCountForLoader1, callCountForLoader2;
	unsigned commonMethodCount, commonCallCount;
};

static std::pair<unsigned long long, unsigned long long> makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Named * l1, Named * l2, vector<Record> r1, vector<Record> r2);
static void makeGraphDBStat(const std::vector<std::string>& labels);

template<typename T>
void printValue(FILE * common_file, const T& value);

template<>
void printValue(FILE * common_file, const float& value) {
	fprintf(common_file, "%.4f;", value);
}

template<>
void printValue(FILE * common_file, const unsigned long long& value) {
	fprintf(common_file, "%llu;", value);
}

template<typename T>
void printMatrix(const std::vector<Named*>& loaders, const std::vector<std::vector<T>>& mat, FILE * common_file, const std::string& type) {
	fprintf(common_file, "%s;", type.c_str());
	for (unsigned i = 0; i < mat.size(); ++i) {
		fprintf(common_file, "%s;", loaders[i]->getName().c_str());
	}
	fprintf(common_file, "\n");

	for (unsigned i = 0; i < mat.size(); ++i) {
		fprintf(common_file, "%s;", loaders[i]->getName().c_str());
		for (unsigned j = 0; j < mat.size(); ++j) {
			printValue<T>(common_file, mat[i][j]);
		}
		fprintf(common_file, "\n");
	}
	fprintf(common_file, "\n");
}



static void writeTSV(vector<Record>, string, string);
static void writeConnTSV( set<pair<int, int>>, string);

int main( int argc, char** argv ) {

  if ( argc < 3 ) {
    
    cout << "At least 1 tool have to be given." << endl;
    return 1;
  }
  
  cout << "Starting transforming and making stat..." << endl;
  
  try { 

  Factory factory = Factory::createFactory();
  
  Switch* switches[] = {
                          new Switch("-s", factory ),
                          new Switch("-c", factory ),
                          new Switch("-sm", factory ),
                          new Switch("-sp", factory ),
                          new Switch("-g", factory ),
                          new Switch("-w", factory ),
						              new Switch("-t", factory),
                          NULL
                        };

  Option* options[] = {
                          new Option("-projectName", &projectNameMethod),
						              new Option("-filterLevel", &filterLevelMethod),
						              new Option("-projectPath", &projectPathMethod),
						              new Option("-calcUnionGraph", &calcUnionGraphMethod),
						              new Option("-transformToGraphDB", &transformToGraphDB),
                          new Option("-CHPtransformation", &cHPTransformationMethod),
                          new Option("-anonymTransformation", &anonymClassNameTransformationMethod),
                          NULL
                      };
    
  //need pointer otherwise vector do not accept as Loader is abstract
  vector<Loader*> loaders;
  vector<Named*> loadersAndUnionG;

Switch* chp = NULL;
int chpArgIndex = -1;
unsigned counters[8] = {0};
  unsigned char j = -1;
  while( switches[++j] ) {
    
    for ( int i = 1; i < argc - 1; i++ ) {
      
      if ( *(switches[j]) == argv[i] ) {
        
        if ( *(switches[j]) == "-c" ) {
          //if it is chp note it and add it later so it wold run for last.
          chp = switches[j];
          chpArgIndex = ++i;
        }
        else {
          //it is not chp. add it.
          switches[j]->init(argv[++i]);
          loaders.push_back( switches[j]->getLoaderPointer(counters[j]++) );
		      loadersAndUnionG.push_back(*loaders.rbegin());
        }
      }
    }
  }
  
  if ( chp ) {
    
    chp->init(argv[chpArgIndex]);
    loaders.push_back( chp->getLoaderPointer(0) ); //fuck the chp
	  loadersAndUnionG.push_back(*loaders.rbegin());
  }
    
  if ( 0 == loaders.size() )
    throw Labels::NO_LOADER_WERE_GIVEN;
  
  j = -1;
  while( options[++j] ) {
    
    for ( int i = 0; i < argc - 1; i++ ) {
      
      if ( *(options[j]) == argv[i] ) {
        
        options[j]->foo(argv, i);
        break;
      }
    }
  }

  if (common::options::loadToGraph == 2) {//csak graf db stat
    
	  std::vector<std::string> graph_ids;
	  GraphDBCommon::loadDBLabelsFromFile(graph_ids, Labels::PROJECT_NAME);
	  makeGraphDBStat(graph_ids);
	  return 0;
  }

  //create an array for the transformed connections
  std::vector<set<pair<int, int>>> connections;
  connections.resize(loaders.size()); //this size won't be the same always!
  std::vector<vector<Record>> records;
  records.resize(loaders.size()); //this neither

  std::set<std::pair<int, int>> unionGraphEdges;
  std::vector<Record> unionGraphNodes;
    
  for (unsigned i = 0; i < loaders.size(); ++i ) {
    
    records[i] = loaders[i]->load();
    connections[i] = loaders[i]->transformConnections();
    
	  if (common::options::calculateUnionGraph) {
		  //collect edges
		  unionGraphEdges.insert(connections[i].begin(), connections[i].end());
	  }
	
    VERBOSE1
    if (common::options::filterLevel > 0) {
      
      std::set<int> filteredIds;
      records[i] = common::filterNodes(records[i], filteredIds);
      connections[i] = common::filterConnections(connections[i], filteredIds);	
    }
    
    common::printFilteredMethod(loaders[i]->getName(), records[i]);
  }
  
  if (common::options::calculateUnionGraph) {
    
   if (common::options::filterLevel > 0) {
	  //filter the union graph
	  std::set<int> filteredIds;
	  unionGraphNodes = common::filterNodes(common::storedIds, filteredIds);
	  unionGraphEdges = common::filterConnections(unionGraphEdges, filteredIds);
   }
   else {
     
	  unionGraphNodes = common::storedIds;
   }

	  records.push_back(unionGraphNodes);
	  connections.push_back(unionGraphEdges);
	  loadersAndUnionG.push_back(factory.getUnionGraphPointer());
  }


  //start generating various outputs, statistics..
  for ( unsigned i = 0; i < records.size() && i < loadersAndUnionG.size(); i++ ) { //the and is here just for safety, those two should be the same.
    
    writeTSV(records[i], loadersAndUnionG[i]->getName(), loadersAndUnionG[i]->getName());
    common::tsvFiles.push_back(loadersAndUnionG[i]->getKind() + Labels::PROJECT_NAME + loadersAndUnionG[i]->getName() + "loadedMethods.tsv");
  }
  
  {
    sort( common::tsvFiles.begin(), common::tsvFiles.end() );
    ofstream TSVFILE("tsvfiles.list");
    if ( !TSVFILE.is_open() )
      throw Labels::COULD_NOT_WRITE_FILE_LIST;
    
    for ( unsigned i = 0; i < common::tsvFiles.size(); i++ ) {
      
      TSVFILE << common::tsvFiles[i] << endl;
    }
  }
  
  for ( unsigned i = 0; i < connections.size() && i < loadersAndUnionG.size(); i++ ) { //that and is for safety too.
    
    writeConnTSV(connections[i], loadersAndUnionG[i]->getName());
    common::connTSVFiles.push_back(loadersAndUnionG[i]->getKind() + Labels::PROJECT_NAME + loadersAndUnionG[i]->getName() + "connections.tsv");
  }
  
  {
    sort( common::connTSVFiles.begin(), common::connTSVFiles.end() );
    ofstream CONNTSVFILE("conntsvfiles.list");
    if ( !CONNTSVFILE.is_open() )
      throw Labels::COULD_NOT_WRITE_FILE_LIST;
    
    for ( unsigned i = 0; i < common::connTSVFiles.size(); i++ ) {
      
      CONNTSVFILE << common::connTSVFiles[i] << endl;
    }
  }
//Edit's edit --------------------------------------------------------------------------
  std::vector<std::vector<unsigned>> statMatrix;

  for (unsigned i = 0; i < loadersAndUnionG.size() - 1; i++) {
	  statMatrix.resize(loadersAndUnionG.size());
  }

  std::vector<std::vector<float>> matrixCalls, matrixMethods;
  std::vector<std::vector<unsigned long long>> matrixCallsCount, matrixMethodsCount;
    
  matrixCalls.resize(loadersAndUnionG.size());
  matrixMethods.resize(loadersAndUnionG.size());
  matrixCallsCount.resize(loadersAndUnionG.size());
  matrixMethodsCount.resize(loadersAndUnionG.size());
    
  for (unsigned i = 0; i < loadersAndUnionG.size(); i++) {
    
	  matrixCalls[i].resize(loadersAndUnionG.size());
	  matrixMethods[i].resize(loadersAndUnionG.size());
	  matrixCallsCount[i].resize(loadersAndUnionG.size());
	  matrixMethodsCount[i].resize(loadersAndUnionG.size());
  }
    
  for (unsigned i = 0; i < loadersAndUnionG.size() - 1; i++ ) {
	  
    for (unsigned j = i + 1; j < loadersAndUnionG.size(); j++ ) {
      
    std::pair<unsigned long long, unsigned long long> commonVals = makeStat( connections[i], connections[j], loadersAndUnionG[i], loadersAndUnionG[j], records[i], records[j] );
	  float loader_i_callNum = (float)connections[i].size();
	  float loader_j_callNum = (float)connections[j].size();

	  float loader_i_uniqueMethod = (float)records[i].size();
	  float loader_j_uniqueMethod = (float)records[j].size();
	  //aranyok
	  matrixCalls[i][i] = loader_i_callNum;
	  matrixMethods[i][i] = loader_i_uniqueMethod;
	  matrixMethods[i][j] = commonVals.first / loader_i_uniqueMethod;
	  matrixCalls[i][j] = commonVals.second / loader_i_callNum;

	  matrixCalls[j][j] = loader_j_callNum;
	  matrixMethods[j][j] = loader_j_uniqueMethod;
	  matrixMethods[j][i] = commonVals.first / loader_j_uniqueMethod;
	  matrixCalls[j][i] = commonVals.second / loader_j_callNum;

	  //szamok
	  matrixCallsCount[i][i] = connections[i].size();
	  matrixMethodsCount[i][i] = records[i].size();
	  matrixMethodsCount[i][j] = commonVals.first;
	  matrixCallsCount[i][j] = commonVals.second;

	  matrixCallsCount[j][j] = connections[j].size();
	  matrixMethodsCount[j][j] = records[j].size();
	  matrixMethodsCount[j][i] = commonVals.first;
	  matrixCallsCount[j][i] = commonVals.second;
    }
  }
    
  std::string fname = Labels::PROJECT_NAME+"_filter_" + std::to_string(common::options::filterLevel) + "_common_calls_methods.csv";
  FILE * common_file = fopen(fname.c_str(), "w");

  if ( !common_file )
    throw Labels::PERCENTAGE_TABLE_FILE_COULD_NOT_OPEN + Labels::PROJECT_NAME + "_common_calls_methods.csv";
    
 
  printMatrix(loadersAndUnionG, matrixCalls, common_file, "calls");
  printMatrix(loadersAndUnionG, matrixMethods, common_file, "methods");

  printMatrix(loadersAndUnionG, matrixCallsCount, common_file, "callsCount");
  printMatrix(loadersAndUnionG, matrixMethodsCount, common_file, "methodsCount");

  fclose(common_file);

  if (common::options::loadToGraph != 0) {
    
	  std::vector<std::string> graph_ids;
	  if (common::options::loadToGraph == 1) {
		
      for (unsigned i = 0; i < records.size(); i++) {
			
        static const string graphml_ext = ".graphml";
			  static const string json_ext = ".json";
			  string filename = Labels::PROJECT_NAME + "_" + loaders[i]->getName();
			  graph_ids.push_back(filename);
			  GraphDBCommon::writeUnifiedGraphToGraphml(filename + graphml_ext, records[i], connections[i]);
			  GraphDBCommon::convertGraphmlToJson(filename + graphml_ext, filename + json_ext);
			  GraphDBCommon::uploadToDraphDB(filename + json_ext, i == 0, filename);
		  }
      
		  GraphDBCommon::saveDBLabelsToFile(graph_ids, Labels::PROJECT_NAME);
	  }
    
	  makeGraphDBStat(graph_ids);
	  
  }
//edit of Edit :P end--------------------------------------------------------------  
  //catch "all" thrown error...
  } catch( const string e ) {
    
    cerr << "An error has occurred: " << e << endl;
    
    return 1;
  }

  cout << "End of program." << endl;

  system("./commonTSV tsvfiles.list conntsvfiles.list");
  
  return 0;
}
//########################################################################x
//########################################################################x
//########################################################################x
//########################################################################x

static void makeGraphDBStat(const std::vector<std::string>& graph_ids) {
	if (graph_ids.size() == 0) {
		std::err << "No graph ids!" << std::endl;
	}
	else {
		for (unsigned i = 0; i < graph_ids.size() - 1; i++) {
			for (unsigned j = i + 1; j < graph_ids.size(); j++) {
				GraphDBCommon::compareInGraphDB(graph_ids[i], graph_ids[j]);
			}
		}
	}
}

static void writeConnTSV( set<pair<int, int>> connections, string name) {
  
  ofstream TSV(Labels::PROJECT_NAME + name + "connections.tsv");
  
  if ( !TSV.is_open() )
    throw Labels::COULD_NOT_WRITE_TSV;
  
  TSV << "caller->callee" << "\t" << name << endl;
  
  for ( pair<int, int> it : connections ) {
    
    TSV << "(" << it.first << ")" << common::getMethodById(it.first) << "->(" << it.second << ")" << common::getMethodById(it.second) << "\t" << name << endl;
  }
}

static void writeTSV( vector<Record> records, string name, string tool ) {
  
  ofstream TSV(Labels::PROJECT_NAME + tool + "loadedMethods.tsv");
  
  if ( !TSV.is_open() )
    throw Labels::COULD_NOT_WRITE_TSV;
  
  TSV << "name" << "\t" << "transformed-rep." << "\t" << "tool.rep" << endl;
  
  for ( unsigned i = 0; i < records.size(); i++ ) {
    
    TSV << name << "\t" << records[i] << "\t";
    //TODO: nem csak kiíratom, vagy a kiíratás lehetne mostmár szebb is
    
   // if ( records[i].getSameMethods().size() > 1 )
   //   throw Labels::TOOL_HAS_MORE_THAN_ONE_REP + name;
    
    TSV << records[i].getSameMethods().at(0).first + records[i].getSecondaryRepresentation() << endl;
  }
}

static std::pair<unsigned long long, unsigned long long> makeStat(set<pair<int, int>> compareSet1, set<pair<int, int>> compareSet2, Named * l1, Named * l2, vector<Record> r1, vector<Record> r2 ) {
  
  unsigned long long commonCalls = 0;
  unsigned long long commonCallsCheck = 0;
  unsigned long long commonMethods = 0;
  unsigned long long commonMethodsCheck = 0;
  
  vector<Record> onlyFirst;
  vector<Record> onlySecond;
  
  vector<pair<int, int>> onlyFirstCall;
  vector<pair<int, int>> onlySecondCall;
  
  ofstream statOut(Labels::PROJECT_NAME + l1->getName() + "-" + l2->getName() + "-common-calls.txt");
  
  //check calls
  if ( !statOut.is_open() )
    throw Labels::COULD_NOT_WRITE_OUTPUT;

  for ( auto it1 : compareSet1 ) {
    
    if ( compareSet2.find(it1) != compareSet2.end() ) {
      //found
      ++commonCalls;
    }
    else {
      
      onlyFirstCall.push_back(it1);
    }
  }
  
  for ( auto it2 : compareSet2 ) {
    
    if ( compareSet1.find(it2) != compareSet1.end() ) {
      //found
      ++commonCallsCheck;
    }
    else {

      onlySecondCall.push_back(it2);
    }
  }
  
  if ( commonCalls != commonCallsCheck )
    cerr << "The search for common calls failed" << endl;
   
  //check the methods
  for ( unsigned i = 0; i < r1.size(); i++ ) {
    
    if ( find(r2.begin(), r2.end(), r1[i]) != r2.end() ) {
      
      ++commonMethods;
    }
    else {
      //this method is not in the second tool's vector
      onlyFirst.push_back(r1[i]);
    }
  }
  
  for ( unsigned i = 0; i < r2.size(); i++ ) {
    
    if ( find(r1.begin(), r1.end(), r2[i]) != r1.end() ) {
      
      ++commonMethodsCheck;
    }
    else {
      //this method is not in the second tool's vector
      onlySecond.push_back(r2[i]);
    }
  }
  
  if ( commonMethodsCheck != commonMethods )
    cerr << "The search for common methods failed" << endl; 
  
  statOut << l1->getFilePath() << " has " << compareSet1.size() << " calls" << " and " << r1.size() << " unique methods. " << endl;
  statOut << l2->getFilePath() << " has " << compareSet2.size() << " calls" << " and " << r2.size() << " unique methods. " << endl;
  statOut << commonCalls << " common calls and " << commonMethods << " common methods." << endl;
  
  //write the differences
  statOut << "Only the " << l1->getName() << " contains this/these method(s):" << endl;
  
  for ( unsigned i = 0; i < onlyFirst.size(); i++ ) {
    
    statOut << onlyFirst[i] << endl;
  }
  
  statOut << "Only the " << l2->getName() << " contains this/these method(s):" << endl;
  
  for ( unsigned i = 0; i < onlySecond.size(); i++ ) {
    
    statOut << onlySecond[i] << endl;
  }
  
  statOut << "Only the " << l1->getName() << " contains this/these call(s):" << endl;
  
  for ( unsigned i = 0; i < onlyFirstCall.size(); i++ ) {
    
    statOut << onlyFirstCall[i].first << " [" << common::getMethodById(onlyFirstCall[i].first) << "] " << onlyFirstCall[i].second << " [" << common::getMethodById(onlyFirstCall[i].second) << " ]" << endl;
  }
  
  statOut << "Only the " << l2->getName() << " contains this/these call(s):" << endl;
  
  for ( unsigned i = 0; i < onlySecondCall.size(); i++ ) {
    
    statOut << onlySecondCall[i].first << " [" << common::getMethodById(onlySecondCall[i].first) << "] " << onlySecondCall[i].second << " [" << common::getMethodById(onlySecondCall[i].second) << " ]" << endl;
  }
  
  statOut.close();

  return std::make_pair(commonMethods, commonCalls);
}
