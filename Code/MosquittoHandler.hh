#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>

class MosquittoHandler {
public:
	MosquittoHandler();
	void takeItem();
	void startSequence();
	void reboot();
	void sendEmergency();
	void sequenceReceived();
	void available();
private:
	const char *host;
	int port;
	int keepAlive;
	struct mosquitto mosq*;
	void connectCallback();
	void messageCallback();
}
