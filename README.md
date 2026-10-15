# OZ Clock

OZ Clock is a compact Wi-Fi clock built around an ESP32 and a 4-digit MAX7219 display. It connects to the internet, syncs the current time using NTP, and shows the time on a custom LED matrix display.

The project is designed to run in the Wokwi simulator, but the code is structured so it can be adapted to real hardware with a similar ESP32 + MAX7219 setup.

## What it does

- Shows the current local time on a 4-digit display
- Uses NTP to keep the clock accurate
- Connects to Wi-Fi and MQTT
- Accepts MQTT commands to control a countdown timer
- Supports timer start, stop, resume, and set-duration actions

## Project layout

- `wokwi/` contains the Arduino sketch and supporting source files
- `wokwi/config.h` defines the display pins and MQTT broker settings
- `wokwi/clock.h` handles time formatting and NTP synchronization
- `wokwi/timer.h` implements the countdown timer logic
- `wokwi/mqtt.h` handles incoming MQTT messages and commands
- `wokwi/secrets.h` is intended for Wi-Fi credentials

## Typical use

This project is useful for a small desk clock, wall clock, or status display that can also act as a timer. It is especially suited for DIY electronics projects where you want a low-cost, internet-synced display driven by a microcontroller.

## Notes

To run it locally or in simulation, configure your Wi-Fi credentials in `wokwi/secrets.h` and open the project in Wokwi or compile it for the target board you are using.
