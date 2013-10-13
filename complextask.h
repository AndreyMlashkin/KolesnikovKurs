#ifndef COMPLEXTASK_H
#define COMPLEXTASK_H

#include "task.h"

class ComplexTask : public Task
{
public:
    ComplexTask(int _simpleCount, Task* _task, ...);
    ~ComplexTask();
    bool ready();

    int time();
    int memory();

    void step();

private:
    void addIncomingDepend(Task*) {}

private:
    QList<Task*> m_subTasks;
};

#endif  // COMPLEXTASK_H

