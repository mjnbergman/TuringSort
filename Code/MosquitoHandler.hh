/*
 * MosquitoHandler.hh
 *
 *  Created on: 1 Apr 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_MOSQUITOHANDLER_HH_
#define TURINGSORT_CODE_MOSQUITOHANDLER_HH_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>
#include "System.hh"

struct mosquitto* mqtt_mosq;
System *S;


void mqtt_setSystem(System *s) {
        S = s;
}

void mqtt_cleanup() {
        std::cout << "Stopping and cleaning up MQTT." << std::endl;
        mosquitto_loop_stop(mqtt_mosq, false);
        mosquitto_destroy(mqtt_mosq);
        mosquitto_lib_cleanup();
}

void mqtt_connect(const char *host, int port, int keepAlive) {
        if (mosquitto_connect(mqtt_mosq, host, port, keepAlive)) {
                std::cerr << "MQTT connection failed." << std::endl;
        }
}

void mqtt_loopStart() {
        mosquitto_loop_start(mqtt_mosq);
}

void mqtt_sendMessage(const char *msg) {
        mosquitto_publish(mqtt_mosq, NULL, "Bot2_T", strlen(msg), msg, 1, false);

        std::cout << "Message sent over MQTT: " << msg << std::endl;
}

void mqtt_takeItem() {
        S->port.in.takeItem();
}
void mqtt_startSequence() {
        S->port.in.startSequence();
}
void mqtt_reboot() {
        S->port.in.reboot();
}
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
                std::cout << "MQTT connected (callback)." << std::endl;
                mosquitto_subscribe(mosq, NULL, "Bot2_R", 2);
        } else {
                std::cerr << "MQTT connection failed (callback)." << std::endl;
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
                        std::cerr << "No valid function for signal " << (const char *)message->payload << std::endl;
                }
                std::cout << "Message received over MQTT" << message->topic << " " << (const char *)message->payload << std::endl;
        } else {
                std::cout << "Message received over MQTT" << message->topic << " (null)" << std::endl;
        }
}

void mqtt_subscribeCallback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos) {
        std::cout << "MQTT has subscribed." << std::endl;
}

void mqtt_init() {
        mosquitto_lib_init();
        mqtt_mosq = mosquitto_new("Bot2", true, NULL);

        if (!mqtt_mosq) {
                std::cerr << "mosquitto failed to create object." << std::endl;
        }

        mosquitto_connect_callback_set(mqtt_mosq, mqtt_connectCallback);
        mosquitto_message_callback_set(mqtt_mosq, mqtt_messageCallback);
        mosquitto_subscribe_callback_set(mqtt_mosq, mqtt_subscribeCallback);
}



#endif /* TURINGSORT_CODE_MOSQUITOHANDLER_HH_ */
