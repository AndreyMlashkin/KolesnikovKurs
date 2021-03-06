#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include "task.h"

class SimpleTask : public Task
{
public:
    SimpleTask(int _memory, int _time, int _timeDispercy);
    int memory();
    int time();
    void step();

private:
    int m_memory;
    int m_time;
};

#endif // SIMPLETASK_H
