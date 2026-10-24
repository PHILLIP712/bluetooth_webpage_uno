#include <SoftwareSerial.h>

// SoftwareSerial Pin Configuration:
// Uno Pin 10 (RX) <--- HC-05 TXD
// Uno Pin 9  (TX) ---> Voltage Divider (1k/2k) ---> HC-05 RXD
SoftwareSerial btSerial(10, 9);

// LED moved to Pin 11 (PWM capable)
const int LED_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Hardware serial for USB debugging
  Serial.begin(9600);
  // Default communication baud rate for HC-05
  btSerial.begin(9600);

  Serial.println(F("[SYSTEM] System ready."));
  Serial.println(F("[CONFIG] HC-05 TX: D9, RX: D10 | LED: D11"));
}

void loop() {
  // Listen for commands from the Web interface / Bluetooth link
  if (btSerial.available()) {
    char cmd = btSerial.read();

    if (cmd == '1') {
      digitalWrite(LED_PIN, HIGH);
      btSerial.println(F("STATUS: LED ON (Pin 11)"));
      Serial.println(F("[BT] Command: 1 -> Pin 11 HIGH"));
    } 
    else if (cmd == '0') {
      digitalWrite(LED_PIN, LOW);
      btSerial.println(F("STATUS: LED OFF (Pin 11)"));
      Serial.println(F("[BT] Command: 0 -> Pin 11 LOW"));
    }
  }

  // Passthrough from PC USB Serial Monitor to Bluetooth
  if (Serial.available()) {
    btSerial.write(Serial.read());
  }
}