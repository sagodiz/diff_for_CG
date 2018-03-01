class Loader_soot : Loader {
  
  public:
    Loader_soot(string filepath);
    bool load();
    std::set<std::pair<int, int> > transformConnections();
}