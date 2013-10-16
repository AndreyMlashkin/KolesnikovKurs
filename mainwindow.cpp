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

    setFocus();
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

    int itemsCount = maxMem - minMem;
    m_ui->progress->setMaximum(itemsCount);
    m_ui->result->setRowCount(itemsCount);

    qApp->processEvents();

    for(int i = minMem; i <= maxMem; i++)
    {
        double average = 0;
        for(int j = 0; j < experimentsNumber; j++)
        {
            ModelMananger mananger(i);
            int res = mananger.calcTime();
            m_report.insert(i, res);

            average += res;
        }
        average /= experimentsNumber;

        QTableWidgetItem* newItem = new QTableWidgetItem("Memory: " + QString::number(i));
        m_ui->result->setItem(i - minMem, 0, newItem);

        newItem = new QTableWidgetItem("Result: "  + QString::number(average));
        m_ui->result->setItem(i - minMem, 1, newItem);

        m_ui->progress->setValue(i - minMem);
        qApp->processEvents();
    }
}

void MainWindow::clear()
{
    m_ui->result->clear();
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
