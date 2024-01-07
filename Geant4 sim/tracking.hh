#ifndef TRACKING_HH
#define TRACKING_HH


#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

#include <unordered_set>
#include <fstream>

class MyTrackingAction : public G4UserTrackingAction
{
public:
    MyTrackingAction();
    ~MyTrackingAction();

    virtual void PreUserTrackingAction(const G4Track* aTrack);

private:
    std::unordered_set<G4int> checkedPhotons;
    std::ofstream myfile;
    int numberOfSteps;
};


#endif
