#ifndef TASK_H
#define TASK_H

#include <QList>

class Task
{
public:
    Task() {}
    virtual ~Task();

    void removeIncomingDependency(Task* _task);
    bool ready();

    virtual int time()   { return 0; }
    virtual int memory() { return 0; }
    virtual void step() = 0;

    static void addConnection(Task* _dominator, Task* _depended);

protected:
    void addIncomingDepend(Task* _dependentOn);
    void addOutcomingDependency(Task* _task);

protected:
    QList<Task*> m_incomingDepends;    // зависит от
    QList<Task*> m_outcomingDepends;   // зависимые от этого
};

#endif // TASK_H
