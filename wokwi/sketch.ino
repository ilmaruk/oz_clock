#include "config.h"
#include "secrets.h"
#include "timer.h"

#include <MD_Parola.h>

// #include <Arduino.h>
#include <PubSubClient.h>

char szMesg[10] = "BOOT...";

#include "wifi.h"
#include "mqtt.h"
#include "clock.h"
#include "clock_font.h"

WiFiClient espClient;
PubSubClient client(espClient);

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup()
{
  // Serial setup
  Serial.begin(115200);

  // set notification call-back function
  // sntp_set_time_sync_notification_cb(time_available);

  /**
   * NTP server address could be aquired via DHCP,
   *
   * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
   * otherwise SNTP option 42 would be rejected by default.
   * NOTE: configTime() function call if made AFTER DHCP-client run
   * will OVERRIDE aquired NTP server address
   */
  // sntp_servermode_dhcp(1);    // (optional)

  /**
   * This will set configured ntp servers and constant TimeZone/daylightOffset
   * should be OK if your time zone does not need to adjust daylightOffset twice a year,
   * in such a case time adjustment won't be handled automagicaly.
   */
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  configTzTime(time_zone, ntpServer1);

  // WiFi setup
  WiFi.mode(WIFI_STA);

  // MQTT setup
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(handle_mqtt_message);

  // Display setop
  display.begin();
  display.setFont(oz_score);
  display.displayText(szMesg, PA_CENTER, 0, 0, PA_NO_EFFECT, PA_NO_EFFECT);
}

void loop()
{
  connectToWiFi(wifi_ssid, wifi_password);

  if (!client.connected()) {
    reconnect_to_mqtt(&client);
  }
  client.loop();

  if (display.displayAnimate()) {
    if (timer_status() != TIMER_STOPPED) {
      timer_format(szMesg);
    } else {
      clock_format(szMesg);
    }
    display.displayText(szMesg, PA_CENTER, 0, 0, PA_NO_EFFECT, PA_NO_EFFECT);
  }

  delay(50);
}
