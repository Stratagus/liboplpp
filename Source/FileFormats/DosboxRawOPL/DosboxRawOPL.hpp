/*!
 *  \brief     The file handler for the Dosbox Raw OPL format
 *  \details    This class handles the reading and writing of
 *          Dosbox RAW OPL files in both the v0.1 spec and
 *          v2.0 spec. Allowing for them to be synthesized to
 *          one of the supported output formats. Allow data is 
 *          to be in LITTLE ENDIAN.
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      May 14, 2014
 *  \copyright LGPLv2
 */
#ifndef DosboxRawOPL_Header
#define DosboxRawOPL_Header

#include <string>
#include <fstream>
#include <vector>

#if defined VERBOSE
    #include <iostream>
#endif

class DosboxRawOPL
{
    //Tells us what kind of OPL hardware we are dealing with, these values match
    //the DRO file spec (In terms of OPL2 == 0)
    enum OPLHardwareType
    {
        opl2 = 0,
        opl3 = 1,
        dualOpl2 = 2,
        invalidOpl = -1,
    };
    
    public:
        DosboxRawOPL();
        ~DosboxRawOPL();
    
    
        void ReadDroFile(const std::string &droFilePath);
        void ReadDro(const std::vector<char> *targetDroData);
    
    protected:
        OPLHardwareType hardwareEmulator;
    
        uint16_t droMajorVersion;
        uint16_t droMinorVersion;
    
        //Version Shared Data Objects
    
    
        //Version 0.1 ONLY Data Objects
        //Version 2.0 ONLY Data Objects
    
    private:
};

#endif