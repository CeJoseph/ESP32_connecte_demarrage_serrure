#ifndef simplyprint_h
#define simplyprint_h

#include <simplyprint.h>

String GetState(int printer_id);
int continuer_impression(int printer_id);
int pauser_impression(int printer_id);
int impression_finit(int printer_id);

#endif