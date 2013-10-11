#include "task.h"

Task::~Task()
{
    foreach(Task* t, m_depends)
        t->removeDependency(this);
}

void Task::setDepended(int _n, Task* _depended, ...)
{
    while(_n > 0)
    {
        _n--;
        m_depends.push_back(_depended);
        _depended++;
    }
}

void Task::removeDependency(Task *_task)
{
    int i = 0;
    foreach(Task* t, m_depends)
    {
        if(_task == t)
            break;
        i++;
    }
    m_depends.removeAt(i);
}

bool Task::ready()
{
    return !m_depends.count();
}
