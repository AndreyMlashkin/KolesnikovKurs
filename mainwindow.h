#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiHash>

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
    void run();
    void clearInput();

    void plotGraphics(int _memory);

private:
    void clear();
    inline void initChart();

private:
    Ui::MainWindow* m_ui;
    QMultiHash<int, int> m_report;
    QCustomPlot* m_chart;
};

#endif // MAINWINDOW_H
