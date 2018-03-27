#include <vector>
#include <algorithm> 
#include <cctype>
#include "Record.h"
#include <string>

namespace common {
  
  extern std::vector<Record> storedIds;
  extern std::vector<std::string> tsvFiles;
  extern std::vector<std::string> connTSVFiles;
  bool unifyeAnonymClasses( std::string& str );
  static inline std::string getMethodById( const unsigned int& id ) {
    
    if ( id < storedIds.size() ) {
      
      std::string params = "";
      for ( unsigned i = 0; i < storedIds[id].getParameters().size(); i++ ) {
        
        params += (storedIds[id].getParameters())[i] + ",";
      }
      //params.erase(params.length() - 1, 1); //the closing ','
      if ( ',' == params[params.length()-1] )
        params[params.length()-1] = ')';
      else
        params += ")";
      return storedIds[id].getClass() + "." + storedIds[id].getMethodName() + "(" + params;// + ")";
    }
    
    return "";
  }
  
  static inline void ltrim(std::string &s) {
	  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		  return !std::isspace(ch);
	  }));
  }

  static inline void rtrim(std::string &s) {
	  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		  return !std::isspace(ch);
	  }).base(), s.end());
  }

  static inline void trim(std::string &s) {
	  ltrim(s);
	  rtrim(s);
  }

  static inline bool checkAndSetId(const std::string& id_str, int& id_num) {
	  for (unsigned i = 0; i < common::storedIds.size(); i++) {
		  if (common::storedIds[i] == id_str) {
			  id_num = i;
			  return true;
		  }
	  }
	  return false;
  };
}

namespace common {
  
  namespace options {
    
    extern unsigned char CHPTransform;
    extern unsigned char anonymClassNameTransform;
  }
}