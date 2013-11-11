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

#include "qcustomplot/qcustomplot.h"

//const int MIN_MEM = 7;
//const int MAX_MEM = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_chart(new QCustomPlot()),
    m_seriesMananger(new ExperimentSeriesMananger)
{
    m_ui->setupUi(this);
    initChart();

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
    QTableWidgetItem* newItem = new QTableWidgetItem("Memory: " + QString::number(_row));
    m_ui->result->setItem(_row - MIN_MEM, 0, newItem);

    newItem = new QTableWidgetItem("Result: "  + QString::number(_value));
    m_ui->result->setItem(_row - MIN_MEM, 1, newItem);

    m_ui->progress->setValue(_row - MIN_MEM);
    qApp->processEvents();
}

void MainWindow::clear()
{
    m_ui->result->clear();
}

void MainWindow::initChart()
{
    m_chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
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
        m_chart->graph()->setLineStyle(QCPGraph::lsLine);

        m_chart->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 7));
    }
    m_chart->resize(500, 500);
}

void MainWindow::outputInConsole(const QMap<int, int> &_dispercy)
{
    static int num = 0;
    num++;

    qDebug() << "\n--- Plot N" << num << " ---";

    QMapIterator<int, int> i(_dispercy);
    while(i.hasNext())
    {
        i.next();
        qDebug() << "t=" << i.key() << "\tn="  << i.value();
    }
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
    _memory += MIN_MEM;

    QPen graphPen;
    graphPen.setColor(Qt::black);
    graphPen.setWidthF(5);
    m_chart->graph()->setPen(graphPen);

    QList<int> values = m_seriesMananger->report().values(_memory);  //m_report.values(_memory);

    qDebug() << _memory;
    qDebug() << values;

    QMap<int, int> dispercy;
    foreach(int time, values)
        dispercy[time] += 1;

    QVector<double> time, quantaty;

    int minTime = 1000000000, maxTime = -1, maxQuataty = -1;
    QMapIterator<int, int> i(dispercy);
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

    outputInConsole(dispercy);
}

MainWindow::~MainWindow()
{
    clear();
    delete m_ui;
}
