#include "tracking.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpBoundaryProcess.hh"

MyTrackingAction::MyTrackingAction()
{
    myfile.open("initialPhotonData.csv");
    numberOfSteps = 0;
}

MyTrackingAction::~MyTrackingAction()
{
    myfile.close();
}

void MyTrackingAction::PreUserTrackingAction(const G4Track* aTrack) {

    if(!myfile.is_open()) {
        G4cout<<"File did not open properly"<<G4endl;
        return;
    };

    const G4VProcess* process = aTrack->GetCreatorProcess();

    if(process && process->GetProcessName() == "Cerenkov") {
    //Note the first check is for photons who have a null creator process
        if(aTrack->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
            if(checkedPhotons.find(aTrack->GetTrackID()) == checkedPhotons.end()) {

                //G4cout<<"Position: "<<aTrack->GetPosition();
                //G4cout<<" Direction: "<<aTrack->GetMomentumDirection();
                //G4cout<<" Energy: "<<aTrack->GetTotalEnergy()<<" | "<<aTrack->GetTrackID()<<G4endl;

                checkedPhotons.insert(aTrack->GetTrackID());

                numberOfSteps++;

                myfile<<aTrack->GetTrackID();
                myfile<<",";

                const G4ThreeVector trackPos = aTrack->GetPosition();
                myfile<<trackPos.getX();
                myfile<<",";
                myfile<<trackPos.getY();
                myfile<<",";
                myfile<<trackPos.getZ();
                myfile<<",";

                const G4ThreeVector trackMomDirection = aTrack->GetMomentumDirection();
                myfile<<trackMomDirection.getX();
                myfile<<",";
                myfile<<trackMomDirection.getY();
                myfile<<",";
                myfile<<trackMomDirection.getZ();
                myfile<<",";

                myfile<<aTrack->GetTotalEnergy();
                myfile<<"\n";
            }
        }
    };
    //if(process->GetProcessName() == "Cerenkov") {
    //    G4cout<<"Cerenkov"<<G4endl;
    //};
}
