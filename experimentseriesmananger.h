#ifndef EXPERIMENTSERIESMANANGER_H
#define EXPERIMENTSERIESMANANGER_H

#include <QObject>

class ExperimentSeriesMananger : public QObject
{
    Q_OBJECT
public:
    explicit ExperimentSeriesMananger(QObject* _parent = 0);
    void runExperiments(int _n);

signals:
    void rowFinished(int _row, double _value);

public slots:

private:
    bool m_isFinished;

};

#endif // EXPERIMENTSERIESMANANGER_H
