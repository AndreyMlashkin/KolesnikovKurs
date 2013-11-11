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

    void plotGraphics(int _memory, const QMap<int, int>& _dispercy);
    void outputInConsole(const QMap<int, int>& _dispercy);

private:
    void inline initChart();

private:
    QCustomPlot* m_chart;
};

#endif // GRAPHICSPLOTTER_H
