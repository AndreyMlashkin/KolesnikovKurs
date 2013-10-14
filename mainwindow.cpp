#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmananger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ModelMananger mananger(20);
    qDebug() << "RESULT: "  << mananger.calcTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}
