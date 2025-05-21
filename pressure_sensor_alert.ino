// Blynk IoT Credentials - Replace these with your own
#define BLYNK_TEMPLATE_ID "TMPL3vlVXG4_6"
#define BLYNK_TEMPLATE_NAME "Pressure Sensor"
#define BLYNK_AUTH_TOKEN "91tihDZOZ2lXu_zPP6Iu_4dsNN0Jsuui"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi credentials
char ssid[] = "Test";
char pass[] = "Test12345";

// Pin definitions
int pressurePin = 34;     // Analog input pin connected to pressure sensor
int ledPin = 2;           // GPIO 2 connected to built-in or external LED

// Variables
float smoothedValue = 0;         // Stores smoothed pressure value
BlynkTimer timer;                // Blynk timer to schedule data sending
bool notificationSent = false;  // Flag to prevent repeated notifications

// Function to read and send pressure data
void sendPressure() {
  int rawValue = analogRead(pressurePin);  // Read analog value from sensor
  smoothedValue = smoothedValue * 0.9 + rawValue * 0.1;  // Apply exponential smoothing

  int valueToSend = (int)smoothedValue;
  Blynk.virtualWrite(V0, valueToSend);  // Send data to Blynk app (Virtual Pin V0)

  Serial.print("Raw: "); 
  Serial.print(rawValue);
  Serial.print(" | Smoothed: ");
  Serial.println(valueToSend);

  // Trigger emergency alert if pressure crosses threshold
  if (valueToSend > 1000 && !notificationSent) {
    Blynk.logEvent("warning", "There is an emergency at location 30.692489631980408, 76.83861496051063");
    digitalWrite(ledPin, HIGH);  // Turn LED ON
    notificationSent = true;     // Set flag to avoid repeat notifications
  }

  // Reset notification and turn off LED if pressure drops
  if (valueToSend <= 1000) {
    digitalWrite(ledPin, LOW);   // Turn LED OFF
    notificationSent = false;    // Reset flag
  }
}

void setup() {
  Serial.begin(115200);           // Start Serial Monitor
  pinMode(ledPin, OUTPUT);        // Set LED pin as output
  digitalWrite(ledPin, LOW);      // Ensure LED is OFF at start

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Connect to Wi-Fi and Blynk
  timer.setInterval(1000L, sendPressure);     // Call sendPressure every 1 second
}

void loop() {
  Blynk.run();  // Keep Blynk connection alive
  timer.run();  // Run Blynk timer
}
