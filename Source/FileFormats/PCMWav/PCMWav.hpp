/*!
 *  \brief     The writer to PCM wav audio from the OPL chip emulation
 *  \details
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      May 14, 2014
 *  \copyright LGPLv2
 */

#ifndef PCMWav_Header
#define PCMWav_Header

#include <string>

class PCMWav
{
    public:
        PCMWav();
        ~PCMWav();
    
        void FilePath();
        void SetFilePath(const std::string &newFilePath);
    protected:
    private:
        std::string filePath;
};

#endif