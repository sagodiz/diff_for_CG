#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

class Record {
  
  std::vector<std::pair<std::string, std::string>> sameMethods; //these string represent the same method only the way is different
  std::string package;  //package of the class thus the method
  std::string methodClass;  //the method is inside of a class
  std::string methodName;   //name of the method
  std::vector<std::string> parameters;  //the method has parameters.
  std::string unifiedRep; //we transform everything to this format
  std::map<std::string, std::vector<std::string>> secondaryRep; //some tools have a secondary rep. to identify methods when dealing with calls.
  int startLine = -1;  //default line is -1. It matches for everything sinc it indicates no information. 
  int endLine = -1; //end of the method.
  /*
  * The [start, end] should include the first expression
  * Byte code based tools have the line info of the first expression.
  */
  
  unsigned int properties;
  std::string declaringClass; //A Record is a method, it has a declaring class that may differ from the containing class (see polymorphism)
  
  std::string createUnifiedMethodName();
  
  public:
    Record( std::pair<std::string, std::string> rep, std::string package, std::string methodClass, std::string methodName, std::vector<std::string> parameters, int startLine = -1, int endLine = -1 );
    //just for those that's rep is an id
    Record( std::pair<std::string, std::string> rep, std::string package, std::string methodClass, std::string methodName, std::vector<std::string> parameters, std::pair<std::string, std::string> secondaryRep, int startLine = -1, int endLine = -1 );
    
    bool operator==( const Record& r ) const;
    bool operator==( const std::pair<std::string, std::string> m ) const;
    bool operator==( const std::string& unifiedNode ) const;
  
    /**
    * \param the method is already found by one of the tools, it just a new form from another method.
    * \return returns a Record, now containing the new form too.
    */
    Record& operator+=( const std::pair<std::string, std::string> newWayOfRepresentation );
  
    /**
    * \param a record of which method representations to be copied. 
    * \return returns an updated record.
    */
    Record& operator+=( const Record& r );
  
    /**
    * \param s a string for the additional secondary representations
    * \param t the tool whose representation it is.
    * \return returns an updated record.
    */
    Record& addSecondaryRepresentation( const std::string& s, const std::string& t );
    
    /**
    * \param a record to be compared to.
    * \return decides whether the given record is smaller or not.
    */
    bool operator<( const Record& r ) const;  //just in order to be able store records in set if needed.
  
  
  //*******************************getter methods********************************************
    std::string getSecondaryRepresentation() const; 
    /**
    * \param tool the tool whose representation array is needed
    * \return Returns the representations for the given tool. If no representation found an empty vector. If tool is empty string random vector.
    */
    std::vector<std::string> getSecondaryRepresentationsForTool(const std::string tool) const; 
    std::string getPackage() const;
    std::string getClass() const;
    std::string getMethodName() const;
    std::vector<std::string> getParameters() const;
    std::vector<std::pair<std::string, std::string>> getSameMethods() const;
    std::string getUnifiedRepresentation() const;
    unsigned int getProperties() const;
    std::string getDeclaringClass() const;
    
  
  
  //*****************************setter methods*******************************************
    void setProperties(const unsigned int tag);
    void setDeclaringClass(const std::string& dc);
  
  
    /**
    * \param o output stream to write to
    * \param r a record that is written to o.
    * \return output stream.
    */
    friend std::ostream& operator<<(std::ostream& o, const Record& r);  //make printing easier.
};

#endif