#ifndef GRAPHICSPLOTTER_H
#define GRAPHICSPLOTTER_H

#include <QWidget>
#include <QMultiMap>

class QCustomPlot;

class GraphicsPlotter : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsPlotter(QWidget* _parent = 0);

    void plotGraphics(const QMap<int, int>& _dispercy);
    void plotIdealDistribution(const QMap<int, int>& _dispercy);
    void outputInConsole(const QMap<int, int>& _dispercy);

private:
    inline void initChart();
   // inline void calculateExpectedValueAndVariance(qreal _expectedValue, qreal _variance, const QMap<int, int>& _dispercy);

private:
    QCustomPlot* m_chart;
};

#endif // GRAPHICSPLOTTER_H
