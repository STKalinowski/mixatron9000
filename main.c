#include "utils/utils.h"
#include "udp/udp.h"
#include "pump/pump.h"

void init() {
   UDP_init();
   pump_init();
}


int main(int argc, char* args[]) {
    init();

    printf("Working\n");
	while (!Utils_isShuttingDown()) {
		sleep_msec(100);
	}

    printf("Cleaning Up\n");
    UDP_cleanup();
    pump_cleanup();

	return 0;
}