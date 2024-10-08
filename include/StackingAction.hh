#ifndef STACKINGACTION_HH
#define STACKINGACTION_HH 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class StackingAction : public G4UserStackingAction
{
    public:
        StackingAction();
        ~StackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;

};

#endif
