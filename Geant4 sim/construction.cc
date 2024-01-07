#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance(); //This manager is used to obtain parameters for pre existing materials

    G4Material *worldMat = nist->FindOrBuildMaterial("G4_WATER"); //Use nist manager to obtain pre defined material

    //For optical photons need to tell Geant4 the refractive index of the material
    //we are working with
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexWorld[2] = {1.333, 1.333};

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 1.0*m); //Created a world volume 1x1x1 (standard Geant4 being mm)

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    //Parameters for G4PhysicalVolume: rotation, position within the world 
    //we would like the volume to be placed, logical volume, name, volume within
    //which we want this volume to be placed inside, boolean functions, copy number,
    //whether the volume should check for overlaps (should always leave true).

    //Note: If two volumes are going to touch one needs to be the mother volume to the other
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.)
,logicWorld, "physWorld", 0, false, 0, true);

    //Adding the photodetectors
    G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.02*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    for(G4int i = 0; i < 100; i++) {
        for(G4int j = 0; j < 100; j++) {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0,
G4ThreeVector(-0.5*m + (i+0.5)*m / 100, -0.5*m + (j+0.5)*m / 100, 0.49*m), logicDetector, 
"physDetector", logicWorld, false, j+i*100, true);

        }
    }

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
