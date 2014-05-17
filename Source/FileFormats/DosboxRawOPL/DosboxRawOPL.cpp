#include "DosboxRawOPL.hpp"

DosboxRawOPL::DosboxRawOPL()
{
    currentOPLEmulator = invalidOpl;
    droMajorVersion = 0;
    droMinorVersion = 0;
    audioLength = 0;
    audioByteLength = 0;
    audioLengthPairs = 0;
    audioFormat = 0;
    audioCompressionType = 0;
    audioShortDelayLength = 0;
    audioLongDelayLength = 0;
    audioCodeMapLength = 0;
    
    droData = NULL;
}

DosboxRawOPL::~DosboxRawOPL()
{
    if(droData)
    {
        delete droData;
        droData = NULL;
    }
}

void DosboxRawOPL::ReadDroFile(const std::string &droFilePath)
{
    //This will hold the entire dro in memory, allowing us to process
    //it by the same method.
    std::vector<uint8_t> *droData = NULL;
    std::ifstream inputFile(droFilePath.c_str(), std::ios::binary);
    inputFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    
    //Seek to the front of the file
    inputFile.seekg(0, std::ios::end);
    
    //Get the length (in bytes) of the file
    std::streampos length(inputFile.tellg());
    
    //If the file contains data
    if(!length)
    {
        throw "There is no valid dro";
    }
    else
    {
        //Read the data into a vector to parse the data
        droData = new std::vector<uint8_t>;
        inputFile.seekg(0, std::ios::beg);
        droData->resize(static_cast<std::size_t>(length));
        inputFile.read((char *)&droData->front(), static_cast<std::size_t>(length));
        
        //Process the data
        ReadDro(droData);
    }
}

void DosboxRawOPL::ReadDro(std::vector<uint8_t> *targetDroData)
{
    droData = targetDroData;
    targetDroData = NULL;
    
    droDataPosition = droData->begin();
    
    //Read in the dro signature
    std::string readInSignature;
    readInSignature.resize(8);
    
    std::copy(droDataPosition, (droDataPosition += 8), (char *) &readInSignature[0]);
    
    #if VERBOSE >= 2
        std::cout << "Read Signature: " << readInSignature << '\n';
    #endif
    if(readInSignature != "DBRAWOPL")
    {
        throw "Invalid OPL file";
    }
    #if VERBOSE >= 5
        else
        {
            std::cout << "Verified Signature\n";
        }
    #endif
    
    //Read the major&minor the file was encoded with
    std::copy(droDataPosition, (droDataPosition += 2), &droMajorVersion);
    std::copy(droDataPosition, (droDataPosition += 2), &droMinorVersion);
    
    #if VERBOSE >= 2
        std::cout << "Dro Version: " << droMajorVersion << '.' << droMinorVersion << '\n';
    #endif
    
    //If we are reading in a 0.1 dro, read in this order
    if((droMajorVersion == 0) && (droMinorVersion == 1))
    {
        //Read in the audio length (in miliseconds)
        std::copy(droDataPosition, (droDataPosition += 4), &audioLength);
        //Read in the audio length (in bytes)
        std::copy(droDataPosition, (droDataPosition += 4), &audioByteLength);
        
        //Determine the OPL configuration at the time of recording
        uint8_t readOPLHardwareType;
        std::copy(droDataPosition, (droDataPosition + 1), &readOPLHardwareType);
        
        //In early files, the field was a UINT8, however in most common (recent) files it is a
        //UINT32LE with only the first byte used. Unfortunately the version number was not changed
        //between these revisions, so the only way to correctly identify the formats is to check the three
        //iHardwareExtra bytes. If these are all zero then they can safely be ignored (iHardwareType was a UINT32.)
        //If any of the three bytes in iHardwareExtra are non-zero, then this is an early
        //revision of the format and those three bytes are actually song data[1].
        //From http://www.shikadi.net/moddingwiki/DRO_Format
        
        //Check whether there is a padded hardware id(
        uint32_t paddedHardwareData;
        std::copy(droDataPosition, (droDataPosition + 4), &paddedHardwareData);
        
        if(paddedHardwareData == 0)
        {
            #if VERBOSE >= 3
                std::cout << "The Hardware ID was PADDED\n";
                droDataPosition += 4;
            #endif
        }
        else
        {
            #if VERBOSE >= 3
                std::cout << "The Hardware ID was NOT PADDED\n";
                droDataPosition += 1;
            #endif
        }
        
        //
        currentOPLEmulator = DetectOPLHardware(readOPLHardwareType);
        
        if(currentOPLEmulator == invalidOpl)
        {
            throw "Unknown/Invalid OPL hardware type";
        }
    
    #if VERBOSE >= 2
        std::cout << "Detected Hardware as ";
        
        switch (currentOPLEmulator)
        {
            case opl2:
            {
                std::cout << "OPL2";
                break;
            }
            case opl3:
            {
                std::cout << "OPL3";
                break;
            }
            case dualOpl2:
            {
                std::cout << "Dual OPL2";
                break;
            }
            default:
            {
                std::cout << "Invalid OPL";
                break;
            }
        }
        std::cout << '\n';
    #endif
    }
    //The file detected is a dro 2.X
    else if(droMajorVersion == 2)
    {
        
    }
    //Invalid/Unknown dro version
    else
    {
        throw "Invalid/Unknown Dro version";
    }
}

DosboxRawOPL::OPLHardwareType DosboxRawOPL::DetectOPLHardware(const uint8_t &droTypeReferenced)
{
    switch (droTypeReferenced)
    {
        case 0:
        {
            return DosboxRawOPL::opl2;
        }
        case 1:
        {
            return DosboxRawOPL::opl3;
        }
        case 3:
        {
            return DosboxRawOPL::dualOpl2;
        }
        default:
        {
            return DosboxRawOPL::invalidOpl;
        }
    }
}