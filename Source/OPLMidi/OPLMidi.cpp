#include "OPLMidi.hpp"

OPLMidi::OPLMidi(const std::string &filePath)
{
    mainMidi = new MIDI::File(filePath.c_str());
    mainMidiHeader = mainMidi->header();
}

OPLMidi::~OPLMidi()
{
    
}

unsigned int OPLMidi::NumberOfTracks()
{
    if(mainMidiHeader)
    {
        return mainMidiHeader->numTracks();
    }
    else
    {
        throw "Error";
    }
}

unsigned int OPLMidi::FramesPerSecond()
{
    if(mainMidiHeader)
    {
        return mainMidiHeader->framesPerSecond();
    }
    else
    {
        throw "Error";
    }
}

unsigned int OPLMidi::TicksPerFrame()
{
    if(mainMidiHeader)
    {
        return mainMidiHeader->ticksPerBeat();
    }
    else
    {
        throw "Error";
    }
}