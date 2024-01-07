#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    myfile.open("photonHitPositions.csv");
}

MySensitiveDetector::~MySensitiveDetector()
{
    myfile.close();
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory
*ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout  << "Photon position: " << posPhoton << G4endl;

    //Next two lines of code are to regist the copy no. aka j+i*100 of the detectors

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();
    //G4cout << "Detector Hit No: " << copyNo << G4endl;
    //These get the position of the detector that the photon just touched
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();
    //G4cout << "Detector Hit Pos: " << posDetector << G4endl;

    if(myfile.is_open()) {

        myfile<<posDetector.getX();
        myfile<<",";
        myfile<<posDetector.getY();
        myfile<<",";
        myfile<<posDetector.getZ();
        myfile<<",";
        myfile<<track->GetLocalTime();
        myfile<<",";
        myfile<<track->GetGlobalTime();
        myfile<<"\n";
    }
    return true;
}
