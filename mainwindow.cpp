#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmananger.h"

const int experimentsNumber = 100;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    for(int i = 7; i < 30; i++)
    {

        double  result = 0;
        for(int j = 0; j < experimentsNumber; j++)
        {
            ModelMananger mananger(i);
            result += mananger.calcTime();
        }
        result /= experimentsNumber;

        QLabel* lbl = new QLabel();
        lbl->setText("Memory: " + QString::number(i) + "\tResult: "  + QString::number(result));
        m_ui->centralWidget->layout()->addWidget(lbl);
    }


//    int result = mananger.calcTime();

//    m_ui->result->setText(QString::number(result));

 //   qDebug() << "RESULT: "  << mananger.calcTime();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
