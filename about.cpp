#include "about.h"
#include <QBitmap>

about::about(QWidget *parent) : QWidget(parent, Qt::Window) {

    QVBoxLayout* layout = new QVBoxLayout;

    QLabel* logo = new QLabel;
    QPixmap picture("resources/gol.png");
    logo->setPixmap(picture);
    logo->setAlignment(Qt::AlignCenter);
    layout->addWidget(logo);

    QLabel* title1 = new QLabel("Conway's");
    title1->setAlignment(Qt::AlignHCenter);
    title1->setFont(QFont("Arial", 20, 75));
    layout->addWidget(title1);

    QLabel* title2 = new QLabel("Game of Life");
    title2->setAlignment(Qt::AlignHCenter);
    title2->setFont(QFont("Arial", 20, 75));
    layout->addWidget(title2);

    QLabel* echipa = new QLabel("Echipa:");
    echipa->setAlignment(Qt::AlignHCenter);
    echipa->setFont(QFont("Arial", 17, 65));
    layout->addWidget(echipa);

    QLabel* docs = new QLabel("Documentatie:");
    docs->setAlignment(Qt::AlignHCenter);
    docs->setFont(QFont("Arial", 14, 50, 1));
    layout->addWidget(docs);

    QLabel* ioana = new QLabel("Popescu Ioana-Laura");
    ioana->setAlignment(Qt::AlignHCenter);
    ioana->setFont(QFont("Arial", 11, 50));
    layout->addWidget(ioana);

    QLabel* silvia = new QLabel("Brindusescu Siliva");
    silvia->setAlignment(Qt::AlignHCenter);
    silvia->setFont(QFont("Arial", 11, 50));
    layout->addWidget(silvia);

    QLabel* cod = new QLabel("Coding:");
    cod->setAlignment(Qt::AlignHCenter);
    cod->setFont(QFont("Arial", 14, 50, 1));
    layout->addWidget(cod);

    QLabel* alex = new QLabel("Birlica Alexandru");
    alex->setAlignment(Qt::AlignHCenter);
    alex->setFont(QFont("Arial", 11, 50));
    layout->addWidget(alex);

    QLabel* jinga = new QLabel("Jinga Radu");
    jinga->setAlignment(Qt::AlignHCenter);
    jinga->setFont(QFont("Arial", 11, 50));
    layout->addWidget(jinga);

    QLabel* multith = new QLabel("Multithreading:");
    multith->setAlignment(Qt::AlignHCenter);
    multith->setFont(QFont("Arial", 14, 50, 1));
    layout->addWidget(multith);

    QLabel* sergiu = new QLabel("Duda Sergiu");
    sergiu->setAlignment(Qt::AlignHCenter);
    sergiu->setFont(QFont("Arial", 11, 50));
    layout->addWidget(sergiu);

    QLabel* interface = new QLabel("Interfata grafica:");
    interface->setAlignment(Qt::AlignHCenter);
    interface->setFont(QFont("Arial", 14, 50, 1));
    layout->addWidget(interface);

    QLabel* laura = new QLabel("Cojocaru Laura-Andreea");
    laura->setAlignment(Qt::AlignHCenter);
    laura->setFont(QFont("Arial", 11, 50));
    layout->addWidget(laura);

    QLabel* vlad = new QLabel("Pelin Vlad");
    vlad->setAlignment(Qt::AlignHCenter);
    vlad->setFont(QFont("Arial", 11, 50));
    layout->addWidget(vlad);

    QLabel* bugs = new QLabel("Bug testing:");
    bugs->setAlignment(Qt::AlignHCenter);
    bugs->setFont(QFont("Arial", 14, 50, 1));
    layout->addWidget(bugs);

    QLabel* raducu = new QLabel("Mirescu Raducu");
    raducu->setAlignment(Qt::AlignHCenter);
    raducu->setFont(QFont("Arial", 11, 50));
    layout->addWidget(raducu);

    QLabel* copy = new QLabel("Copyright (c) 2016 mentioned authors");
    copy->setAlignment(Qt::AlignHCenter);
    copy->setFont(QFont("Arial", 7, 30));
    layout->addWidget(copy);

    QPushButton* gnu = new QPushButton ("Distributed under GNU GPLv3 license");
    connect(gnu, SIGNAL(clicked()), this, SLOT(handleGNU()));
    layout->addWidget(gnu);

    QPushButton* closeButton = new QPushButton("OK");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    layout->addWidget(closeButton);

    setLayout(layout);
}

void about::handleGNU() {

    license* license_w = new license;
    license_w->show();
    license_w->setWindowTitle("GNU GPLv3");
    license_w->setFixedSize(400, 250);
}
