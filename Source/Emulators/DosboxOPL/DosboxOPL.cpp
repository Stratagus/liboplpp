#include "DosboxOPL.hpp"

DosboxOPL::DosboxOPL(unsigned int soundSampleRate, unsigned int soundChannels)
{
    //Initalize dbopl itself
    DBOPL_InitTables();
    Chip__Chip(&mainOPLChip);
    Chip__Setup(&mainOPLChip, soundSampleRate);
    
    mainSoundChannels = soundChannels;
    mainSoundSampleRate = soundSampleRate;
}

DosboxOPL::~DosboxOPL()
{
}