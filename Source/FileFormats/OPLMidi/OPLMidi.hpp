#ifndef oplMidi_Header
#define oplMidi_Header

/*!
 *  \brief Midi synthesizer
 *  \details
 *  \author    Bradley Clemetson
 *  \version   0.0.1
 *  \date      Janurary 5, 2014
 *  \copyright LGPLv2
 */

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

//Libmidi includes
#include <MIDI.h>

#include "../liboplpp.hpp"

class OPLMidi
{
    public:
        OPLMidi(const std::string &filePath);
        ~OPLMidi();
    
        unsigned int NumberOfTracks();
        unsigned int FramesPerSecond();
        unsigned int TicksPerFrame();
        unsigned int TicksPerBeat();
    protected:
            MIDI::File *mainMidi;
            MIDI::Header *mainMidiHeader;
    private:

    
};


#endif