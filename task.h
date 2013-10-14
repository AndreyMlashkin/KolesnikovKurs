#ifndef TASK_H
#define TASK_H

#include <QList>

class Task
{
public:
    Task() {}
    virtual ~Task() = 0;

    void addIncomingDepend(Task* _dependentOn);
    void removeIncomingDependency(Task* _task);
    virtual bool ready();

    virtual int time() = 0;
    virtual int memory() = 0;
    virtual void step() = 0;

protected:
    void addOutcomingDependency(Task* _task);

//protected:
public: // ###
    QList<Task*> m_incomingDepends;    // зависит от
    QList<Task*> m_outcomingDepends;   // зависимые от этого
};

#endif // TASK_H
