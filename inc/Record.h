#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>

class Record {
  
  std::vector<std::string> sameMethods; //these string represent the same method only the way is different
  std::string package; //the method must be in a package.
  std::string methodClass;  //the method is inside of a class
  std::string methodName;
  std::vector<std::string> parameters;  //the method has parameters.
  
  public:
    Record( std::string rep, std::string package, std::string methodClass, std::string methodName, std::vector<std::string> parameters);
    bool operator==( const Record& r ) const;
    bool operator==( const std::string m ) const;
    Record& operator+( const std::string newWayOfRepresentation );
    Record& operator+( const Record& r );
  
    std::string getPackage() const;
    std::string getClass() const;
    std::string getMethodName() const;
    std::vector<std::string> getParameters() const;
    std::vector<std::string> getSameMethods() const;
};

#endif