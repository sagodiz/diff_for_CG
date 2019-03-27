#ifndef EDGEMATRIX_H
#define EDGEMATRIX_H
class EdgeMatrix {
  int** cells;
  int size;
  int callNum = 0;
public:
  EdgeMatrix(int size);
  ~EdgeMatrix();
  EdgeMatrix& operator+=(std::pair<int, int> edge);
  EdgeMatrix& operator=(const EdgeMatrix& m);
  int getSize() const;
  int getCallNum() const;
}

#endif