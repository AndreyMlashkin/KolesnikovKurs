#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmananger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    for(int i = 10; i < 30; i++)
    {
        ModelMananger mananger(20);
        int result = mananger.calcTime();

//        int result = i;
        QLabel* lbl = new QLabel();
        lbl->setText(QString::number(result));
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
