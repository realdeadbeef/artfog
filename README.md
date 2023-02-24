# artfog
Artfog is a artnet receiver that can turn on/off a fog machine using a relay.

## Parts
- Arduino Uno (But can probably work with any ethernet board)
- 5V relay

## How the code works
It listens for its address value to be above a certain threshold, it will then let power through a relay. It will then timeout after 15 seconds.
If it does not recieve any artnet packets in 3 seconds, it will also turn off the smoke machine (stopping power through the relay). These timeouts are
so as to stop the smoke machine from just letting out smoke infinitly.  
These timeouts, as well as the IP address, DMX universe & DMX address can all be configured with the consts in the top of the file

## Contributing
There's not a whole lot to contribute but your welcome to submit PRs.
