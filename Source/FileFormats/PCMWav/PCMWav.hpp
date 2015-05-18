/*!
 *  \brief     The writer to PCM wav audio from the OPL chip emulation
 *  \details
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      May 14, 2014
 *  \copyright LGPLv2
 */

#pragma once

#include <string>

class PCMWav
{
    public:
        //How is the PCM data written
        enum Encoding
        {
            Signed16LE,
            Signed16BE,
            Signed32LE,
            Signed32BE,
        };
    
    PCMWav(const std::string &targetfilePath = "audio.wav",
           const unsigned int &targetSampleRate = 22050,
           const unsigned int &targetChannels = 1);
        ~PCMWav();
    
        void FilePath();
        void SetFilePath(const std::string &newFilePath);
    protected:
    
        //Check if the samplerate is valid
    bool validSampleRate;
    private:
        std::string filePath;
        //The sample rate of the audio
        unsigned int sampleRate;
        //The number of channel in the audio
        unsigned int channels;
};