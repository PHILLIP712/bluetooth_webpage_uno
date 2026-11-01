#include <SoftwareSerial.h>

// RX = Pin 2 (HC-05 TXD), TX = Pin 3 (HC-05 RXD via divider)
SoftwareSerial bt(2, 3);

const int LED_PIN = 11; // Ensure external LED or onboard Pin 13 is set correctly

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Enable internal pull-up on SoftwareSerial RX to stop floating noise
  pinMode(2, INPUT_PULLUP);

  Serial.begin(9600);
  bt.begin(9600);

  Serial.println(F("[SYSTEM] Filtered Controller Ready."));
}

void loop() {
  if (bt.available()) {
    char c = bt.read();

    // Ignore newlines, carriage returns, spaces, and non-printable noise
    if (c == '\r' || c == '\n' || c == ' ' || (uint8_t)c > 127) {
      return;
    }

    if (c == '1') {
      digitalWrite(LED_PIN, HIGH);
      bt.println(F("LED: ON"));
      Serial.println(F(">>> LED ON"));
    } 
    else if (c == '0') {
      digitalWrite(LED_PIN, LOW);
      bt.println(F("LED: OFF"));
      Serial.println(F(">>> LED OFF"));
    }
  }
}