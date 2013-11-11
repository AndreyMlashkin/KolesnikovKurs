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

const QMultiMap<int, int>& ExperimentSeriesMananger::report() const
{
    return m_report;
}
