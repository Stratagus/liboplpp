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
    
    droData = nullptr;
}

DosboxRawOPL::~DosboxRawOPL()
{
    if(droData)
    {
        delete droData;
        droData = nullptr;
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
        ReadDroHeader(droData);
    }
}

void DosboxRawOPL::ReadDroHeader(std::vector<uint8_t> *targetDroData)
{
    droData = targetDroData;
    targetDroData = NULL;
    
    droDataPosition = droData->begin();
    
    //Read in the dro signature
    std::string readInSignature;
    readInSignature.resize(8);
    
    std::copy(droDataPosition, (droDataPosition + 8), (char *) &readInSignature[0]);
    droDataPosition += 8;

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
    std::copy(droDataPosition, (droDataPosition + 2), &droMajorVersion);
    droDataPosition += 2;
    std::copy(droDataPosition, (droDataPosition + 2), &droMinorVersion);
    droDataPosition += 2;
    
    #if VERBOSE >= 2
        std::cout << "Dro Version: " << droMajorVersion << '.' << droMinorVersion << '\n';
    #endif
    
    //If we are reading in a 0.1 dro, read in this order
    if((droMajorVersion == 0) && (droMinorVersion == 1))
    {
        ReadDro01();
    }
    //The file detected is a dro 2.X
    else if(droMajorVersion == 2)
    {
        ReadDro20();
    }
    //Invalid/Unknown dro version
    else
    {
        throw "Invalid/Unknown Dro version";
    }
}

std::vector<uint8_t> *DosboxRawOPL::GeneratePCM()
{
    std::vector<uint8_t> *generatePCM = new std::vector<uint8_t>;
    
    //Initialize the DosboxOPL library

}

void DosboxRawOPL::ReadDro01()
{
    //Read in the audio length (in milliseconds)
    std::copy(droDataPosition, (droDataPosition + 4), &audioLength);
    droDataPosition += 4;
    //Read in the audio length (in bytes)
    std::copy(droDataPosition, (droDataPosition + 4), &audioByteLength);
    droDataPosition += 4;
    
    //Determine the OPL configuration at the time of recording
    uint8_t readOPLHardwareType;
    std::copy(droDataPosition, (droDataPosition + 1), &readOPLHardwareType);
    droDataPosition += 1;

    //In early files, the field was a UINT8, however in most common (recent) files it is a
    //UINT32LE with only the first byte used. Unfortunately the version number was not changed
    //between these revisions, so the only way to correctly identify the formats is to check the three
    //iHardwareExtra bytes. If these are all zero then they can safely be ignored (iHardwareType was a UINT32.)
    //If any of the three bytes in iHardwareExtra are non-zero, then this is an early
    //revision of the format and those three bytes are actually song data[1].
    //From http://www.shikadi.net/moddingwiki/DRO_Format
    
    //Check whether there is a padded hardware id(
    uint32_t paddedHardwareData;
    std::copy(droDataPosition, (droDataPosition + 3), &paddedHardwareData);
    
    if(paddedHardwareData == 0)
    {
    #if VERBOSE >= 3
        std::cout << "The Hardware ID was PADDED\n";
    #endif
        droDataPosition += 3;
    }
    else
    {
    #if VERBOSE >= 3
        std::cout << "The Hardware ID was NOT PADDED\n";
    #endif
    }

    currentOPLEmulator = DetectOPLHardware(readOPLHardwareType);
    
    if(currentOPLEmulator == invalidOpl)
    {
        throw "Unknown/Invalid OPL hardware type";
    }
    
    #if VERBOSE >= 2
        std::cout << "Detected Hardware as " << DosboxRawOPL::GetOPLHardware(currentOPLEmulator) << '\n';
    #endif
    
    
    //Now that we are up to the song data, lets get parsing it
#pragma message ("While not in the spec there appears to be a dead 4 byte length")
    droDataPosition += 4; //The data position should now be at 28.
    
    
}

void DosboxRawOPL::ReadDro20()
{
    //Read in the length in pairs
    std::copy(droDataPosition, (droDataPosition + 4), &audioLengthPairs);
    droDataPosition += 4;
    #if VERBOSE >= 2
        std::cout << "Length of song in register/value pairs: " << audioLengthPairs << '\n';
    #endif

    //Read in the length of the song data in miliseconds
    std::copy(droDataPosition, (droDataPosition + 4), &audioLength);
    droDataPosition += 4;
    #if VERBOSE >= 2
        std::cout << "Length of song in miliseconds is: " << audioLength << "ms\n";
    #endif

   //Determine the OPL configuration at the time of recording
   uint8_t readOPLHardwareType;
   std::copy(droDataPosition, (droDataPosition + 1), &readOPLHardwareType);
   droDataPosition += 1;
   currentOPLEmulator = DetectOPLHardware(readOPLHardwareType);
   #if VERBOSE >= 2
       std::cout << "Detected Hardware as " << DosboxRawOPL::GetOPLHardware(currentOPLEmulator) << '\n';
   #endif

   //Determine the format data arrangement of the dro
   std::copy(droDataPosition, (droDataPosition + 1), &audioFormat);
   droDataPosition += 1;
   #if VERBOSE >= 2
       std::cout << "Dro V2 audio format: " << static_cast<unsigned int>(audioFormat) << '\n';
   #endif

   //Determine the compression type
   std::copy(droDataPosition, (droDataPosition + 1), &audioCompressionType);
   droDataPosition += 1;
   #if VERBOSE >= 2
       std::cout << "Dro V2 compression type: " << static_cast<unsigned int>(audioCompressionType) << '\n';
   #endif

   //Short delay time
   std::copy(droDataPosition, (droDataPosition + 1), &audioShortDelayLength);
   droDataPosition += 1;
   #if VERBOSE >= 2
       std::cout << "Dro V2 SHORT delay time: " << static_cast<unsigned int>(audioShortDelayLength) << "ms\n";
   #endif

   //Long delay time
   std::copy(droDataPosition, (droDataPosition + 1), &audioLongDelayLength);
   droDataPosition += 1;
   #if VERBOSE >= 2
       std::cout << "Dro V2 LONG delay time: " << static_cast<unsigned int>(audioLongDelayLength) << "ms\n";
   #endif


   //Codemap Length
   std::copy(droDataPosition, (droDataPosition + 1), &audioCodeMapLength);
   droDataPosition += 1;
   #if VERBOSE >= 2
       std::cout << "Dro V2 Audio code map length: " << static_cast<unsigned int>(audioCodeMapLength) << "ms\n";
   #endif

   //Read in the audio code map
   codeMapTable.resize(audioCodeMapLength);
   std::copy(droDataPosition, (droDataPosition + audioCodeMapLength), &codeMapTable.at(0));
   droDataPosition += audioCodeMapLength;

    #if VERBOSE >= 5
        std::cout << "***Codetable Start***\n";
        for(uint8_t code : codeMapTable)
            std::cout << static_cast<unsigned int>(code);
        std::cout << "\n***Codetable End***\n";
    #endif

   //Ensure that the OPL hardware is correct.
   if(currentOPLEmulator == invalidOpl)
   {
       throw "Unknown/Invalid OPL hardware type";
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

#if defined VERBOSE
std::string DosboxRawOPL::GetOPLHardware(DosboxRawOPL::OPLHardwareType HardwareType)
{
    switch (HardwareType)
    {
        case opl2:
        {
            return "OPL2";
        }
        case opl3:
        {
            return "OPL3";
        }
        case dualOpl2:
        {
            return "Dual OPL2";
        }
        default:
        {
            return "Invalid OPL";
        }
    }
}
#endif
