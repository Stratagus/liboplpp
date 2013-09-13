#ifndef DOSBOX_DOSBOX_H
#define DOSBOX_DOSBOX_H

#include "config.h"

void E_Exit(const char * message,...) GCC_ATTRIBUTE( __format__(__printf__, 1, 2));

void MSG_Add(const char*,const char*); //add messages to the internal langaugefile
const char* MSG_Get(char const *);     //get messages from the internal langaugafile

enum MachineType {
	MCH_HERC,
	MCH_CGA,
	MCH_TANDY,
	MCH_PCJR,
	MCH_EGA,
	MCH_VGA
};

extern MachineType machine;

#ifndef DOSBOX_LOGGING_H
#include "logging.h"
#endif // the logging system.

#endif /* DOSBOX_DOSBOX_H */