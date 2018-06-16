#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>
#include <iostream>

class Record {
  
  std::vector<std::pair<std::string, std::string>> sameMethods; //these string represent the same method only the way is different
  std::string methodClass;  //the method is inside of a class (with package name!)
  std::string methodName;
  std::vector<std::string> parameters;  //the method has parameters.
  std::string unifiedRep;
  std::string secondaryRep;

  std::string createUnifiedMethodName();
  
  public:
    Record( std::pair<std::string, std::string> rep, std::string methodClass, std::string methodName, std::vector<std::string> parameters);
    //just for those that's rep is an id
    Record( std::pair<std::string, std::string> rep, std::string methodClass, std::string methodName, std::vector<std::string> parameters, std::string secondaryRep);
    
    bool operator==( const Record& r ) const;
    bool operator==( const std::pair<std::string, std::string> m ) const;
    bool operator==( const std::string& unifiedNode ) const;
    /**
    * \param  A record, but this time the record is not compared to the original classname but every '$' is replaced with '.'
    * \return a bool value if the 2 records, this and the parameter, are equal
    */
    bool operator>>=( const Record& r ) const;
    Record& operator+=( const std::pair<std::string, std::string> newWayOfRepresentation );
    Record& operator+=( const Record& r );
    bool operator<( const Record& r ) const;
  
    std::string getSecondaryRepresentation() const;
  
    std::string getClass() const;
    std::string getMethodName() const;
    std::vector<std::string> getParameters() const;
    std::vector<std::pair<std::string, std::string>> getSameMethods() const;
    
    
    
    friend std::ostream& operator<<(std::ostream& o, const Record& r);
};

#endif