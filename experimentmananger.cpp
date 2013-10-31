#include <QDebug>

#include "simpletask.h"
#include "experimentmananger.h"
#include "complextask.h"

ExperimentMananger::ExperimentMananger(int _memorySize)
    : m_time(0),
      m_memorySize(_memorySize)
{
    Task* one   = new SimpleTask(4, 4, 2);
    Task* two   = new SimpleTask(3, 3, 1);
    Task* three = new SimpleTask(5, 5, 2);
    Task* four  = new SimpleTask(0, 0, 0);

    Task* fiveOne   = new SimpleTask(4, 4, 1);
    Task* fiveThree = new SimpleTask(2, 2, 1);
    ComplexTask* five = new ComplexTask(2, fiveOne, fiveThree);

    Task* sixThree  = new SimpleTask(6, 6, 3);
    Task* sixFour   = new SimpleTask(5, 5, 2);
    ComplexTask* six = new ComplexTask(2, sixThree, sixFour);

    Task* sevenFour = new SimpleTask(2, 2, 0);
    Task* sevenFive = new SimpleTask(7, 7, 3);
    Task* sevenSix  = new SimpleTask(3, 3, 1);
    ComplexTask* seven = new ComplexTask(3, sevenFour, sevenFive, sevenSix);

    Task::addConnection(two,   four);
    Task::addConnection(one,   fiveOne);
    Task::addConnection(three, fiveThree);
    Task::addConnection(three, sixThree);
    Task::addConnection(four,  sixFour);
    Task::addConnection(four,  sevenFour);
    Task::addConnection(five,  sevenFive);
    Task::addConnection(six,   sevenSix);

    m_processQue << one << two << three << four << fiveOne << fiveThree << five;
    m_processQue << sixThree << sixFour << six << sevenFour << sevenFive << sevenSix << seven;
    //qDebug() << one << two << three << four << fiveOne << fiveThree << five << sixThree << sixFour << six << sevenFour << sevenFive << sevenSix << seven;
}

int ExperimentMananger::calcTime()
{
    int step = 0;
    while(!m_processQue.isEmpty())
    {
        foreach (Task* t, m_processQue)
        {
            //qDebug() << "#in queue:" << i++ << " " << t;
            //qDebug() << "memoryLeft: " << memoryLeft();
              //qDebug() << "incoming: " << t->m_incomingDepends.count();
            //qDebug() << "in queue: " << m_processQue.size();
            //qDebug() << "is processing: " << m_isNowProcesing.size() << '\n';
            tryToProcess(t);
        }
        updateProcessing();
        step++;
    }
    return step;
}

int ExperimentMananger::memoryLeft()
{
    int usingMemory = 0;
    foreach (Task* t, m_isNowProcesing)
        usingMemory += t->memory();
    return m_memorySize - usingMemory;
}

void ExperimentMananger::updateProcessing()
{
    foreach (Task* t, m_isNowProcesing)
    {
        t->step();
        //qDebug() << "Time to end: " << t->time();
        if(t->time() <= 0)
        {
            const QList<Task*> candidatesToProcess = t->getOutcomingDepends();
            m_isNowProcesing.removeOne(t);
            delete t;
            foreach(Task* candidat, candidatesToProcess)
                tryToProcess(candidat);
        }
    }
}

void ExperimentMananger::tryToProcess(Task* _task)
{
    if((memoryLeft() >= _task->memory()) && _task->ready())
    {
        m_isNowProcesing << _task;
        m_processQue.removeOne(_task);
    }
}
