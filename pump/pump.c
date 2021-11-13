#include "pump.h"

#define TRUE 1
#define FALSE 0

#define Primary_Pump_Pin 66     // 66    P8_7    Primary Pump
#define Pump1_Pin 69            // 69    P8_9    Dosing Pump 1
#define Pump2_Pin 45            // 45    P8_11   Dosing Pump 2
#define Pump3_Pin 47            // 47    P8_15   Dosing Pump 3
#define Pump4_Pin 27            // 27    P8_17   Dosing Pump 4
#define Solenoid1_Pin 67        // 67    P8_8    Solenoid 1
#define Solenoid2_Pin 68        // 68    P8_10   Solenoid 2
int gpios[] = {Primary_Pump_Pin,Pump1_Pin,Pump2_Pin,Pump3_Pin,Pump4_Pin,Solenoid1_Pin,Solenoid2_Pin};

static _Bool stopping = false;
static pthread_t pumpThreadId;

static int currentDrink = NONE;

void setupGPIO() {
  char buffer [70];
  struct timespec quick_sleep = {0, 50000000L};
  for (int i = 0;i<7;i++){
    sprintf(buffer, "echo %d > /sys/class/gpio/export 2> /dev/null",gpios[i]);
    system(buffer);
    nanosleep(&quick_sleep,NULL);
    bzero(buffer,70);
    sprintf(buffer, "echo out > /sys/class/gpio/gpio%d/direction 2> /dev/null",gpios[i]);
    system(buffer);
    bzero(buffer,70);
    sprintf(buffer, "echo 0 > /sys/class/gpio/gpio%d/value 2> /dev/null",gpios[i]);
    system(buffer);
  }
}

void pump_init(void) {
    setupGPIO();
    sleep_msec(330); 
	  pthread_create(&pumpThreadId, NULL, pumpThread, NULL);
}

void pump_cleanup(void) {
	printf("Stopping gpio...\n");

	stopping = true;
	pthread_join(pumpThreadId, NULL);

	printf("Done stopping gpio...\n");
	fflush(stdout);
}


void Primary_Pump(int state) {
  if (state) activate(Primary_Pump_Pin);
  else deactivate(Primary_Pump_Pin);
}

void Pump1(int state) {
  if (state) activate(Pump1_Pin);
  else deactivate(Pump1_Pin);
}
void Pump2(int state) {
  if (state) activate(Pump2_Pin);
  else deactivate(Pump2_Pin);
}

void Pump3(int state) {
  if (state) activate(Pump3_Pin);
  else deactivate(Pump3_Pin);
}

void Pump4(int state) {
  if (state) activate(Pump4_Pin);
  else deactivate(Pump4_Pin);
}

void Solenoid1(int state) {
  if (state) activate(Solenoid1_Pin);
  else deactivate(Solenoid1_Pin);
}

void Solenoid2(int state) {
  if (state) activate(Solenoid2_Pin);
  else deactivate(Solenoid2_Pin);
}

static void activate(int gpio) {
  char buffer [70];
  sprintf(buffer, "echo 1 > /sys/class/gpio/gpio%d/value 2> /dev/null",gpio);
  system(buffer);
}

static void deactivate(int gpio) {
  char buffer [70];
  sprintf(buffer, "echo 0 > /sys/class/gpio/gpio%d/value 2> /dev/null",gpio);
  system(buffer);
}

void writeToFile(char* file, char* value) {
	FILE *pFile = fopen(file, "w");
	if (pFile == NULL) {
		printf("ERROR OPENING %s.", file);
		exit(1);
	}
	int charWritten = fprintf(pFile, "%s", value);
	if (charWritten <= 0) {
		printf("ERROR WRITING DATA");
		exit(1);
	}
	fclose(pFile);
}

int pump_getDrink() {
    return currentDrink;
}


void pump_setDrink(int newDrink) {
    currentDrink = newDrink;
}

// TODO: implement this so the pumps will operate for the correct drinks
void make_drink(void) {
  printf("do stuff\n");
}

// The pumpThread is continously running. Whenever the udp server gets a command from the node.js server
// the udp server will change the "currentDrink" state and the pump thread will mix the updated drink
void* pumpThread(void* arg) {
    printf("Pump Control Test: select device to test\n");
    printf("\t 1) Primary Pump\n");
    printf("\t 2) Pump#1\n");
    printf("\t 3) Pump#2\n");
    printf("\t 4) Pump#3\n");
    printf("\t 5) Pump#4\n");
    printf("\t 6) Pump#4\n");
    printf("\t 7) Pump#4\n");

    while (!stopping) {
      switch(currentDrink) {
        case NONE:
          break;
        case DRINK1:
          // TODO: make_drink(DRINK1);
          break;
        case DRINK2:
          // TODO: make_drink(DRINK2);
          break;
        case DRINK3:
          // TODO: make_drink(DRINK3);
          break;
        case DRINK4:
          // TODO: make_drink(DRINK4);
          break;
    }
    sleep_msec(100);
	}
	printf("returning from gpioThread \n");
	return NULL;
}