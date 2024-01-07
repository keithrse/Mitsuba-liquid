#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance(); //This manager is used to obtain parameters for pre existing materials
    /*
    //Like in the PhysicsMatters tutorial, will add a detector volume. Thin layer of aerogel.
    //Start by describing the properties of the material
    G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2); //Last parameter is number of components
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Element *C = nist->FindOrBuildElement("C");

    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    //Adding refractive index properties of the aerogel
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    //Define layer of water
    G4Material *waterMat = nist->FindOrBuildMaterial("G4_WATER");
    G4double rindexWater[2] = {1.333, 1.333};

    G4MaterialPropertiesTable *mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", energy, rindexWater, 2);

    waterMat->SetMaterialPropertiesTable(mptWater);

*/
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

    //Adding the thin layer of Aerogel 
/*
    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, waterMat, "logicalRadiator");

    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m),
logicRadiator, "physRadiator", logicWorld, false, 0, true);

*/
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
