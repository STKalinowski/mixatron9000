#ifndef _UDP_H_
#define _UDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>			// for strncmp()
#include <unistd.h>			// for close()
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>

#define MSG_MAX_LEN 1024
#define PORT        12345

#define GET_MIX "get_mix"

#define PUMP_DRINK_NONE "pump_none"
#define PUMP_DRINK1 "pump_drink1"
#define PUMP_DRINK2 "pump_drink2"
#define PUMP_DRINK3 "pump_drink3"
#define PUMP_DRINK4 "pump_drink4"

void UDP_init(void);
void UDP_cleanup(void);

void initSocket(void);
void listenForData(void);
void* udpThread(void* arg);
void sendMessage(char* message);
void handleCommand(char* command);

void sendCurrentMix();
void sendCurrentSpeed();


#endif

