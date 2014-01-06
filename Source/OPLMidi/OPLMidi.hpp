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

#include "../liboplpp.hpp"

class OPLMidi
{
    public:
        OPLMidi();
        ~OPLMidi();
    
        void LoadMidi(const std::string &filePath);
        void SynthesizeToWav(const std::string &filePath, OPLSystem targetSynthesizer = DosBox);
    
    protected:
    private:
    
};


#endif