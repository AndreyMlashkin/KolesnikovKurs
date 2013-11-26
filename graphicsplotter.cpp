#include <QDebug>
#include <QVector>
#include <QtMath>

#include "qcustomplot/qcustomplot.h"
#include "modelapi.h"
#include "graphicsplotter.h"

GraphicsPlotter::GraphicsPlotter(QWidget* _parent) :
    QWidget(_parent),
    m_chart(new QCustomPlot(this))
{
    initChart();
}

void GraphicsPlotter::initChart()
{
    m_chart->axisRect()->setupFullAxesBox();

    m_chart->plotLayout()->insertRow(0);
    m_chart->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_chart, tr("Dispersy")));

    m_chart->xAxis->setLabel("Time");
    m_chart->yAxis->setLabel("Quantaty");
    m_chart->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);

    if(!m_chart->graph(0))
    {
        m_chart->addGraph(0);
        m_chart->graph(0)->setLineStyle(QCPGraph::lsLine);

        m_chart->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 7));
        m_chart->graph(0)->setName("Experiment");
    }

    if(!m_chart->graph(1))
    {
        m_chart->addGraph();
        m_chart->graph(1)->setLineStyle(QCPGraph::lsLine);

        m_chart->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 7));
        m_chart->graph(1)->setName("Ideal Dispercy");
    }

    QPen graphPen;
    graphPen.setColor(Qt::black);
    graphPen.setWidthF(5);
    m_chart->graph(0)->setPen(graphPen);

    m_chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    m_chart->resize(500, 500);
}

void GraphicsPlotter::plotGraphics(const QMap<int, int>& _dispercy)
{
    QVector<double> time, quantaty;

    int minTime = 1000000000, maxTime = -1, maxQuataty = -1;
    QMapIterator<int, int> i(_dispercy);
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
    m_chart->graph(0)->setData(time, quantaty);

    m_chart->xAxis->setRange(minTime-1, maxTime + 1);
    m_chart->yAxis->setRange(0, maxQuataty);

    m_chart->replot();
    m_chart->show();
}

inline void calculateExpectedValueAndVariance(qreal& _expectedValue, qreal& _variance, int& _experimentsNumber, const QMap<int, int>& _dispercy)
{
    _expectedValue = 0;
    _variance = 0;

    QMapIterator<int, int> i(_dispercy);
    while(i.hasNext())
    {
        i.next();
        _experimentsNumber += i.value();
    }
    i.toFront();
    while(i.hasNext())
    {
        i.next();

        int tmp = i.key() * (i.value());
        _expectedValue += tmp;
        _variance += tmp * i.key();
    }

    _expectedValue /= _experimentsNumber;
    _variance /= _experimentsNumber;
    _variance -= _expectedValue * _expectedValue;
}

void GraphicsPlotter::plotIdealDistribution(const QMap<int, int> &_dispercy)
{
    qreal expectedValue(0), variance(0);
    int experimentsNumber(0);

    calculateExpectedValueAndVariance(expectedValue, variance, experimentsNumber, _dispercy);
//    qDebug() << "expectedValue: " << expectedValue << "variance: " << variance;

    QVector<double> time, data;
    QMapIterator<int, int> i(_dispercy);
    while(i.hasNext())
    {
        i.next();
        int x = i.key();

        time << x;
        data << (1/(qSqrt(2*M_PI*variance))*qExp(-pow((x-expectedValue),2)/(2*variance))) * experimentsNumber;
    }
//    qDebug() << data;

    m_chart->graph(1)->setData(time, data);

    m_chart->replot();
    m_chart->show();
}

void GraphicsPlotter::outputInConsole(const QMap<int, int> &_dispercy)
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


