#include "../inc/common.h"
#include "../inc/Loader.h"
#include "../inc/Labels.h"
#include<numeric>
#include<iostream>

namespace common {
  
  std::vector<Record> storedIds;
  std::vector<std::string> tsvFiles;
  std::vector<std::string> connTSVFiles;
  bool TRACE_RUN = false;
  bool JUST_TRACE_RUN = false;
  std::string sootTagging = "";
  std::string jdtTagging = "";
  std::vector<std::string> approxTools;
  
  void cutPckgClass(const std::string pckgClass, std::string& pckg, std::string& classStr) {
    size_t genericSign = pckgClass.find("<");
    size_t lastDot = 0;
    
    if (genericSign != std::string::npos) {

      lastDot = genericSign;
      while (lastDot != 0 && pckgClass[lastDot] != '.') {

        --lastDot;
      }

      if (lastDot != 0) {

        pckg = pckgClass.substr(0, lastDot);
        classStr = pckgClass.substr(lastDot + 1);
      }
      else {
        classStr = pckgClass;
      }
    }
    else {

      lastDot = pckgClass.rfind(".");
      if (lastDot == std::string::npos) {
        classStr = pckgClass;
      }
      else {
        pckg = pckgClass.substr(0, lastDot);
        classStr = pckgClass.substr(lastDot + 1);
      }
    }    
  }
    void cutPckgClassMethod(const std::string pckClassMethod, std::string& pckg, std::string& clazz, std::string& method) {

    size_t par = pckClassMethod.rfind('(');
    if ( par == std::string::npos )
      return;

    size_t last_dot = pckClassMethod.substr(0, par).rfind(".");

    method = pckClassMethod.substr(last_dot + 1);

    cutPckgClass(pckClassMethod.substr(0, last_dot), pckg, clazz);
  }

  bool unifyeAnonymClasses( std::string& str ) {
    
    bool replaced = false;
    
    for ( unsigned i = 0; i < str.length() - 1; i++ ) {
      
      if ( '$' == str[i] && str[i + 1] >= '0' && str[i + 1] <= '9' ) {
        
        str.erase(i+1);
        str += "UNIFIEDANONYMCLASSNAME";
        replaced = true;
        break;
      }
    }
    
    return replaced;
  }
  
  bool unifyeAnonymMethods( std::string& str ) {
    
    bool replaced = false;
    
    for ( unsigned i = 0; i < str.length() - 1; i++ ) {
      
      if ( '$' == str[i] && str[i + 1] >= '0' && str[i + 1] <= '9' ) {
        
        str.erase(i+1);
        str += "UNIFIEDANONYMMETHODNAME";
        replaced = true;
        break;
      }
    }
    
    return replaced;
  }
  
  void printFilteredMethod(const std::string& loadername, std::vector<Record> records) {
    std::ofstream of("non_filtered_methods_" + loadername + "_unified");
    if (!of.is_open()) {
      return;
    }
    of << records.size() << std::endl;
    std::sort(records.begin(), records.end(), [](const Record& lhs, const Record& rhs) {
      return lhs.getSecondaryRepresentation().compare(rhs.getSecondaryRepresentation()) < 0;
    });
    for (const auto& meth : records) {
      of << meth.getSecondaryRepresentation() << std::endl;
    }
    of.close();
  }

  std::vector<Record> filterNodes(const std::vector<Record>& unfiltered, std::set<int>& filteredIds) {
    std::vector<Record> filteredNodes;
    auto findId = [](const Record& c)->unsigned {
      for (unsigned i = 0; i < common::storedIds.size(); ++i) {
        if (common::storedIds[i] == c) {
          return i;
      }
    }
      return 0;
    };
    for (unsigned i = 0; i < unfiltered.size(); ++i) {
      std::string method = unfiltered[i].getPackage() + "." + unfiltered[i].getClass() + "." + unfiltered[i].getMethodName();
      if (!isExclude(method)) {
        filteredNodes.push_back(unfiltered[i]);
      }
      else {
        filteredIds.insert(findId(unfiltered[i]));
      }
    }
    return filteredNodes;
  }
  std::set<std::pair<int, int>> filterConnections(const std::set<std::pair<int, int>>& unfiltered, const std::set<int>& filteredIds) {
    std::set<std::pair<int, int>> filtered;
    for (const auto& edge : unfiltered) {
      if (filteredIds.find(edge.first) != filteredIds.end() || filteredIds.find(edge.second) != filteredIds.end()) {
        continue;
      }
      filtered.insert(edge);
    }
    return filtered;
  }

  bool isJavaLib(const std::string& method) {
    const static std::set<std::string> excludes = { "java.", "sun.", "javax." };
    for (const std::string& anExclude : excludes) {
      if (method.find(anExclude) == 0) {
        return true;
      }
    }
    if (Labels::PROJECT_PATH.length() > 0 && method.find(Labels::PROJECT_PATH) != 0) {
      return true;
    }

    return false;
  }

  bool isExcludableInit(const std::string& name) {
    static const std::set<std::string> excludedInits = { "<init>", "<clinit>", "<initblock>" };
    for (const std::string& anExclude : excludedInits) {
      if (name.find(anExclude) != std::string::npos) {
        return true;
      }
    }
    return false;
  }

  bool isExclude(const std::string& method) {
    switch (common::options::filterLevel) {
    case 0:
      return false;
    case 1:
      return isJavaLib(method);
    case 2:
      return isJavaLib(method) || isExcludableInit(method);
    default:
      return false;
    }
  }


  std::string produceMethodPairingName() {
	  switch (common::options::resolve) {
	  case common::enums::methodRes::nothing: return "nothing";
	  case common::enums::methodRes::unio: return "unio";
	  case common::enums::methodRes::section: return "section";
	  default: return "dafaq";
	  }
  }

  std::string produceFileNamePrefix() {
	  return Labels::PROJECT_NAME + "_" + produceMethodPairingName() + "_";
  }

  
  namespace {
    bool notCaller(const std::set<std::pair<int, int>>& sootC, int id) {
      //std::cout << "Checking clinit " << id << std::endl;
      //std::cout << getMethodById(id) << std::endl;
      bool asd = find_if(sootC.begin(), sootC.end(), [&](const std::pair<int, int>& c){return c.first == id;}) == sootC.end();
      //std::cout << asd << std::endl;
      return asd;
    }
  }

  void calculateAndAddApprox(std::vector<std::vector<Record>>& records, 
                            std::vector<std::set<std::pair<int, int>>>& connections, 
                            std::vector<Named *>& loadersAndUnionG) {
    static unsigned approxIndex = 0;
    std::cout << "Number of calls considered too big: " << common::options::filterNumber << " Number of calls to use instead: " << common::options::approxAddedMethods << std::endl;

    std::string firstName = approxTools[approxIndex++];
    std::string secondName = approxTools[approxIndex++];

    Loader* first = nullptr;
    std::set<std::pair<int, int>> first_calls;
    for ( auto i = 0u; i < loadersAndUnionG.size(); ++i ) { // TODO: find?
      if ( firstName == loadersAndUnionG[i]->getName() ) {
        first = dynamic_cast<Loader*>(loadersAndUnionG[i]);
        first_calls = connections[i];
      }
    }

    if ( !first ) {
      throw Labels::APPROX_TOOL_ONE_NOT_FOUND;
    }

    Loader* second = nullptr;
    std::set<std::pair<int, int>> second_calls;
    for ( auto i = 0u; i < loadersAndUnionG.size(); ++i ) {
      if ( secondName == loadersAndUnionG[i]->getName() ) {
        second = dynamic_cast<Loader*>(loadersAndUnionG[i]);
        second_calls = connections[i];
      }
    }

    if ( !second ) {
      throw Labels::APPROX_TOOL_TWO_NOT_FOUND;
    }

    std::set<std::pair<int, int>> combined_calls;
    size_t skipped = 0;
    size_t clskipp = 0;
    for(auto call : first_calls ) {
      /*if( common::getMethodById(call.second).find("clinit") != std::string::npos ) {
         std::cout << "clinit omg" << std::endl;
      }*/
      if ( common::getMethodById(call.second).rfind("java", 0) != std::string::npos ) {
        // std::cout << "Skipping" <<std::endl;
        ++skipped;
      }
      else if( common::getMethodById(call.second).find("clinit") != std::string::npos && notCaller(first_calls, call.second) ) {
        //std::cout << "Skipped clinit" << std::endl;
        ++clskipp;
      }
      else {
        combined_calls.insert(call);
      }
    }

    std::set<std::pair<int, int>> to_erase;
    std::set<std::pair<int, int>> to_add;


    for(auto call : combined_calls) {
      std::vector<int> similar_callees;
      std::string pckg, clazz, method;

      cutPckgClassMethod(common::getMethodById(call.second), pckg, clazz, method);
      
      auto similar_calls_num = count_if(combined_calls.begin(), combined_calls.end(), [&](const std::pair<int, int>& c){
          if ( call.first != c.first)
            return false;
          std::string pckg2, clazz2, method2;
          cutPckgClassMethod(common::getMethodById(c.second), pckg2, clazz2, method2);
            
          if ( method2 == method && clazz != clazz2) {
            
//            std::cout << "Sim call" << call.first << pckg2 << " " << pckg << " " << clazz2 << " " << clazz << " " << method2 << " " << method << std::endl;
            similar_callees.push_back(c.second);
            return true;
          }
          return false;
      });
//      std::cout << similar_calls_num << std::endl;
      if( similar_calls_num > common::options::filterNumber ) {
        for( auto id : similar_callees ) {
          to_erase.insert(std::make_pair(call.first, id));
        }
        unsigned i = 1;
        for( auto call_spoon : second_calls ) {
          if( call.first == call_spoon.first ) {
            std::string pckg2, clazz2, method2;
            cutPckgClassMethod(common::getMethodById(call_spoon.second), pckg2, clazz2, method2);
            if( method == method2 ) {
              to_add.insert(call_spoon);
              
              if ( common::options::approxAddedMethods != 0 && i > common::options::approxAddedMethods ) break;
              
              ++i;
            }
          }
        }
        to_erase.insert(call);
      }
    }

    for(auto e : to_erase) {
      //std::cout << "Deleting:" << common::getMethodById(e.first) << "->" << common::getMethodById(e.second) << std::endl;
      combined_calls.erase(e);
    }

    for (auto a : to_add) {
      combined_calls.insert(a);
    }

    /*for (auto call : combined_calls) {
      std::cout << common::getMethodById(call.first) << "->" << common::getMethodById(call.second) << std::endl;
    }*/
    std::cout << "Deleted: " << to_erase.size() << " added: " << to_add.size() << " skipped: " << skipped << " clskipped: " << clskipp << " Final size " << combined_calls.size() << std::endl;
    
    connections.push_back(combined_calls);
   
    class Approx : public Named {
      std::string name;
      public:
        Approx(const std::string& first, const std::string& second) : name(first + "-" + second) {}
        virtual std::string getName() const override { return name; }
        virtual std::string getFilePath() override { return "Approx"; }
        virtual std::string getKind() const override { return "A_"; }

    };
    loadersAndUnionG.push_back( new Approx(firstName, secondName) );
    
    std::set<int> approx_methods;
    for ( auto call : combined_calls ) {
      approx_methods.insert(call.first);
      approx_methods.insert(call.second);
    }
    std::vector<Record> approx_records;
    for ( auto methodID : approx_methods ) {
      approx_records.push_back(storedIds[methodID]);
    }
    records.push_back(approx_records);
  }


}

namespace common {
  
  namespace options {
    unsigned char loadToGraph = 0;
    unsigned char filterLevel = 0;
    unsigned char calculateUnionGraph = 0;
    unsigned char anonymClassNameTransform = 0;
    bool lineInfoPairing = false;
    unsigned char resolve = 0;
    unsigned char JDT_generics = common::enums::JDTGenerics::JDT_classAndParameters;
    bool onlyAnonymWithLineinfo = false;
    bool genericParameterTypesNames = false;
    bool initblock2init = true;
    bool calculateApprox = false;
    unsigned filterNumber = 5;
    unsigned approxAddedMethods = 1;
    unsigned approxNum = 0;
  }
}