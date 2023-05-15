//cpG8iS_NVfCk1HTv7KPJ5O key

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TskoliVESM";  // Enter SSID here
const char* password = "Fallegurhestur";  //Enter Password here

//Your Domain name with URL path or IP address with path
String serverName = "http://maker.ifttt.com/trigger/button_pressed/with/key/cpG8iS_NVfCk1HTv7KPJ5O";
// Pin connected to the button



const int buttonPin = 25;

// Variable to store the button state
int buttonState = 0;

void setup() {
  
  pinMode(buttonPin, INPUT);

  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(buttonPin, INPUT);
 
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed
  if (buttonState == HIGH) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "?temperature=24.37";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    delay(200);  // Add a small delay to debounce the button
  }
}