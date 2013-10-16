#include <QDebug>
#include "task.h"

Task::~Task()
{
    //qDebug() << this << " removed";
    foreach(Task* t, m_outcomingDepends)
    {
        t->removeIncomingDependency(this);
        //qDebug() << "   freed: " << t;
    }
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

void Task::addConnection(Task* _dominator, Task* _depended)
{
    _dominator->addOutcomingDependency(_depended);
    _depended->addIncomingDepend(_dominator);
}

void Task::addIncomingDepend(Task* _dependentOn)
{
    m_incomingDepends << _dependentOn;
}

void Task::addOutcomingDependency(Task *_task)
{
    m_outcomingDepends << _task;
}
