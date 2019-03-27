#ifndef EDGEMATRIX_H
#define EDGEMATRIX_H
#include <utility>

class EdgeMatrix {
  int** cells;
  int size;
  int callNum;
public:
  EdgeMatrix(int size);
  ~EdgeMatrix();
  EdgeMatrix & operator+=(std::pair<int, int> edge);
  EdgeMatrix & operator=(const EdgeMatrix& m);
  int getSize() const;
  int getCallNum() const;
};

#endif