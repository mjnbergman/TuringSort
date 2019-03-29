#include "MosquittoHandler.hh"

MosquittoHandler::MosquittoHandler(const char *host, int port, int keepAlive) {
	this.host = host;
	this.port = port;
	this.keepAlive = keepAlive;

	mosquitto_lib_init();
	this.mosq = mosquitto_new(NULL, true, NULL);

	if (!mosq) {
		fprintf(stderr, "mosquitto failed to initialise.");
	}
	mosquitto_connect_callback_set(mosq, MosquittoHandler::connectCallback);
	mosquitto_message_callback_set(mosq, MosquittoHandler::messageCallback);
}

void MosquittoHandler::takeItem() {}
void MosquittoHandler::startSequence() {}
void MosquittoHandler::reboot() {}
void MosquittoHandler::sendEmergency() {}
void MosquittoHandler::sequenceReceived() {}
void MosquittoHandler::available() {}

void MosquittoHandler::connectCallback(struct mosquitto *mosq, void *userdata, int result) {
	if (!result) {
		mosquitto_subscribe(mosq, NULL, "Bot2_R");
	} else {
		fprintf(stderr, "Connection failed.\n");
	}
}

void MosquittoHandler::messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	if (message->payloadlen) {
		printf("%s %s\n", message->topic, message->payload);
	} else {
		printf("%s (null)\n", message->topic);
	}
}
