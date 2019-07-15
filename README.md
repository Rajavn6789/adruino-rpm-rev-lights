## Description
RPM Rev lights using Adruino and WS2812 LED Strip.

Games can send telemetry data via UDP Ports. Nodejs server extracts the details such as idleRPM, currentRPM and maxRPM from the UDP Packets and sends the count of the LEDs to be lighted via Serial Port. Adruino receives the LED count and lights up the LEDS accordingly.

![Rpm Rev](https://github.com/Rajavn6789/adruino-rpm-rev-lights/blob/master/assets/rpm_rev_lights.gif)

### Hardware Required
1. Adruino
2. WS2812 LED Strip (x2)

### Steps

1. Solder the WS2812 LED Strip together and connect it to Adruino
    ```
    DIN - D7 of Adruino
    5V - 5V OF Adruino
    GND (x2) - Any GND Pin in Adruino
    ```
    > WS2812 LED Strip can be connected in chain.
    > If using more than two use external 5v power supply or you will end up in frying the adruino.

2. Upload the sketch inside adruino folder to the AdruinoIDE and flash the sketch into the adruino
    > Install FastLED library before flashing

3. Clone the Repo
    ```sh
    $ git clone https://github.com/Rajavn6789/adruino-rpm-rev-lights.git
   ```

3. Replace .env file with the udp server, port
    ```
    GAME_UDP_SERVER_IP='127.0.0.1'
    GAME_UDP_SERVER_PORT=20777
    ADRUINO_SERIAL_PORT='COM6'
    ```

4. Install dependecies
    ```sh
    $ npm install
    ```

5. Start the node server
    ```sh
    $ npm start
    ```

### Supported Games
1. Dirt Rally (v1)
2. F1 2017

### References
1. [Fast Led](http://fastled.io/)
2. [MAKE ARDUINO RGB REV LIGHTS w SIMHUB](https://www.youtube.com/watch?v=u5kZjg_sJdg)
