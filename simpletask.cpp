#include "simpletask.h"

SimpleTask::SimpleTask(int _memory, int _time, int _timeDispercy)
    : Task(),
      m_memory(_memory),
      m_time(_time)
{
    if(_timeDispercy == 0)
        return;

    int dispercy =  qrand() % (2 * _timeDispercy) - _timeDispercy;
    m_time += dispercy;
}

int SimpleTask::memory()
{
    return m_memory;
}

int SimpleTask::time()
{
    return m_time;
}

void SimpleTask::step()
{
    m_time--;
}
