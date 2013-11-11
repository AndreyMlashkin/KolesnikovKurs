#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>
#include <QIntValidator>
#include <QVector>
#include <QMapIterator>
#include <QMap>

#include "modelapi.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "experimentseriesmananger.h"
#include "graphicsplotter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_seriesMananger(new ExperimentSeriesMananger),
    m_plotter(new GraphicsPlotter())
{
    m_ui->setupUi(this);

    setFocus();
    connect(m_ui->run, SIGNAL(clicked()), this, SLOT(compute()));
    connect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), SLOT(clearInput()));
    connect(m_ui->result, SIGNAL(cellClicked(int,int)), this, SLOT(plotGraphics(int)));
}

void MainWindow::compute()
{
    int experimentsNumber = m_ui->expCount->text().toInt();
    if(experimentsNumber <= 0)
        return;

    clear();

    int itemsCount = MAX_MEM - MIN_MEM;
    m_ui->progress->setMaximum(itemsCount);
    m_ui->result->setRowCount(itemsCount);

    qApp->processEvents();

    connect(m_seriesMananger, SIGNAL(rowFinished(int, double)), this, SLOT(rowFinished(int,double)));
    m_seriesMananger->runExperiments(experimentsNumber);
}

void MainWindow::rowFinished(int _row, double _value)
{
    qApp->processEvents();
    QTableWidgetItem* newItem = new QTableWidgetItem("Memory: " + QString::number(_row));
    m_ui->result->setItem(_row - MIN_MEM, 0, newItem);

    newItem = new QTableWidgetItem("Result: "  + QString::number(_value));
    m_ui->result->setItem(_row - MIN_MEM, 1, newItem);

    m_ui->progress->setValue(_row - MIN_MEM);
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

void MainWindow::plotGraphics(int _memory)
{
    qDebug() << _memory << " plotGraphics";
    m_plotter->plotGraphics(_memory, m_seriesMananger->report());
    m_plotter->show();
//    m_plotter->outputInConsole(m_seriesMananger->report());
}

MainWindow::~MainWindow()
{
    clear();
    delete m_ui;
}
