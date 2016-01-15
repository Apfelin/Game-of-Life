#include <iostream>
#include <fstream>
#include "matrix.h"

matrix::matrix(int m, int n) {

    int i, j;

    this->n = n;
    this->m = m;

    M = new char *[m+2];       //o las bordata pe fiecare parte, aloc doar pointerii pt linii
    M[0] = new char [(m+2)*(n+2)];     //aloc matricea ca bloc

    for (i = 1; i <= m+1; i++) {

        M[i] = M[0]+i*(n+2);      //fac legaturile pointerilor in bloc
    }

    for (i = 0; i <= m+1; i++) {

        for(j = 0; j <= n+1; j++) {       //initializez cu 0

            M[i][j] = 0;
        }
    }
}

matrix::~matrix() {

    delete M[0];        //dealoc blocul
    delete M;       //dealoc vect de pointeri
}

void matrix::set(int i, int j, char current) {

    M[i][j] = current;
}

int matrix::get(int i, int j) {

    return M[i][j] == 1;
}

void matrix::swap (matrix &A) {

    char **a = A.M;
    A.M = M;
    M = a;
}

void matrix::write(char *file) {

    int i, j;

    ofstream g(file);

    for (i = 1; i <= m; i++) {   //doar blocul neincadrat

        for(j = 1; j <= n; j++) {

            g << (M[i][j] == 1) << ' ';
        }

        g << '\n';
    }

    g.close();
}
