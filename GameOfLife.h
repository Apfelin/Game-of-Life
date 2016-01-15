#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "matrix.h"
#include <QRect>
#include <QPainter>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class GameOfLife : public QWidget {

    Q_OBJECT

private:

    matrix *principalMatrix, *auxiliarMatrix;
    char DeadOrAlive(int, int);
    QRect rectPaint;
    QColor cellColourAlive;
    QColor cellColourDead;
    QPainter painter;

public:

    GameOfLife(QWidget* parent = 0, int threads_no = 1, int generations = 1, char* file_in = NULL, char* file_out = NULL);
    ~GameOfLife();
    void nextGeneration(int, int, int, int);
    void write(char*);
    void boarding();
    void swap();
    void get_dim(int&, int&);
    bool get_elem(int, int);

    int thread_id;
    int rest;
    int cat;
    int rows, cols;
    int i = 1;
    char * file_out;
    int threads_no;
    int generations_no;
    int cellSize = 5;

protected:

    /*overload*/ void paintEvent(QPaintEvent *);
};

#endif // GAMEOFLIFE_H
