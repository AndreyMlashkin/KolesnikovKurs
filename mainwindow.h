#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiMap>

class ExperimentSeriesMananger;

class QCustomPlot;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void compute();
    void rowFinished(int _row, double _value);

    void clearInput();

    void plotGraphics(int _memory);

private:
    void clear();
    inline void initChart();

    void outputInConsole(const QMap<int, int>& _dispercy);

private:
    Ui::MainWindow* m_ui;
    QCustomPlot* m_chart;
    ExperimentSeriesMananger* m_seriesMananger;
};

#endif // MAINWINDOW_H
