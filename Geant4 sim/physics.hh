#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4RayleighScattering.hh"
#include "G4OpticalPhoton.hh"
#include "G4OpRayleigh.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();

    //virtual void ConstructProcess();
};

#endif
