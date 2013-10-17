#include <QDebug>
#include <QLayout>
#include <QString>
#include <QLabel>
#include <QIntValidator>
#include <QVector>
#include <QHashIterator>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelmananger.h"

#include "qcustomplot/qcustomplot.h"

const int minMem = 7;
const int maxMem = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_chart(new QCustomPlot())
{
    m_ui->setupUi(this);
    initChart();

    setFocus();
    connect(m_ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(m_ui->expCount, SIGNAL(cursorPositionChanged(int,int)), SLOT(clearInput()));
    connect(m_ui->result, SIGNAL(cellClicked(int,int)), this, SLOT(plotGraphics(int)));
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

void MainWindow::initChart()
{
    m_chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

//    m_chart->xAxis->setRange(minMem-1, maxMem+1);
//    m_chart->yAxis->setRange(0, 40);

    m_chart->axisRect()->setupFullAxesBox();

    m_chart->plotLayout()->insertRow(0);
    m_chart->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_chart, tr("Time")));

    m_chart->xAxis->setLabel("Memory");
    m_chart->yAxis->setLabel("Time");
    m_chart->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);

    if(!m_chart->graph())
    {
        m_chart->addGraph();
     //   m_chart->graph()->setLineStyle(QCPGraph::lsImpulse);
    }


    m_chart->resize(500, 500);
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
    _memory += minMem;

    QPen graphPen;
    graphPen.setColor(Qt::black);
    graphPen.setWidthF(5);
    m_chart->graph()->setPen(graphPen);

    QList<int> values = m_report.values(_memory);

    QHash<int, int> dispercy;
    foreach(int time, values)
        dispercy[time] += 1;

    QVector<double> time, quantaty;

    int minTime = 1000000000, maxTime = -1, maxQuataty = -1;
    QHashIterator<int, int> i(dispercy);
    while(i.hasNext())
    {
        i.next();
        time << i.key();
        quantaty << i.value();

        if(minTime > i.key())
            minTime = i.key();
        if(maxTime < i.key())
            maxTime = i.key();
        if(maxQuataty < i.value())
            maxQuataty = i.value();
    }
    m_chart->graph()->setData(time, quantaty);

    m_chart->xAxis->setRange(minTime-1, maxTime + 1);
    m_chart->yAxis->setRange(0, maxQuataty);

    m_chart->replot();
    m_chart->show();
}

MainWindow::~MainWindow()
{
    clear();
    delete m_ui;
}
