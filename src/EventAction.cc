#include "G4RunManager.hh"
#include <ctime>
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4ParticleDefinition.hh"
EventAction::EventAction() : G4UserEventAction()
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
    m_NOp    = 0;
    m_DeltaE = 0;

    m_PName  = "";
    m_KEi    = 0;
    m_PFound = false;
    m_Rnum = 0;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *)
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
    m_NOp    = 0;
    m_DeltaE = 0;

    m_PName  = "";
    m_KEi    = 0;
    m_PFound = false;
    m_Rnum = 0;
}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{
    auto AM = G4CsvAnalysisManager::Instance();
     if(m_NOp < 5)
        {
          G4int ENofEvent = anEvent -> GetEventID();
          AM -> FillNtupleIColumn(2,0,ENofEvent);
          AM -> AddNtupleRow(2);
          G4RunManager::GetRunManager() -> AbortEvent();
          return;
        } 

    AM -> FillNtupleIColumn(1, 0, anEvent -> GetEventID());
    AM -> FillNtupleSColumn(1, 1, m_PName);
    AM -> FillNtupleDColumn(1, 2, m_KEi);
    AM -> FillNtupleDColumn(1, 3, m_DeltaE);
    AM -> FillNtupleIColumn(1, 4, m_NOp);
    AM -> FillNtupleIColumn(1, 5, m_Rnum);
    AM -> AddNtupleRow(1);

}


void EventAction::AddScint()
{
	m_NScint++;
}

void EventAction::AddCeren()
{
	m_NCeren++;
}


void EventAction::SetPrimaryName(G4String pname)
{
	m_PName = pname;
}

void EventAction::SetPrimaryEnergy(G4double kei)
{
	m_KEi = kei;
}

void EventAction::SetPrimaryFound()
{
	m_PFound = true;
}

G4bool EventAction::GetPrimaryFound()
{
    return m_PFound;
}


void EventAction::AddOp()
{
	m_NOp++;
}

void EventAction::AddDeltaE(G4double dE)
{
	m_DeltaE += dE;
}

void EventAction::AddRef(G4int num)
{
    m_Rnum += num;
}



