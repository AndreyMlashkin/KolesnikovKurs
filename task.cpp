#include <QDebug>
#include "task.h"

Task::~Task()
{
    foreach(Task* t, m_outcomingDepends)
    {
        qDebug() << this << " removed";
        t->removeIncomingDependency(this);
    }
}

void Task::addIncomingDepend(Task* _dependentOn)
{
    m_incomingDepends << _dependentOn;
    _dependentOn->addOutcomingDependency(this);
}

void Task::removeIncomingDependency(Task* _task)
{
    if(!m_incomingDepends.removeOne(_task))
        qDebug() << "error! dependency was not removed in Task::removeIncomingDependency";
}

bool Task::ready()
{
    return !m_incomingDepends.count();
}

void Task::addOutcomingDependency(Task *_task)
{
    m_outcomingDepends << _task;
}
