#pragma once

#include "dbopl.h"

class DosboxOPL
{
    public:
        DosboxOPL(unsigned int soundSampleRate = 22050, unsigned int soundChannels = 1);
        ~DosboxOPL();
    protected:
        OPL::DOSBox::DBOPL::Chip mainChip;
    private:
    unsigned int mainSoundChannels;
    unsigned int mainSoundSampleRate;
};
