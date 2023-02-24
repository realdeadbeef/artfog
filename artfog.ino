#include <ArtnetEther.h>

// Ethernet stuff
const IPAddress ip(192, 168, 8, 169);
byte mac[] = { 0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31 };

ArtnetReceiver artnet;
// Set universe
uint32_t universe = 0;  // 0 - 15
// Set DMX channel to listen for trigger
int dmxAddress = 0;

// Set trigger threshold 0 - 255
const int minValue = 204; // 80%
// Set Pin for relay
const int relayPin = 7;

const long artnetTimeout = 1000 * 3;
const long smokeTimeout = 1000 * 15;

unsigned long lastArtnet;
unsigned long lastRelay;

boolean relayActive = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Wagwan");
    
    // Shit out LAN IP
    Ethernet.begin(mac, ip);
    Serial.println(Ethernet.localIP());
    artnet.begin();
    
    // Listen for data on defined universe
    artnet.subscribe(universe, callback);
    
    // Set up relay
    pinMode(relayPin, OUTPUT);
}

void loop() {
  artnet.parse();  // check if artnet packet has come and execute callback
  
  if(millis() - lastArtnet >= artnetTimeout) {
    digitalWrite(relayPin, LOW);
  }
  Serial.println(lastRelay);
  if(millis() - lastRelay >= smokeTimeout) {
    digitalWrite(relayPin, LOW);
  }
}

void artnetCallback(const uint8_t* data, const uint16_t size) {
    // you can also use pre-defined callbacks
    if(data[dmxAddress] >= minValue) {
      if(relayActive) return;
      // Fog maccy
      Serial.println("I tried to catch some fog the other day");
      Serial.println("I mist");
      digitalWrite(relayPin, HIGH);
      lastRelay = millis();
      relayActive = true;
    } else {
      if(!relayActive) return;
      digitalWrite(relayPin, LOW);
      relayActive = false;
    }
}

void callback(const uint8_t* data, const uint16_t size) {
  lastArtnet = millis();
  debugArtnet(data, size);
  artnetCallback(data, size);
}

void debugArtnet(const uint8_t* data, const uint16_t size) {
  Serial.print("artnet data (universe : ");
  Serial.print(universe);
  Serial.print(", size = ");
  Serial.print(size);
  Serial.print(") :");
  for (size_t i = 0; i < size; ++i) {
      Serial.print(data[i]);
      Serial.print(",");
  }
  Serial.println();
  
  Serial.print("My value is ");
  Serial.print(data[dmxAddress]);
  Serial.println();
}
