const dgram = require('dgram');
const SerialPort = require("serialport");
const dotenv = require('dotenv');

// Intialize dotenv
dotenv.config();

// 1. Initialize a Serial connection with adruino serial port
const arduinoCOMPort = process.env.ADRUINO_SERIAL_PORT || 'COM1';
const arduinoSerialPort = new SerialPort(arduinoCOMPort, {
  baudRate: 9600,
});

arduinoSerialPort.on("open", () => {
  console.log('Serial Port ' + arduinoCOMPort + ' is opened.');
});

arduinoSerialPort.on('close', () => {
  console.log('Serial Port ' + arduinoCOMPort + ' is closed.');
});

arduinoSerialPort.on('error', (err) => {
  console.log('Error occured in Serial Port ' + err.message);
});

// 2. Initialize a UDP server listening to port 20777
const udpServer = dgram.createSocket('udp4');
udpServer.bind({
  address: process.env.GAME_UDP_SERVER_IP || '127.0.0.1',
  port: process.env.GAME_UDP_SERVER_PORT || 20777,
});

udpServer.on('listening', () => {
  const address = udpServer.address();
  console.log(`server listening ${address.address}:${address.port}`);
});

udpServer.on('message', function(buffer, rinfo) {
    // Read data from the game telemetry UDP Packets
    const engineRPM = Math.round(buffer.readFloatLE(148));
    const maxRPM = Math.round(buffer.readFloatLE(252));
    const idleRPM = Math.round(buffer.readFloatLE(256));

    // Calculate Percentage of RPM and no of LEDS to be lightened
    const percentageRPM = Math.floor(((engineRPM - idleRPM) / (maxRPM - idleRPM)) * 100);
    const numLeds = Math.ceil(percentageRPM / 6.25);

    // Send to Adruino
    arduinoSerialPort.write(`${numLeds.toString()}\n`);
});

udpServer.on('error', (err) => {
  console.log(`server error:\n${err.stack}`);
  udpServer.close();
});
