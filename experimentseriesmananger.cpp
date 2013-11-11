#include "modelapi.h"
#include "experimentseriesmananger.h"
#include "experimentmananger.h"

ExperimentSeriesMananger::ExperimentSeriesMananger(QObject* _parent)
    : QObject(_parent),
      m_isFinished(false)
{}

void ExperimentSeriesMananger::runExperiments(int _n)
{
    m_isFinished = false;
    m_report.clear();
    for(int i = MIN_MEM; i <= MAX_MEM; i++)
    {
        double average = 0;
        for(int j = 0; j < _n; j++)
        {
            ExperimentMananger mananger(i);
            int res = mananger.calcTime();
            m_report.insert(i, res);

            average += res;
        }
        average /= _n;
        emit rowFinished(i, average);
    }
    m_isFinished = true;
}

const QMap<int, int> ExperimentSeriesMananger::report(int _memory) const
{
    _memory += MIN_MEM;
    QList<int> values = m_report.values(_memory);

    QMap<int, int> ans;
    foreach(int time, values)
        ans[time] += 1;

    return ans;
}
