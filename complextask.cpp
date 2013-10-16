#include <QDebug>
#include "complextask.h"

ComplexTask::ComplexTask(int _simpleCount, Task* _task, ...)
    : Task()
{
    Task** task = &_task;
    while(_simpleCount)
    {
        Task::addConnection(*task, this);
        (task)++;
        _simpleCount--;
    }
}
