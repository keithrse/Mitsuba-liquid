#include "stepping.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4OpBoundaryProcess.hh"

MySteppingAction::MySteppingAction()
{}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* aStep) {

        if(aStep->GetTrack()->GetTrackID() == 1) {

            if(aStep->GetTrack()->GetPosition().getZ() > 10) {
                aStep->GetTrack()->SetTrackStatus(fStopAndKill);
            }
        }
/*
        if(aStep->GetTrack()->GetTrackID() > 1) {
            const G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
            const G4VProcess* process = postStepPoint->GetProcessDefinedStep();
            if(process && process->GetProcessName() == "OpAbsorption") {
                G4cout<<"Absorption occured"<<G4endl;
            }
        }
*/
        //const G4VProcess* process = aStep->GetPostStepPoint()->GetProcessDefinedStep();

        //G4cout<<process->GetProcessName()<<G4endl;

        // Check if the current step corresponds to Cerenkov photons
        //if(process->GetProcessName() == "Cerenkov") {G4cout<<"Cerenkov"<<G4endl;};
        /*
        if (aStep->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
            G4double energy = aStep->GetTrack()->GetTotalEnergy();
            G4ThreeVector position = aStep->GetTrack()->GetPosition();
            G4ThreeVector direction = aStep->GetTrack()->GetMomentumDirection();

            // Print or store the information as needed
            G4cout << "Photon - Energy: " << energy << " | Position: " << position << " | Direction: " << direction << G4endl;
        }
        */
}
