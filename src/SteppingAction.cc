#include "SteppingAction.hh"
#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4RootAnalysisManager.hh"
SteppingAction::SteppingAction(EventAction* EA): G4UserSteppingAction(), m_EA(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    //Defining particle name
    G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();

    //Defining process
    const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();

    const G4VProcess* proc = step -> GetPostStepPoint() -> GetProcessDefinedStep();
    G4String procname = proc -> GetProcessName();    

    //Defining PostPV
    G4String namePostPV;
	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
	if ( postPV != 0 ) namePostPV = postPV -> GetName();
	else namePostPV = "outside";

    //Defining PrePV
    G4String namePrePV;
	G4VPhysicalVolume* prePV = step -> GetPreStepPoint() -> GetPhysicalVolume();
    namePrePV = prePV -> GetName();

    //Defining Kinetic Energy
    G4double preKinEgy  = step -> GetPreStepPoint()  -> GetKineticEnergy();
    G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();

    G4int ENofStep = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
    
/*
    if ( parName == "gamma" && 2.634*keV <= preKinEgy && preKinEgy <= 25.511*keV)
    {
   
     G4cout << step -> GetTrack() -> GetTrackID() << ", " << parName << ", " << preKinEgy / keV << ", " << step -> GetTrack() -> GetParentID() << ", " << creProc -> GetProcessName() << G4endl;
        }
*/
    // Who is the primary?
    if ( ! m_EA -> GetPrimaryFound() && step -> GetTrack() -> GetTrackID() == 2 )
    {
        m_EA -> SetPrimaryName(parName);
        m_EA -> SetPrimaryEnergy(step -> GetPreStepPoint() -> GetKineticEnergy() / keV);
        m_EA -> SetPrimaryFound();
//       G4cout << "Pre: " << step -> GetPreStepPoint() -> GetKineticEnergy() / keV << G4endl;
//       G4cout << "Post: " << step -> GetPostStepPoint() -> GetKineticEnergy() / keV << G4endl;
    }

    //Counting Optical Photons
    if ( parName == "opticalphoton" && namePostPV == "PMTPhy" && creProc -> GetProcessName() == "Scintillation")
    {
        // Let's count number of photons in an event
        m_EA -> AddOp();
        
        auto AM = G4CsvAnalysisManager::Instance();
        AM -> FillNtupleDColumn(0,0, postKinEgy / eV);
        AM -> FillNtupleIColumn(0,1,ENofStep);
        AM -> AddNtupleRow(0);
        }
    
        
    // Accumulate dE
    if (parName == "gamma" && namePrePV == "ScintPV" )
    {   
        G4double Delegy = step -> GetDeltaEnergy() / keV;
        m_EA -> AddDeltaE(Delegy);
    }



    auto stat = step -> GetTrack() -> GetTrackStatus();
    if ( parName == "opticalphoton" && stat == fStopAndKill && namePostPV == "PMTPhy")
    {
        G4int num = (step -> GetTrack() -> GetCurrentStepNumber() - 1)*0.5;
            m_EA -> AddRef(num);
    }

}

