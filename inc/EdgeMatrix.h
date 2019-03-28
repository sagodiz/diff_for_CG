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
  EdgeMatrix & operator+=(const EdgeMatrix& m);
  EdgeMatrix & operator=(const EdgeMatrix& m);
  int getSize() const;
  int getCallNum() const;
  int getCell(int, int) const;
  /**
  * This method sets the i, j-th cell to the value.
  * \param i the row
  * \param j the column
  * \param value The value thata should be set. By default it is 1.
  */
  void setCell(int i, int j, int value = 1);
};

#endif