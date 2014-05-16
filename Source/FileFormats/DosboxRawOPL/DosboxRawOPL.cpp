#include "DosboxRawOPL.hpp"

DosboxRawOPL::DosboxRawOPL()
{
    hardwareEmulator = invalidOpl;
}

DosboxRawOPL::~DosboxRawOPL()
{
    
}

void DosboxRawOPL::ReadDroFile(const std::string &droFilePath)
{
    //This will hold the entire dro in memory, allowing us to process
    //it by the same method.
    std::vector<char> *droData = NULL;
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
        droData = new std::vector<char>;
        inputFile.seekg(0, std::ios::beg);
        droData->resize(static_cast<std::size_t>(length));
        inputFile.read((char *)&droData->front(), static_cast<std::size_t>(length));
        
        //Process the data
        try
        {
            ReadDro(droData);
            
        }
        catch (...)
        {
            delete droData;
            droData = NULL;
            throw "Invalid Dro file";
        }

        
        //Delete the dro data we read in
        delete droData;
        droData = NULL;
    }
}

void DosboxRawOPL::ReadDro(const std::vector<char> *targetDroData)
{
    
}
