/*
 * To compile, install package libmosquitopp-dev on the Raspberry Pi,
 * then sync sysroots in cross-compilation toolchain.
 * Also link with -lmosquittopp -lmosquitto
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>

class MosquittoHandler {
public:
	MosquittoHandler();
	void connect(const char *host, int port, int keepAlive);
	void cleanup();

	void takeItem();
	void startSequence();
	void reboot();
	void sendEmergency();
	void sequenceReceived();
	void available();
private:
	struct mosquitto mosq*;
	void connectCallback(struct mosquitto *mosq, void *userdata, int result);
	void messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);

	void sendMessage(const char *msg);
}
