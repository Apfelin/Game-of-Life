#include "GameOfLife.h"
#include "matrix.h"

using namespace std;

GameOfLife::GameOfLife(QWidget *parent, int threads_no, int generations, char *file_in, char* file_out) : QWidget(parent) {

    this->threads_no = threads_no;
    this->generations_no = generations;
    this->file_out = file_out;
    this->cellColourAlive = QColor(0,255,0);
    this->cellColourDead = QColor(0,0,0);

    ifstream f(file_in);

    f >> rows;
    f >> cols;

    rest = rows % (this->threads_no);
    cat = rows / (this->threads_no);

    char aux;

    principalMatrix = new matrix{rows, cols};
    auxiliarMatrix = new matrix{rows, cols};

    for(int i = 1; i <= rows; ++i) {

        for(int j = 1; j <= cols; ++j) {

            f >> aux;
            aux = aux - '0';
            principalMatrix->set(i, j, aux);
        }
    }

    f.close();
    boarding();
    update();
}

GameOfLife::~GameOfLife() {

    delete principalMatrix;
    delete auxiliarMatrix;
}

void GameOfLife::write(char *file) {

    principalMatrix->write(file);
}

char GameOfLife::DeadOrAlive(int i, int j) {

    int sum=0;

    sum = principalMatrix->get(i-1,j-1)+principalMatrix->get(i-1,j)+principalMatrix->get(i-1,j+1)+principalMatrix->get(i,j-1)+
            principalMatrix->get(i,j+1)+principalMatrix->get(i+1,j-1)+principalMatrix->get(i+1,j)+principalMatrix->get(i+1,j+1);

    if(sum > 3 || sum < 2) {

        return 0;
    }
    else if (principalMatrix->get(i, j) == 0 && sum == 2) {

        return 0;
    }
    else {

        return 1;
    }
}

void GameOfLife::nextGeneration(int rows_first, int cols_first, int rows_final, int cols_final) {

    int i, j;

    for(i = rows_first; i <= rows_final; ++i) {

        for(j = cols_first; j <= cols_final; ++j) {

            auxiliarMatrix->set(i,j,DeadOrAlive(i,j));
        }
    }
}

void GameOfLife::boarding() {

    int i;

    for(i = 1; i <= cols; ++i) {

        principalMatrix->set(rows+1,i,principalMatrix->get(1,i));
        principalMatrix->set(0,i,principalMatrix->get(rows,i));
    }

    for(i = 1; i <= rows; ++i) {

        principalMatrix->set(i,cols+1,principalMatrix->get(i,1));
        principalMatrix->set(i,0,principalMatrix->get(i,cols));
    }

    principalMatrix->set(rows+1,cols+1,principalMatrix->get(1,1));
    principalMatrix->set(0,cols+1,principalMatrix->get(rows,1));
    principalMatrix->set(rows+1,0,principalMatrix->get(1,cols));
    principalMatrix->set(0,0,principalMatrix->get(rows,cols));
}

void GameOfLife::swap() {

    principalMatrix->swap(*auxiliarMatrix);
}

void GameOfLife::get_dim(int &r, int &c) {

    r = rows;
    c = cols;
}

bool GameOfLife::get_elem(int i,int j) {

    return principalMatrix->get(i, j);
}

void GameOfLife::paintEvent(QPaintEvent *event) {

    QWidget::paintEvent(event);

    painter.begin(this);

    rectPaint = event->region().boundingRect();
    register int x1Rect = rectPaint.x();
    register int y1Rect = rectPaint.y();
    register int x2Rect = x1Rect + rectPaint.width();
    register int y2Rect = y1Rect + rectPaint.height();

    register int xCell;
    register int yCell = 0;

    for (int i = 1; i <= rows; i++) {

        xCell = 0;

        for (int j = 1; j <= cols; j++) {

            if (xCell <= x2Rect && yCell <= y2Rect && xCell + cellSize >= x1Rect &&
                    yCell + cellSize >= y1Rect) {

                if (principalMatrix->get(i,j)) {

                    painter.fillRect(xCell, yCell, cellSize - 1, cellSize - 1, cellColourAlive);
                }
                else {

                    painter.fillRect(xCell, yCell, cellSize - 1, cellSize - 1, cellColourDead);
                }
            }

            xCell += cellSize;
        }

        yCell += cellSize;
    }

    painter.end();
}
