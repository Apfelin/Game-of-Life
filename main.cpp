#include "displayjoc.h"
#include <QApplication>
#include <cstdlib>
#include <iostream>
#include "GameOfLife.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    int threads_no = atoi(argv[1]);
    int generations = atoi(argv[2]);

    DisplayJoc w(NULL, threads_no, generations, argv[3], argv[4]);
    w.showMaximized();
    w.setWindowTitle("Conway's Game of Life");

    return a.exec();
}
