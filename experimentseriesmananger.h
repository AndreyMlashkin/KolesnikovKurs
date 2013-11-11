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
    const QMap<int, int> report(int _memory) const;

signals:
    void rowFinished(int _row, double _value);

private:
    bool m_isFinished;
    QMultiMap<int, int> m_report;
};

#endif // EXPERIMENTSERIESMANANGER_H
