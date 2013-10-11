#ifndef COMPLEXTASK_H
#define COMPLEXTASK_H

#include "task.h"

class ComplexTask : public Task
{
public:
    ComplexTask(int _simpleCount, Task* _task, ...);
    ~ComplexTask();

    void removeDependency(Task *_task);
    bool ready();

private:
    QList<Task*> m_subTasks;
};

#endif  // COMPLEXTASK_H

