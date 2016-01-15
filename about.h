#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include "license.h"

class about : public QWidget {

    Q_OBJECT

public:

    explicit about(QWidget *parent = 0);

public slots:

    void handleGNU();
};

#endif // ABOUT_H
