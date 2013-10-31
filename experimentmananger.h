#ifndef EXPERIMENTMANANGER_H
#define EXPERIMENTMANANGER_H

#include <QList>
class Task;
class ExperimentMananger
{
public:
    ExperimentMananger(int _memorySize);
    int calcTime();

private:
    inline int memoryLeft();
    void tryToProcess(Task* _task);
    void updateProcessing();

private:
    int m_time;

    QList<Task*> m_processQue;
    QList<Task*> m_isNowProcesing;

    const int m_memorySize;
};

#endif // EXPERIMENTMANANGER_H
