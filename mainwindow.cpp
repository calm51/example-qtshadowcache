#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <qtshadowcache/qtshadowcache.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // layout()->setContentsMargins(0, 0, 0, 0);
    qDebug() << layout()->contentsMargins();

    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    qDebug() << ui->centralwidget->layout()->contentsMargins();
}

MainWindow::~MainWindow() {
    delete ui;
}
