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
#include <iterator>
#include <vector>
#include <algorithm>

#pragma message("This is a hack")
#define VERBOSE 5

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
        void ReadDro(std::vector<char> *targetDroData);
    
    protected:
        std::vector<char>::iterator droDataPosition;
        std::vector<char> *droData;

        DosboxRawOPL::OPLHardwareType DetectOPLHardware(const uint8_t &droTypeReferenced);
    
        //***************************
        //Version Shared Data Objects
        //***************************
    
        //The version of dro files
        uint16_t droMajorVersion;
        uint16_t droMinorVersion;
    
        //What kind of OPL hardware configuration was
        //used to create the dro
        OPLHardwareType currentOPLEmulator;
    
        //Length of the Dro (In miniseconds)
        uint32_t audioLength;
    
        //*****************************
        //Version 0.1 ONLY Data Objects
        //*****************************
        uint32_t audioByteLength;
    
        //*****************************
        //Version 2.0 ONLY Data Objects
        //*****************************
    
        //Length of the song in register/value pairs
        uint32_t audioLengthPairs;
        //The data arrangment used
        uint8_t audioFormat;
        //Compression Type
        uint8_t audioCompressionType;
        //Define how long a "short delay" is (in miliseconds)
        uint8_t audioShortDelayLength;
        //Define hwo long a "long delay" is (in miliseconds)
        uint8_t audioLongDelayLength;
        //The number of entries in the codemap
        uint8_t audioCodeMapLength;
    
    private:
};

#endif