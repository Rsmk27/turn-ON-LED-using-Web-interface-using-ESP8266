/**
 * ESP8266 Firmware for Firebase LED Control
 * 
 * Hardware:
 *  - NodeMCU / Wemos D1 Mini (ESP8266)
 *  - LED connected to Pin D4 (Built-in LED on many boards) or D1/D2.
 *    Note: Built-in LED is often active LOW (LOW=ON, HIGH=OFF).
 *          External LED is usually active HIGH.
 * 
 * Libraries Required:
 *  - FirebaseESP8266 (by Mobizt)
 *  - ESP8266WiFi
 */

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// ---------------------------------------------------------------------------
// CONFIGURATION
// ---------------------------------------------------------------------------

// 1. WiFi Credentials
#define WIFI_SSID "rsmk"
#define WIFI_PASSWORD "rsmk2005"

// 2. Firebase Credentials
#define API_KEY "FIREBASE-API"
#define DATABASE_URL "DATABASE-URL"

// 3. Hardware Settings
const int LED_PIN = 5; // Built-in LED is usually D4 (GPIO2)
                        // Change to another pin if using external LED

// ---------------------------------------------------------------------------
// GLOBALS
// ---------------------------------------------------------------------------

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

bool ledState = false;

// ---------------------------------------------------------------------------
// SETUP
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start OFF

  Serial.println("\n\nStarting...");

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  // Configure Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  
  // Sign up anonymously implementation can be tricky, so we rely on 
  // "Test Mode" (open rules) or set Legacy Token if supported.
  // For Mobizt library v4+, we can just set the signer.
  
  // NOTE: If using "Database Secrets" (Legacy), set:
  // config.signer.tokens.legacy_token = "YOUR_DATABASE_SECRET";
  
  // For this example, we assume open rules or anon auth helper.
  // We'll trust the config.api_key handles the handshake for public/test databases.
  
  config.signer.test_mode = true; // Provides a quick way to patch auth for testing

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  // Optional: Set stream to listen for changes immediately (more advanced)
  // For simplicity, we will poll in the loop or use stream.
  
  if (!Firebase.beginStream(firebaseData, "/led_status")) {
      Serial.println("Could not begin stream");
      Serial.println("REASON: " + firebaseData.errorReason());
  }
}

// ---------------------------------------------------------------------------
// LOOP
// ---------------------------------------------------------------------------
void loop() {
  
  if (!Firebase.readStream(firebaseData)) {
    Serial.println("Stream read error");
    Serial.println("REASON: " + firebaseData.errorReason());
  } else {
    // Check if stream has data
    if (firebaseData.streamTimeout()) {
      Serial.println("Stream timeout, resume...");
    }

    if (firebaseData.dataType() == "boolean") {
      ledState = firebaseData.boolData();
      Serial.print("Stream Data: ");
      Serial.println(ledState ? "ON" : "OFF");

      digitalWrite(LED_PIN, ledState); 
    }
  }

  // Keep alive / fallback polling if stream fails? 
  // For basic example, stream is best.
}

