class Loader {
  
  FILE* fp;
  
  public:
    Loader( std::string file2access );
    
    /**
    * Loads the nodes to the method store, if no matching method is found creates a new one with a new id
    */
    bool load() = 0;
  
    /**
    * Uses the ids (ones that is used by every other tool) instead of it's own method names
    * @return Returns a set of connections a connection is represented as a pair<caller, calle>
    */
    std::set<std::pair<int, int> > transformConnections() = 0;
  
};