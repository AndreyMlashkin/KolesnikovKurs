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
    void singleTic();

    inline int memoryLeft();
    void tryToProcess(Task* _task);
    void updateProcessing();

private:
    int m_time;

    QList<Task*> m_processQue;
    QList<Task*> m_isNowProcesing;

    const int m_memorySize;
};

#endif // MODELMANANGER_H
