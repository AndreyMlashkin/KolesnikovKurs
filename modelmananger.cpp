#include "simpletask.h"
#include "modelmananger.h"

ModelMananger::ModelMananger()
{
    Task* one   = new SimpleTask(4, 4, 2);
    Task* two   = new SimpleTask(3, 3, 1);
    Task* three = new SimpleTask(5, 5, 2);
    Task* four  = new SimpleTask(0, 0, 0);


//    Task* fiveOne   = new Task(4, 4, 1);
//    Task* fiveThree = new Task(2, 2, 1);

//    Task* sixThree  = new Task(6, 6, 3);
//    Task* sixFour   = new Task(5, 5, 2);

//    Task* sevenFour = new Task(2, 2, 0);
//    Task* sevenFive = new Task(7, 7, 3);
//    Task* sevenSix  = new Task(3, 3, 1);
}
