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

class OPLMidi
{
    public:
        OPLMidi();
        ~OPLMidi();
    
        void LoadMidi(const std::string &filePath);
    
    protected:
    private:
};


#endif