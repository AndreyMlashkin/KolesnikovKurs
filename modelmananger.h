#ifndef MODELMANANGER_H
#define MODELMANANGER_H

#include <QList>
class Task;
class ModelMananger
{
public:
    ModelMananger();

private:
    QList<Task*> processQue;
};

#endif // MODELMANANGER_H
