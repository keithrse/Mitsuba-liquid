#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    //Telling the program to register the types of physics we want for our
    //application. In this case Cherenkov Detection
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
/*
void MyPhysicsList::ConstructProcess()
{
    // Get the process manager for optical photons
    G4ProcessManager* processManager = G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

    // Remove Rayleigh scattering process for optical photons
    if (processManager) {
        G4OpRayleigh* rayleighProcess = new G4OpRayleigh();
        processManager->InActivateProcess(rayleighProcess);
    }
}
*/
