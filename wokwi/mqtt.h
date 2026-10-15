#ifndef _MQTT_H
#define _MQTT_H

#include <ArduinoJson.h>

void reconnect_to_mqtt(PubSubClient* client) {
  // Loop until we're reconnected
  while (!client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client->connect(MQTT_CLIENT_NAME)) {
      Serial.println("connected");
      // Subscribe
      client->subscribe(MQTT_TOPIC, 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}

void handle_mqtt_message(char* topic, byte* message, unsigned int length) {
  JsonDocument doc;
  deserializeJson(doc, message);

  const char* cmd = doc["command"];
  Serial.print("Received command: ");
  Serial.println(cmd);

  if (strcmp(cmd, "SET") == 0) {
    size_t duration = doc["duration"];
    timer_set(duration * 1000);
  } else if (strcmp(cmd, "START") == 0) {
    timer_start();
  } else if (strcmp(cmd, "STOP") == 0) {
    timer_stop();
  } else if (strcmp(cmd, "RESUME") == 0) {
    timer_start();
  } else {
    Serial.println("Command unknown");
  }
}

#endif // _MQTT_H