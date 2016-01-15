#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

using namespace std;

class matrix {

private:

    char **M;
    int n, m;

public:

    matrix(int, int);
    ~matrix();
    void set(int, int, char);
    int get(int i, int j);
    void swap (matrix &A);
    void write(char *file);
};

#endif // MATRIX_H
