#include <SoftwareSerial.h>

// Pin Configuration:
// Uno Pin 10 (Soft RX) <--- Direct Wire <--- HC-05 TXD
// Uno Pin 9  (Soft TX) ---> 1k/2k Divider ---> HC-05 RXD
SoftwareSerial btSerial(10, 9);

// Target LED connected to Pin 11 (PWM-capable)
const int LED_PIN = 11;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Hardware serial for optional USB monitoring
  Serial.begin(9600);
  
  // HC-05 communication baud rate
  btSerial.begin(9600);

  Serial.println(F("[SYSTEM] Arduino ready. LED on Pin 11."));
}

void loop() {
  // Listen for wireless commands from the web controller
  if (btSerial.available()) {
    char cmd = btSerial.read();

    if (cmd == '1') {
      digitalWrite(LED_PIN, HIGH);
      Serial.println(F("[BT] LED ON"));
    } 
    else if (cmd == '0') {
      digitalWrite(LED_PIN, LOW);
      Serial.println(F("[BT] LED OFF"));
    }
  }

  // Optional pass-through from USB Serial Monitor
  if (Serial.available()) {
    char usbCmd = Serial.read();
    if (usbCmd == '1') {
      digitalWrite(LED_PIN, HIGH);
    } else if (usbCmd == '0') {
      digitalWrite(LED_PIN, LOW);
    }
  }
}