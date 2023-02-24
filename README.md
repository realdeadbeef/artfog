# artfog
Artfog is an arduino based artnet receiver that can turn on/off a fog machine using a relay.

## Parts
- Arduino Uno
- Arduino Ethernet Shield
- 5V relay

## How the code works
It listens for a DMX address' value to be above a certain threshold, it will then switch on a relay. It will then timeout after 15 seconds as a failsafe.
If it does not recieve any artnet packets in 3 seconds, it will also turn off the smoke machine (switching off the relay). These timeouts are
so as to stop the smoke machine from just letting out smoke infinitly.  
These timeouts, as well as the IP address, DMX universe & DMX address can all be configured with the variables in the top of the file.

## Wiring

Arduino GND > Relay GND  
Arduino 5V > Relay VCC  
Arduino Pin D7 > Relay Signal Pin

## Contributing
There's not a whole lot to contribute but you're welcome to submit PRs.
