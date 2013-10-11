#include "simpletask.h"

SimpleTask::SimpleTask(int _memory, int _time, int _timeDispercy)
    : Task(),
      m_memory(_memory),
      m_time(_time)
{
    int dispercy =  qrand() % (2 * _timeDispercy) - _timeDispercy;
    m_time += dispercy;
}
