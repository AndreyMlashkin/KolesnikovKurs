#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>
#include <QIntValidator>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmananger.h"

const int minMem = 7;
const int maxMem = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

 //   setFocus();
    connect(m_ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), SLOT(clearInput()));
}

void MainWindow::run()
{
    m_report.clear();
    int experimentsNumber = m_ui->expCount->text().toInt();
    if(experimentsNumber <= 0)
        return;

    clear();
    m_ui->progress->setMaximum(maxMem - minMem);
    qApp->processEvents();

    for(int i = minMem; i <= maxMem; i++)
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
        m_ui->labels->addWidget(lbl);

        m_ui->progress->setValue(i - minMem);
        qApp->processEvents();
    }
}

void MainWindow::clear()
{
    QLayoutItem *item;
    while(item = m_ui->labels->takeAt(0))
    {
        if (item->widget())
                delete item->widget();
        delete item;
    }
}

void MainWindow::clearInput()
{
    disconnect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(clearInput()));
    m_ui->expCount->clear();
    m_ui->expCount->setFont(QFont());
    m_ui->expCount->setValidator(new QIntValidator);
}

MainWindow::~MainWindow()
{
    clear();
    delete m_ui;
}
