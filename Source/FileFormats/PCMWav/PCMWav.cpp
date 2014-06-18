#include "PCMWav.hpp"

PCMWav::PCMWav(const std::string &targetfilePath, const unsigned int &targetSampleRate, const unsigned int &targetChannels)
{
    filePath = targetfilePath;
    sampleRate = targetSampleRate;
    channels = targetChannels;
}

PCMWav::~PCMWav()
{
    
}

void PCMWav::FilePath()
{
    
}

void PCMWav::SetFilePath(const std::string &newFilePath)
{
    
}