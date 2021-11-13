#include "udp.h"
#include "../pump/pump.h"

static struct sockaddr_in sockAddr;
static struct sockaddr_in sinRemote;

static int socketDescriptor;
static unsigned int sin_len;

void* udpThread(void* arg);
static _Bool stopping = false;
static pthread_t udpThreadId;

void UDP_init(void) {
    initSocket();
	pthread_create(&udpThreadId, NULL, udpThread, NULL);
}

void UDP_cleanup(void) {
	printf("Stopping UDP...\n");
	stopping = true;
	close(socketDescriptor);
	pthread_join(udpThreadId, NULL);
	printf("Done stopping UDP...\n");
	fflush(stdout);
}

void initSocket() {
	// Address
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;                   // Connection may be from network
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);    // Host to Network long
	sockAddr.sin_port = htons(PORT);                 // Host to Network short
	// Create the socket for UDP
	socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
	// Bind the socket to the port (PORT) that we specify
	bind (socketDescriptor, (struct sockaddr*) &sockAddr, sizeof(sockAddr));
}

void listenForData() {
    sin_len = sizeof(sinRemote);
    char messageRx[MSG_MAX_LEN];
    int bytesRx = recvfrom(socketDescriptor,
        messageRx, MSG_MAX_LEN, 0,
        (struct sockaddr *) &sinRemote, &sin_len);

    // Make it null terminated (so string functions work):
    int terminateIdx = (bytesRx < MSG_MAX_LEN) ? bytesRx : MSG_MAX_LEN - 1;
    messageRx[terminateIdx] = 0;
    handleCommand(messageRx);
}

// The UDP server listens for commands from the node.js server and does the corresponding action
// All commands are defined in udp.h
void handleCommand(char* command) {
	printf("current command: %s\n", command);
    if (strncmp(command, GET_MIX, 16) == 0) {
        sendCurrentMix();
	}
	else if (strncmp(command, PUMP_DRINK_NONE, 16) == 0) {
        pump_setDrink(NONE);
        sendCurrentMix();
	}
	else if (strncmp(command, PUMP_DRINK1, 16) == 0) {
        pump_setDrink(DRINK1);
        sendCurrentMix();
	}
	else if (strncmp(command, PUMP_DRINK2, 16) == 0) {
        pump_setDrink(DRINK2);
        sendCurrentMix();
	}
	else if (strncmp(command, PUMP_DRINK3, 16) == 0) {
        pump_setDrink(DRINK3);
        sendCurrentMix();
	}
	else if (strncmp(command, PUMP_DRINK4, 16) == 0) {
        pump_setDrink(DRINK4);
        sendCurrentMix();
	}
	else {
		printf("no command\n");
	}
}

// Sends the current mix to the node.js server to display which drink recipe is currently being mixed
void sendCurrentMix() {
    int currMix = pump_getDrink();
    char buf[256];
	switch(currMix) {
		case NONE:
            snprintf(buf, sizeof buf, "%s %s", "mix", "none");
            break;
        case DRINK1:
            snprintf(buf, sizeof buf, "%s %s", "mix", "drink1");
            break;
        case DRINK2:
            snprintf(buf, sizeof buf, "%s %s", "mix", "drink2");
            break;
        case DRINK3:
            snprintf(buf, sizeof buf, "%s %s ", "mix", "drink3");
            break;
        case DRINK4:
            snprintf(buf, sizeof buf, "%s %s", "mix", "drink4");
            break;
    }
    sendMessage(buf);
}

void sendMessage(char* message) {
	sin_len = sizeof(sinRemote);
    char buf[256];
    snprintf(buf, sizeof buf, "%s %s", "message", message);
	sendto(socketDescriptor,
		buf, strlen(buf),
		0,
		(struct sockaddr *) &sinRemote, sin_len);
}

void* udpThread(void* arg) {
	printf("starting UDP thread\n");
	while (!stopping) {
		listenForData();
	}
	return NULL;
}