#ifndef EXPERIMENTSERIESMANANGER_H
#define EXPERIMENTSERIESMANANGER_H

#include <QObject>
#include <QMultiMap>

class ExperimentSeriesMananger : public QObject
{
    Q_OBJECT
public:
    explicit ExperimentSeriesMananger(QObject* _parent = 0);
    void runExperiments(int _n);
    const QMultiMap<int, int>& report() const;

signals:
    void rowFinished(int _row, double _value);

public slots:

private:
    bool m_isFinished;
    QMultiMap<int, int> m_report;

};

#endif // EXPERIMENTSERIESMANANGER_H
