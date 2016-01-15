#include <iostream>
#include "displayjoc.h"
#include "about.h"
#include <omp.h>

DisplayJoc::DisplayJoc(QWidget *parent, int threads_no, int generations, char* file_in, char* file_out) :
    QWidget(parent) {

    gol = new GameOfLife(this, threads_no, generations, file_in, file_out);
    QSize *adjustSize = new QSize(gol->cellSize, gol->cellSize);

    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();

    if ((gol->rows < (width/5)) || (gol->cols < (height/5))) {

        if (width >= height) {

            gol->cellSize = width / gol->cols;
        }
        else {

            gol->cellSize = height / gol->rows;
        }
    }

    adjustSize->setWidth(gol->cellSize * gol->rows);
    adjustSize->setHeight(gol->cellSize * gol->cols);
    gol->setMinimumSize(*adjustSize);

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *title = setupTitle();
    layout->addLayout(title);

    QHBoxLayout *buttons = setupButtons();
    layout->addLayout(buttons);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::black);

    scrlArea = new QScrollArea(this);
    scrlArea->setAutoFillBackground(true);
    scrlArea->setPalette(pal);
    scrlArea->setWidget(gol);

    layout->addWidget(scrlArea);

    setLayout(layout);
}

QHBoxLayout* DisplayJoc::setupTitle() {

    QHBoxLayout *header = new QHBoxLayout();
    header->setAlignment(Qt::AlignHCenter);

    title = new QLabel("Game of Life",this);
    title->setAlignment(Qt::AlignHCenter);
    title->setFont(QFont("Arial", 20, QFont::Bold));

    header->addWidget(title);

    return header;
}

QHBoxLayout* DisplayJoc::setupButtons() {

    QHBoxLayout *buttonRow = new QHBoxLayout();
    buttonRow->setAlignment(Qt::AlignHCenter);

    runButton = new QPushButton("Run");
    QPixmap runPix("resources/run.png");
    QIcon runIcon(runPix);
    runButton->setIcon(runIcon);
    runButton->setIconSize(runPix.rect().size());
    connect(runButton, SIGNAL(clicked()), this, SLOT(handleRun()));
    buttonRow->addWidget(runButton);

    pauseButton = new QPushButton("Pause");
    QPixmap pausePix("resources/pause.png");
    QIcon pauseIcon(pausePix);
    pauseButton->setIcon(pauseIcon);
    pauseButton->setIconSize(pausePix.rect().size());
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));
    pauseButton->setEnabled(false);
    buttonRow->addWidget(pauseButton);

    QPushButton *quitButton = new QPushButton("Quit");
    QPixmap quitPix("resources/quit.png");
    QIcon quitIcon(quitPix);
    quitButton->setIcon(quitIcon);
    quitButton->setIconSize(quitPix.rect().size());
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttonRow->addWidget(quitButton);

    info = new QLabel("Game isn't running");
    buttonRow->addWidget(info);

    QPushButton *aboutButton = new QPushButton("About");
    QPixmap aboutPix("resources/about.png");
    QIcon aboutIcon(aboutPix);
    aboutButton->setIcon(aboutIcon);
    aboutButton->setIconSize(aboutPix.rect().size());
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(handleAbout()));
    buttonRow->addWidget(aboutButton);

    return buttonRow;
}

void DisplayJoc::handleRun() {

    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerFired()));
    this->timer->start(35);
    runButton->setEnabled(false);
    pauseButton->setEnabled(true);
    info->setText("Game is running...");
}

void DisplayJoc::handlePause() {

    this->timer->stop();
    delete this->timer;
    runButton->setEnabled(true);
    runButton->setText("Continue");
    pauseButton->setEnabled(false);
    info->setText("Game paused");
}

void DisplayJoc::handleAbout() {

    about* window = new about(NULL);
    window->show();
    window->setWindowTitle("About");
    window->setFixedSize(450,750);
}

void DisplayJoc::timerFired() {

    int threads_no = gol->threads_no;
    int thread = gol->thread_id;

    if (gol->i < gol->generations_no) {

        gol->boarding();
        #pragma omp parallel num_threads(threads_no) private (thread)
        {

            thread = omp_get_thread_num();
            int b = (thread + 1) * gol->cat + thread + 1;
            int a = thread * (gol->cat + 1) + 1;
            int c = thread * gol->cat + 1 + gol->rest;
            int d = (thread + 1) * gol->cat + gol->rest;

            if (thread < gol->rest) {

                gol->nextGeneration(a, 1, b, gol->cols);
            }
            else {

                gol->nextGeneration(c, 1, d, gol->cols);
            }
        }

        gol->i++;
        gol->swap();
        gol->update();
    }
    else {

        this->timer->stop();
        delete this->timer;
        runButton->setEnabled(false);
        pauseButton->setEnabled(false);
        info->setText("Game has finished!");
        gol->write(gol->file_out);
    }
}
