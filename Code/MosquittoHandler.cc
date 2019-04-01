//#include "MosquittoHandler.hh"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>

struct mosquitto* mqtt_mosq;

void mqtt_cleanup() {
	mosquitto_destroy(mqtt_mosq);
	mosquitto_lib_cleanup();
}

void mqtt_connect(const char *host, int port, int keepAlive) {
	if (mosquitto_connect(mqtt_mosq, host, port, keepAlive)) {
		fprintf(stderr, "MQTT connection failed.\n");
	}
}

void mqtt_sendMessage(const char *msg) {
	mosquitto_publish(mqtt_mosq, NULL, "Bot2_T", strlen(msg), msg, 2, false);

	fprintf(stdout, "Message sent over MQTT: %s\n", msg);
}

void mqtt_takeItem() {}
void mqtt_startSequence() {}
void mqtt_reboot() {}
void mqtt_sendEmergency() {
	mqtt_sendMessage("emergency");
}
void mqtt_sequenceReceived() {
	mqtt_sendMessage("sequenceReceived");
}
void mqtt_available() {
	mqtt_sendMessage("available");
}

void mqtt_connectCallback(struct mosquitto *mosq, void *userdata, int result) {
	if (!result) {
		mosquitto_subscribe(mosq, NULL, "Bot2_R", 2);
	} else {
		fprintf(stderr, "MQTT connection failed.\n");
	}
}

void mqtt_messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
	if (message->payloadlen) {
		if (strcmp((const char *)message->payload, "takeItem") == 0) {
			mqtt_takeItem();
		} else if (strcmp((const char *)message->payload, "startSequence") == 0) {
			mqtt_startSequence();
		} else if (strcmp((const char *)message->payload, "reboot") == 0) {
			mqtt_reboot();
		} else {
			fprintf(stderr, "No valid function for signal %s\n", (const char *)message->payload);
		}
		fprintf(stdout, "Message received over MQTT: %s %s\n", message->topic, (const char *)message->payload);
	} else {
		fprintf(stdout, "Message received over MQTT: %s (null)\n", message->topic);
	}
}

void mqtt_init() {
	mosquitto_lib_init();
	mqtt_mosq = mosquitto_new(NULL, true, NULL);

	if (!mqtt_mosq) {
		fprintf(stderr, "mosquitto failed to initialise.\n");
	}
	mosquitto_connect_callback_set(mqtt_mosq, mqtt_connectCallback);
	mosquitto_message_callback_set(mqtt_mosq, mqtt_messageCallback);
}
