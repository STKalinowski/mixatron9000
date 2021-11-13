#include "utils.h"
#include <time.h>

static _Bool shutdown = false;
void Utils_issueShutdown(void) {
	shutdown = true;
}
_Bool Utils_isShuttingDown(void) {
	return shutdown;
}

void sleep_msec(long msec) {
	
	struct timespec sleep_time;
	sleep_time.tv_sec = (msec / 1000);
	sleep_time.tv_nsec = (msec % 1000) * 1000000;
	nanosleep(&sleep_time, NULL);
}
