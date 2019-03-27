#include "../inc/EdgeMatrix.h"
using namespace std;
//public methods for class

EdgeMatrix::EdgeMatrix(int size) : size(size), callNum(0) {

  cells = new int*[size];
  for (int i = 0; i < size; i++) {

    cells[i] = new int[size];
    for (int j = 0; i < size; j++) {  //it might useless
      cells[i][j] = 0;
    }
  }
}

EdgeMatrix::~EdgeMatrix() {

  for (int i = 0; i < size; i++) {
    delete[] cells[i];
  }
  delete[] cells;
}

//getters
int EdgeMatrix::getSize() const {
  return size;
}

int EdgeMatrix::getCallNum() const {
  return callNum;
}

//operators

EdgeMatrix& EdgeMatrix::operator+=(pair<int, int> edge) {
  cells[edge.first][edge.second] = 1;
  return *this;
}

EdgeMatrix& EdgeMatrix::operator=(const EdgeMatrix& m) {
  
  for (int i = 0; i < size; i++) {
    delete[] cells[i];
  }
  delete[] cells;

  this->size = m.size;
  cells = new int*[size];
  for (int i = 0; i < size; i++) {
    cells[i] = new int[size];
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      this->cells[i][j] = m.cells[i][j];
    }
  }

  this->callNum = m.callNum;

  return *this;
}