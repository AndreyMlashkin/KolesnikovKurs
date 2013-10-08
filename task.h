#ifndef TASK_H
#define TASK_H

#include <QList>

class Task
{
public:
    Task(int _memory, int _time, int _timeDispercy);
    ~Task();

    void setDepended(int _n, Task* _depended, ...);
    void removeDependency(Task* _task);

private:
    QList<Task*> m_depends;
    int m_memory;
    int m_time;
};

#endif // TASK_H
