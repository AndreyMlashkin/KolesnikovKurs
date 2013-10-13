#include "complextask.h"

ComplexTask::ComplexTask(int _simpleCount, Task* _task, ...)
    : Task()
{
    while(_simpleCount)
    {
        m_subTasks << _task;
        m_incomingDepends << _task;
        _task++;
        _simpleCount--;
    }
}

ComplexTask::~ComplexTask()
{
    foreach(Task* t, m_subTasks)
        delete t;
}

//void ComplexTask::removeIncomingDependency(Task *_task)
//{
//    foreach(Task* t, m_subTasks)
//        t->removeIncomingDependency(_task);
//}

bool ComplexTask::ready()
{
    bool isReady = false;
    foreach(Task* t, m_subTasks)
        isReady = isReady || t->ready();

    return isReady;
}

int ComplexTask::time()
{
    return 0;
}

int ComplexTask::memory()
{
    return 0;
}

void ComplexTask::step()
{
    foreach(Task* t, m_outcomingDepends)
        t->removeIncomingDependency(this);

//    Task::~Task(); // !!!!
}
