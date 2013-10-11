#include "complextask.h"

ComplexTask::ComplexTask(int _simpleCount, Task* _task, ...)
    : Task()
{
    while(_simpleCount)
    {
        m_subTasks.push_back(_task);
        _task++;
        _simpleCount--;
    }
}

ComplexTask::~ComplexTask()
{
    foreach(Task* t, m_subTasks)
        delete t;
}

void ComplexTask::removeDependency(Task *_task)
{
    foreach(Task* t, m_subTasks)
        t->removeDependency(_task);
}

bool ComplexTask::ready()
{
    bool isReady = false;
    foreach(Task* t, m_subTasks)
        isReady = isReady || t->ready();

    return isReady;
}
