#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>
#include <QHash>

namespace Ui {
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
    void clear();
    void clearInput();

private:
    Ui::MainWindow* m_ui;
    QHash<int, QVector<int> > m_report;
};

#endif // MAINWINDOW_H
