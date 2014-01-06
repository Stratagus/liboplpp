#include "OPLMidi.hpp"

OPLMidi::OPLMidi(const std::string &filePath)
{
    mainMidi = new MIDI::File(filePath.c_str());
}

OPLMidi::~OPLMidi()
{
    
}