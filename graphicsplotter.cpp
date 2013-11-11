#include <QDebug>

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

void GraphicsPlotter::plotGraphics(int _memory, const QMap<int, int>& _dispercy)
{
    _memory += MIN_MEM;

    QPen graphPen;
    graphPen.setColor(Qt::black);
    graphPen.setWidthF(5);
    m_chart->graph()->setPen(graphPen);

    QList<int> values = _dispercy.values(_memory);

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


