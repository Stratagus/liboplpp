#ifndef oplMidi_Header
#define oplMidi_Header

/*!
 *  \brief Midi synthesizer
 *  \details
 *  \author    Bradley Clemetson
 *  \version   0.0.1
 *  \date      Janurary 5, 2014
 *  \copyright GPL
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
    
    protected:
            MIDI::File *mainMidi;
    private:

    
};


#endif