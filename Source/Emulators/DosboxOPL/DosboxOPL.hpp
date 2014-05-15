#ifndef DosboxOPL_Header
#define DosboxOPL_Header

#include "dbopl.h"

class DosboxOPL
{
    public:
        DosboxOPL(unsigned int soundSampleRate = 22050, unsigned int soundChannels = 1);
        ~DosboxOPL();
    protected:
    private:
     Chip mainOPLChip;
    unsigned int mainSoundChannels;
    unsigned int mainSoundSampleRate;
};

#endif