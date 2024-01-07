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
}
