#ifndef COMPLEXTASK_H
#define COMPLEXTASK_H

#include "task.h"

class ComplexTask : public Task
{
public:
    ComplexTask(int _simpleCount, Task* _task, ...);
    void step();

private:
};

#endif  // COMPLEXTASK_H

