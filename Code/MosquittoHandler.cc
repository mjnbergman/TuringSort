	#include "MosquittoHandler.hh"

MosquittoHandler::MosquittoHandler() {
	mosquitto_lib_init();
	this.mosq = mosquitto_new(NULL, true, NULL);

	if (!mosq) {
		fprintf(stderr, "mosquitto failed to initialise.\n");
	}
	mosquitto_connect_callback_set(mosq, MosquittoHandler::connectCallback);
	mosquitto_message_callback_set(mosq, MosquittoHandler::messageCallback);
}

void MosquittoHandler::cleanup() {
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}

void MosquittoHandler::connect(const char *host, int port, int keepAlive) {
	if (mosquitto_connect(mosq, host, port, keepAlive)) {
		fprintf(stderr, "MQTT connection failed.\n");
	}
}

void MosquittoHandler::takeItem() {}
void MosquittoHandler::startSequence() {}
void MosquittoHandler::reboot() {}
void MosquittoHandler::sendEmergency() {
	MosquittoHandler::sendMessage("emergency");
}
void MosquittoHandler::sequenceReceived() {
	MosquittoHandler::sendMessage("sequenceReceived");
}
void MosquittoHandler::available() {
	MosquittoHandler::sendMessage("available");
}

void MosquittoHandler::connectCallback(struct mosquitto *mosq, void *userdata, int result) {
	if (!result) {
		mosquitto_subscribe(mosq, NULL, "Bot2_R");
	} else {
		fprintf(stderr, "MQTT connection failed.\n");
	}
}

void MosquittoHandler::messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	if (message->payloadlen) {
		switch (message->payload) {
			case "takeItem": MosquittoHandler::takeItem();
			case "startSequence": MosquittoHandler::startSequence();
			case "reboot": MosquittoHandler::reboot();
			default: fprintf(stderr, "No valid function for signal\n");
		}
		fprintf(stdout, "Message received over MQTT: %s %s\n", message->topic, message->payload);
	} else {
		printf("%s (null)\n", message->topic);
	}
}

void MosquittoHandler::sendMessage(const char *msg) {
	mosquitto_publish(mosq, NULL, "Bot2_T", strlen(msg), msg, 0, false);

	fprintf(stdout, "Message sent over MQTT: %s\n", msg);
}
