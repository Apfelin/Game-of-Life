#ifndef DISPLAYJOC_H
#define DISPLAYJOC_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QApplication>
#include <QScrollArea>
#include <QPalette>
#include <QMenuBar>
#include <QMenu>
#include <QDesktopWidget>
#include "GameOfLife.h"

namespace Ui {
    class DisplayJoc;
}

class DisplayJoc : public QWidget
{
    Q_OBJECT

public:

    explicit DisplayJoc(QWidget *parent = NULL, int threads_no = 1, int generations = 0, char* = NULL, char* = NULL);

public slots:

    void handleRun();
    void handlePause();
    void handleAbout();
    void timerFired();

private:

    Ui::DisplayJoc *ui;
    QTimer *timer;
    QLabel *title;
    GameOfLife *gol;
    QScrollArea* scrlArea;
    QPushButton *runButton;
    QPushButton *pauseButton;
    QLabel *info;
    QHBoxLayout* setupTitle();
    QHBoxLayout* setupButtons();
    void setupMenu();
};

#endif // DISPLAYJOC_H
