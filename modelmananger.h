#ifndef MODELMANANGER_H
#define MODELMANANGER_H

#include <QList>
class Task;
class ModelMananger
{
public:
    ModelMananger(int _memorySize);
    int calcTime();

private:
    inline int freeMemory();
    void putInMemory(Task* _task);

private:
    QList<Task*> m_processQue;
    QList<Task*> m_isNowProcesing;

    const int m_memorySize;
};

#endif // MODELMANANGER_H
