#include "G4Electron.hh"
#include "G4OpticalPhoton.hh"
#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    //Parameters for G4ParticleGun: Number of particles per event
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "mu-";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    G4ThreeVector pos(0., 0., 0.); //Created in the centre of the mother volume
    G4ThreeVector mom(0., 0., 1.); //Give particle some momentum in z direction

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(400.*MeV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
