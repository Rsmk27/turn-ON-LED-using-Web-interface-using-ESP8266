# ESP8266 Global LED Control

This project allows you to control an LED connected to your ESP8266 from anywhere in the world using a simple web page, powered by Firebase.

## Prerequisites
1.  **ESP8266 Board** (NodeMCU, Wemos D1 Mini, etc.)
2.  **Arduino IDE** installed.
3.  **Google Account** for Firebase.

## Step 1: Firebase Setup
1.  Go to [Firebase Console](https://console.firebase.google.com/).
2.  Click **Add project** -> Give it a name (e.g., `led-controller`).
3.  Once created, go to **Build** -> **Realtime Database**.
4.  Click **Create Database**. Select a location (e.g., US) and choose **Test mode** (allows read/write for 30 days, easiest for starting).
5.  Go to **Project Settings** (Gear icon) -> **General** -> scroll down to "Your apps".
6.  Click the web icon `</>` to register a web app.
7.  Copy the `firebaseConfig` object (apiKey, databaseURL, etc.).

## Step 2: Configure Web App
1.  Open `web/index.html` in a text editor (VS Code, Notepad, etc.).
2.  Find the `firebaseConfig` section.
3.  Paste your credentials from Step 1.

## Step 3: Configure Firmware
1.  Open `firmware/firmware.ino` in Arduino IDE.
2.  Install the **FirebaseESP8266** library by Mobizt (via Sketch -> Include Library -> Manage Libraries).
3.  Update the following lines with your details:
    ```cpp
    #define WIFI_SSID "YOUR_WIFI_SSID"
    #define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
    #define API_KEY "YOUR_API_KEY_FROM_FIREBASE"
    #define DATABASE_URL "YOUR_DATABASE_URL" // e.g., https://xyz.firebaseio.com
    ```

## Step 4: Run
1.  **Flash** the code to your ESP8266.
2.  Open Serial Monitor (115200 baud) to see connection status.
3.  Open `web/index.html` in any web browser (Chrome, Edge on phone or PC).
4.  Click **Turn ON** / **Turn OFF**. The LED on the board should react!
