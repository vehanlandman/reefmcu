# ReefMCU
A ESP32/ESP8266 controlled system for a Coral Reef Tank

This is a little side project. I am just trying to make all the controls of my reef tank more automatic. This is mainly a place for me to keep track of updates and to hold myself accountable to do the work.

### Current features:

SmartPlug8/16 - MQTT controlled relay board can control either 8 relay board or 16 relay board. Gerber only attached for 8 relay board.
ReefMCU Sensor - Sensor that sends values over MQTT (Currently supports: Temperature, Float Switch, Photoelectric Liquid Level Sensor).
Sonoff Sump Light - Code for Sump Light with Sonoff Switch to communicate over MQTT.
Auto TopUp - (needs lots of improvement)

### Future features:

ReefMCU Sensor - Add support for Conductivity Sensor, Ph Sensor and Ion-specific Calcium Sensor (Pro version).
ReefMCU Sensor - Add gerber file with support for the following: Temperature, Float Switch, Photoelectric Liquid Level Sensor, Conductivity Sensor and Ph Sensor.
Auto TopUp - More solid code for seperate unit not connected to smart plug. ie. Includes relay control for 12V pump, Photoelectric Liquid Level Sensor and Resevoir Level Detector (float switch or ultrasonic distance sensor).
