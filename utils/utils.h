// Shared includes and functions

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include <sys/types.h>
#include <time.h>

void Utils_shutdown(void);
_Bool Utils_isShuttingDown(void);
void sleep_msec(long msec);

#endif