#ifndef TASK_H
#define TASK_H

#include <QList>

class Task
{
public:
    Task() {}
    virtual ~Task();

    void addIncomingDepend(Task* _dependentOn);
    void removeIncomingDependency(Task* _task);
    bool ready();

    virtual int time() = 0;
    virtual int memory() = 0;
    virtual void step() = 0;

protected:
    void addOutcomingDependency(Task* _task);

//protected:
public: // ###
    QList<Task*> m_incomingDepends;    // зависит от
    QList<Task*> m_outcomingDepends;   // зависимые от этого

    friend class ComplexTask;
};

#endif // TASK_H
