#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiMap>

class ExperimentSeriesMananger;
class GraphicsPlotter;

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

private:
    Ui::MainWindow* m_ui;
    ExperimentSeriesMananger* m_seriesMananger;
    GraphicsPlotter* m_plotter;
};

#endif // MAINWINDOW_H
