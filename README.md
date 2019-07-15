## Description
RPM Rev lights using Adruino and WS2812 LED Strip.

Games can send telemetry data via UDP Ports. Nodejs server extracts the details such as idleRPM, currentRPM and maxRPM from the UDP Packets and sends the count of the LEDs to be lighted via Serial Port. Adruino receives the LED count and lights up the LEDS accordingly.

![Rpm Rev](https://github.com/Rajavn6789/adruino-rpm-rev-lights/blob/master/assets/rpm_rev_lights.gif)


### Steps
1. Clone the Repo
```
git clone repo_url
```

2. Replace .env file with the udp server and port
```
GAME_UDP_SERVER_IP='192.168.1.5'
GAME_UDP_SERVER_PORT=20777
ADRUINO_SERIAL_PORT='/dev/cu.usbmodem1421'
```

3. Install dependecies
```
npm install
```

4. Start the node server
```
npm start
```

### Hardware Required
1. Adruino
2. WS2812 LED Strip (x2)

### Supported Games
1. Dirt Rally (v1)
2. F1 2017

### References
1. [Fast Led](http://fastled.io/)
2. [MAKE ARDUINO RGB REV LIGHTS w SIMHUB](https://www.youtube.com/watch?v=u5kZjg_sJdg)
