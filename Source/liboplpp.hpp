#ifndef liboplpp_H
#define liboplpp_H

/*! \mainpage General Information
 *  liboplpp Motivation
 *  ================
 *  1. Extensive Documentation
 *  2. Cross Platform (Windows, Mac OSX, Linux)
 *  3. C++ (Use of OOP Techniques)\n
 *  4. Offer OPL emulation to digital audio formats
 *
 *  CMake Build Options
 *  ===================
 *  There are three parameters that can be modified.\n
 *  1. VERBOSE - The amount of information outputted to the console
 *      while processing GRP files and ColorPalettes.\n
 *      DEFAULT = 0 Range = [1 - 5]\n
 *      To set add the cmake flag "-DVERBOSE=[DesiredValue]"\n\n
 *  2. UNITTESTS - Compile the Boost Unit tests inluded with libgrp.
 *      This will require that the Boost Library with the Unit Test Framework Module
 *      be compiled and installed.\n To enable unit tests
 *      Add the cmake flag "-DUNITTESTS=on"\n\n
 *  3. SAMPLECODE - To compile the sample code.\n
 *      Add the cmake flag "-DSAMPLECODE=on"\n
 *
 *  Sample Code
 *  ===========
 *  Sample code can be found from the root directory folder\n
 *  "SampleSource/"
 *
 *  Credits
 *  =======
 *  1. Bradley Clemetson\n
 *      @ http://codeprogrammers.net
 *  2. Dosbox Developers (botik32, infbonzay)\n
 *      @ http://www.dosbox.com/
 *  3. Chocolate Doom Developers\n
 *      @ http://www.chocolate-doom.org
 *
 *  Special Thanks
 *  ==============
 *  1. My super duper awesome parents.
 */

//The different Digital Sound Writiers
#include "FileFormats/PCMWav/PCMWav.hpp"
#include "FileFormats/DosboxRawOPL/DosboxRawOPL.hpp"


//The different OPL Implementataions
#include "Emulators/DosboxOPL/DosboxOPL.hpp"


#endif