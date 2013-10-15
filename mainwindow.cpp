#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>

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

    setFocus();
    connect(m_ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), SLOT(clearInput()));
}

void MainWindow::run()
{
    int experimentsNumber = m_ui->expCount->text().toInt();
    clear();
    m_ui->progress->setMaximum(maxMem - minMem);

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
        m_ui->centralWidget->layout()->addWidget(lbl);

        m_ui->progress->setValue(i - minMem);
        qApp->processEvents();
    }
}

void MainWindow::clear()
{
    QObjectList children = m_ui->centralWidget->layout()->children();

    qDebug() << m_ui->centralWidget->layout()->children().size();
    foreach(QObject* o, children)
    {
        QLabel* label = static_cast<QLabel*>(o);
        if(label)
            m_ui->centralWidget->layout()->removeWidget(label);
    }
    qDebug() << m_ui->centralWidget->layout()->children().size();
}

void MainWindow::clearInput()
{
    disconnect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(clearInput()));
    m_ui->expCount->clear();

}

MainWindow::~MainWindow()
{
    delete m_ui;
}
