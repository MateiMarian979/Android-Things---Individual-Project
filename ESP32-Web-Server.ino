#include <WiFi.h>

// Network credentials
const char* ssid = "ESP32-Network";
const char* password = "marian123";

// Create web server on port 80
WiFiServer server(80);

// String to store HTTP request
String header;

// Array to store LED states (false = off, true = on)
bool ledState[2] = {false, false};

// Define GPIO pins for LEDs
const int ledPins[2] = {16, 17};

// Runs once and configures the pins and starts the web server
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Initialize LED pins as outputs and set them to LOW
  for (int i = 0; i < 2; i++) {
    pinMode(ledPins[i], OUTPUT); // setting the pins as outputs (esp32 can control voltage on these pins)
    digitalWrite(ledPins[i], LOW); // the pins are turned off in the beginning 
  }
  
  // Configure ESP32 as Access Point with credentials
  WiFi.softAP(ssid, password);
  
  // Print IP address to Serial Monitor
  Serial.println("IP: " + WiFi.softAPIP().toString());
  
  // Start web server
  server.begin();
}

// Loops after setup() completes and listens for incoming web connections + process requests
void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();
  
  // If a new client connects
  if (client) {
    // Variable for timeout tracking
    unsigned long timeout = millis();
    
    // String to hold incoming data from client
    String currentLine = "";
    
    // Loop while client is connected and hasn't timed out (2 seconds)
    while (client.connected() && millis() - timeout < 2000) {
      // If data is available to read
      if (client.available()) {
        // Read a byte
        char c = client.read();
        
        // Add byte to header
        header += c;
        
        // If newline character received
        if (c == '\n') {
          // If current line is blank, it's the end of HTTP request
          if (currentLine.length() == 0) {
            // Send HTTP response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Process URL requests for LED control
            for (int i = 0; i < 2; i++) {
              int pin = ledPins[i];
              
              // Check if URL contains request to turn LED on
              if (header.indexOf("GET /" + String(pin) + "/on") >= 0) {
                ledState[i] = true;
                digitalWrite(pin, HIGH); // Turn LED on
              } 
              // Check if URL contains request to turn LED off
              else if (header.indexOf("GET /" + String(pin) + "/off") >= 0) {
                ledState[i] = false;
                digitalWrite(pin, LOW); // Turn LED off
              }
            }
            
            // Start of HTML content
            client.println("<!DOCTYPE html><html><head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            
            client.println("<style>");
            client.println("body{font-family:Arial,sans-serif;background-color:#f0f4f8;margin:0;padding:20px;color:#333}");
            client.println(".container{max-width:400px;margin:0 auto;background-color:#fff;border-radius:10px;padding:20px;box-shadow:0 4px 6px rgba(0,0,0,0.1)}");
            client.println("h1{color:#2a5298;margin-bottom:10px}");
            client.println("p{color:#666;margin-bottom:20px;font-size:18px}");
            client.println(".button-group{display:flex;flex-direction:column;gap:15px}");
            client.println(".led-label{font-weight:bold;margin-bottom:5px;text-align:left}");
            client.println(".button{background-color:#4CAF50;color:white;padding:12px;font-size:20px;cursor:pointer;border:none;border-radius:5px;transition:all 0.3s}");
            client.println(".button:hover{opacity:0.9;transform:translateY(-2px)}");
            client.println(".button2{background-color:#f44336}");
            client.println("</style></head>");
            
            client.println("<body><div class=\"container\"><h1>ESP32 Control Panel</h1><p>Manage your connected devices</p><div class=\"button-group\">");
            
            String ledNames[2] = {"First LED", "Second LED"};
            for (int i = 0; i < 2; i++) {
              int pin = ledPins[i];
              
              client.println("<div><div class=\"led-label\">" + ledNames[i] + "</div>");
              
              if (!ledState[i]) {
                // when pressing the button , we access a new url redirecting us based on the value of the button ( on / of / 16/ 17)
                client.println("<a href=\"/" + String(pin) + "/on\"><button class=\"button\">TURN ON</button></a>");
              } else {
                // Turn OFF button (red)
                client.println("<a href=\"/" + String(pin) + "/off\"><button class=\"button button2\">TURN OFF</button></a>");
              }
              client.println("</div>");
            }
            
            // Footer with version info
            client.println("</div><div style=\"margin-top:20px;font-size:12px;color:#999\">ESP32 Web Server v1.0</div></div></body></html>");
            
            // End of HTTP response
            break;
          } else {
            // Clear current line for next line of request
            currentLine = "";
          }
        } else if (c != '\r') {
          // If not carriage return, add character to current line
          currentLine += c;
        }
      }
    }
    
    // Clear the header variable for next request
    header = "";
    
    // Close the connection
    client.stop();
  }
}