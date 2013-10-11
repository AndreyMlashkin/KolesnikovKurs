#include "simpletask.h"
#include "modelmananger.h"
#include "complextask.h"

ModelMananger::ModelMananger(int _memorySize)
    : m_memorySize(_memorySize)
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

    one->setDepended(1, five);
    two->setDepended(1, four);
    three->setDepended(2, fiveThree, sixThree);
    four->setDepended(2, sixFour, sevenFour);
    five->setDepended(1, sevenFive);
    six->setDepended(1, sevenSix);

    m_processQue.push_back(one);
    m_processQue.push_back(two);
    m_processQue.push_back(three);
    m_processQue.push_back(four);
    m_processQue.push_back(five);
    m_processQue.push_back(six);
    m_processQue.push_back(seven);
}

int ModelMananger::calcTime()
{
    int step = 0;
    while(m_processQue.isEmpty())
    {

        step++;
    }
    return step;
}
