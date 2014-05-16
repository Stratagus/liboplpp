#liboplpp is a library that emulates the Yamaha YMF262 FM Synthesis sound
#chip

project(oplpp)
cmake_minimum_required(VERSION 2.6)

#Set the current version of the library
set(LIBOPLPP_MAJOR_VERSION 0)
set(LIBOPLPP_MINOR_VERSION 1)
set(LIBOPLPP_PATCH_VERSION 0)

#If you want debug information add the flag -DVERBOSE= [1-5]
#1 being basic 5 for everything
IF (NOT DEFINED VERBOSE)
    SET(VERBOSE 0)
ENDIF()
ADD_DEFINITIONS(-DVERBOSE=${VERBOSE})

option(RPATH "Relative Runtime Path" OFF)
#Sets the directory for cmake to find Cmake configration packages,
#these packages allow for cmake to find libraries that are not included
#in the standard installation of Cmake. The standard packages can be
#found @ /usr/share/cmake-2.8/Modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})


#Find the size of different types
include(CheckTypeSize)

check_type_size("unsigned char" UNSIGNED_CHAR_SIZE)
check_type_size("unsigned int" UNSIGNED_INT_SIZE)
check_type_size("unsigned long long" UNSIGNED_LONG_LONG_SIZE)
check_type_size("unsigned short" UNSIGNED_SHORT_SIZE)

add_definitions(-DSIZEOF_UNSIGNED_CHAR=${UNSIGNED_CHAR_SIZE}
				-DSIZEOF_UNSIGNED_INT=${UNSIGNED_INT_SIZE}
				-DSIZEOF_UNSIGNED_LONG_LONG=${UNSIGNED_LONG_LONG_SIZE}
				-DSIZEOF_UNSIGNED_SHORT=${UNSIGNED_SHORT_SIZE})



#Source directory variables
#These allow for folders in the source and unittesting to be moved
#without having to manually change each individual filepath, they
#also act as shortcuts.
set(SOURCE_DIR "./Source")
set(LIBRARY_DIR "./Libraries")
set(OPLPLAYER_SOURCE_DIR "./OPLPlayer")
set(UNITTEST_DIR "./UnitTests")

#Different file format supported by liboplpp
set(FILEFORMATS_DIR "${SOURCE_DIR}/FileFormats")
set(PCMWAV_DIR "${FILEFORMATS_DIR}/PCMWav")
set(DRO_DIR "${FILEFORMATS_DIR}/DosboxRawOPL")

#Different OPL emulators offered
set(EMULATORS_DIR "${SOURCE_DIR}/Emulators")
set(DOSBOX_SOURCE_DIR "${EMULATORS_DIR}/DosboxOPL")

#Add LibMidi for decoding
ADD_SUBDIRECTORY(${LIBRARY_DIR}/libmidi/src)

include_directories(${LIBRARY_DIR}/libmidi/src)

set(LIBOPLPP_SOURCE
		${SOURCE_DIR}/liboplpp.hpp
		${SOURCE_DIR}/liboplpp.cpp
	)

set(LIBOPLPP_EXCEPTION_SOURCE
		${SOURCE_DIR}/Exceptions/OplppException.hpp
		${SOURCE_DIR}/Exceptions/OplppException.cpp
	)

set(LIBOPLPP_UNITTEST_SOURCE
		${UNITTEST_DIR}/main.hpp
		${UNITTEST_DIR}/main.cpp
		${UNITTEST_DIR}/APITest/APITest.hpp
		${UNITTEST_DIR}/APITest/APITest.cpp
	)

set(LIBOPLPP_PCMWAV_SOURCE
		${PCMWAV_DIR}/PCMWav.hpp
		${PCMWAV_DIR}/PCMWav.cpp
	)

set(LIBOPLPP_DOSBOXRAWOPL_SOURCE
		${DRO_DIR}/DosboxRawOPL.hpp
		${DRO_DIR}/DosboxRawOPL.cpp
	)

set(DOSBOX_OPL_SOURCE
		${DOSBOX_SOURCE_DIR}/dbopl.h
		${DOSBOX_SOURCE_DIR}/dbopl.cpp
		${DOSBOX_SOURCE_DIR}/DosboxOPL.hpp
		${DOSBOX_SOURCE_DIR}/DosboxOPL.cpp
	)

set(OPLPLAYER_SOURCE
		${OPLPLAYER_SOURCE_DIR}/main.cpp
		${OPLPLAYER_SOURCE_DIR}/main.hpp
	)

#Code groupings allow for IDEs to put files into collections
#instead of simply throwing all files into a pile. This should
#allow for easy navigation through the code base for novice and
#heavy contributors.
source_group(Main FILES ${LIBOPLPP_SOURCE})
source_group(FileFormats\\OPLMidi FILES ${OPLMIDI_SOURCE})
source_group(Exceptions FILES ${LIBOPLPP_EXCEPTION_SOURCE})

source_group(FileFormats\\PCMWAV FILES ${LIBOPLPP_PCMWAV_SOURCE})
source_group(FileFormats\\DRO FILES ${LIBOPLPP_DOSBOXRAWOPL_SOURCE})

source_group(Emulators\\Dosbox FILES ${DOSBOX_OPL_SOURCE})

if(RPATH)
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")
endif()

add_library(oplpp SHARED ${LIBOPLPP_SOURCE} 
						 ${LIBOPLPP_EXCEPTION_SOURCE} 
						 ${OPLMIDI_SOURCE} 

						 ${LIBOPLPP_DOSBOXRAWOPL_SOURCE}
						 ${LIBOPLPP_PCMWAV_SOURCE}

						 ${DOSBOX_OPL_SOURCE})
target_link_libraries(oplpp midi)
if(APPLE)

option(MAKEFRAMEWORK "Create FRAMEWORK" OFF)
option(OSXUNIVERSAL "Universal Build" OFF)

#Check MacPorts include/lib folders
include_directories("/opt/local/include")

link_directories("/opt/local/lib")

if(OSXUNIVERSAL)
	set(CMAKE_OSX_ARCHITECTURES ppc;i386;ppc64;x86_64) 
endif()

if(MAKEFRAMEWORK)
    set_target_properties(oplpp PROPERTIES FRAMEWORK true)
    set_target_properties(oplpp PROPERTIES PUBLIC_HEADER "Source/liboplpp.hpp")
endif()
    set_target_properties(oplpp PROPERTIES LINK_FLAGS "-framework Carbon")
endif()

if(UNIX)
    set_target_properties(oplpp PROPERTIES VERSION ${LIBOPLPP_MAJOR_VERSION}.${LIBOPLPP_MINOR_VERSION}.${LIBOPLPP_PATCH_VERSION})
    set_target_properties(oplpp PROPERTIES SOVERSION ${LIBOPLPP_MAJOR_VERSION}.${LIBOPLPP_MINOR_VERSION}.${LIBOPLPP_PATCH_VERSION})
endif()

if(WIN32)
    set_target_properties(oplpp PROPERTIES OUTPUT_NAME grp)
endif()

#Unittest configuration settings
option(UNITTESTS "Compile Unittests" OFF)
if(UNITTESTS)
	#Search for the required libraries for the project to properly
	#link and compile.
	find_package(Boost REQUIRED COMPONENTS system date_time unit_test_framework)

	add_executable(liboplppUnitTests ${LIBOPLPP_UNITTEST_SOURCE})
	target_link_libraries(liboplppUnitTests oplpp ${Boost_LIBRARIES})
endif()

option(OPLPlayer "Compile OPLPlayer" ON)
if(OPLPlayer)

	add_executable(OPLPlayer ${OPLPLAYER_SOURCE})
	target_link_libraries(OPLPlayer oplpp)

endif()

#Tell the developer the current build options
message("\n\nliboplpp Compile Options\n Unit Tests: ${UNITTESTS} [-DUNITESTS=(off-on)]")
message(" Verbose Level: ${VERBOSE} [-DVERBOSE=[(1-5)] 1-Min 5-Max")
if(APPLE)
message(" Compile Framework: ${MAKEFRAMEWORK} [-DMAKEFRAMEWORK=(off-on)")
endif()