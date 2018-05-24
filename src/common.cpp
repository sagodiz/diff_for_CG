#include "../inc/common.h"
#include<iostream>
namespace common {
  
  std::vector<Record> storedIds;
  std::vector<std::string> tsvFiles;
  std::vector<std::string> connTSVFiles;

  bool unifyeAnonymClasses( std::string& str ) {
    
    bool replaced = false;
    
    for ( unsigned i = 0; i < str.length() - 1; i++ ) {
      
      if ( '$' == str[i] && str[i + 1] >= '0' && str[i + 1] <= '9' ) {
        //so it is an inner class, what's more an anonym class
        //str.replace(i+1, str.length(), "UNIFIEDANONYMCLASSNAME");
        str.erase(i+1);
        str += "UNIFIEDANONYMCLASSNAME";
        replaced = true;
        break;
      }
    }
    
    return replaced;
  }
}

namespace common {
  
  namespace options {
	unsigned char loadToGraph = 0;
    unsigned char CHPTransform = 0;
    unsigned char anonymClassNameTransform = 0;
  }
}