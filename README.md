## Description
RPM Rev lights using Adruino and WS2812 LED Strip.

Games can send telemetry data via UDP Ports. Nodejs Server extracts the details such as idleRPM, currentRPM and maxRPM from the UDP Packets and sends the count of the LEDs to be lighted via Serial Port. Adruino receives the LED count and lights up the LEDS.

![Rpm Rev](https://github.com/Rajavn6789/adruino-rpm-rev-lights/blob/master/assets/rpm_rev_lights.gif)

#### Hardware Required
1. Adruino
2. WS2812 LED Strip (x2)

#### Supported Games
1. Dirt Rally (v1)
2. F1 2017

#### References
1. [Fast Led](http://fastled.io/)
2. [MAKE ARDUINO RGB REV LIGHTS w SIMHUB](https://www.youtube.com/watch?v=u5kZjg_sJdg)
