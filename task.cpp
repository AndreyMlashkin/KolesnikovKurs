#include "task.h"

Task::~Task()
{
    foreach(Task* t, m_outcomingDepends)
        t->removeIncomingDependency(this);
}

void Task::addIncomingDepend(Task *_dependentOn)
{
    m_incomingDepends << _dependentOn;
}

void Task::removeIncomingDependency(Task* _task)
{
    int i = 0;
    foreach(Task* t, m_incomingDepends)
    {
        if(_task == t)
            break;
        i++;
    }
    m_incomingDepends.removeAt(i);
}

bool Task::ready()
{
    return !m_incomingDepends.count();
}

void Task::addOutcomingDependency(Task *_task)
{
    m_outcomingDepends << _task;
}
