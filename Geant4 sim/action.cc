#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    //MyRunAction *runAction = new MyRunAction(); NEED TO RESTORE THE RUN.CC AND RUN.HH FILES AS SEEN INPHYSICS MATTERS TUTORIAL
    //SetUserAction(runAction);

    //MySteppingAction *steppingAction = new MySteppingAction();
    //SetUserAction(steppingAction);
}
