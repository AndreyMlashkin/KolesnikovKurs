#ifndef TASK_H
#define TASK_H

#include <QList>

class Task
{
public:
    Task() {}
    virtual ~Task() = 0;

    void setDepended(int _n, Task* _depended, ...);
    virtual void removeDependency(Task* _task);
    virtual bool ready();

protected:
    QList<Task*> m_depends;
};

#endif // TASK_H
