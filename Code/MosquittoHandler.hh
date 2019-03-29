#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>

class MosquittoHandler {
public:
	MosquittoHandler(const char *host, int port, int keepAlive);
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
	void connectCallback(struct mosquitto *mosq, void *userdata, int result);
	void messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
}
