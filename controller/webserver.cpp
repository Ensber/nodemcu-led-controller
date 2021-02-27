#include "webserver.hpp"
#include "credentials.hpp"
#include "webContent.hpp"
#include "globals.hpp"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <math.h>

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt -= 48;
    if (nextInt >= 65 && nextInt <= 70) nextInt -= 55;
    if (nextInt >= 97 && nextInt <= 102) nextInt -= 87;
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

void handleRoot() {
  for (uint8_t i = 0; i < server.args(); i++) {
    String aName = server.argName(i);
    // if (aName == "x")
    //   goal[0] = server.arg(i).toFloat();
    // if (aName == "y")
    //   goal[1] = server.arg(i).toFloat();
    // if (aName == "brightness"){
    //   brightness = server.arg(i).toInt();
    //   blinking = 0;
    //   if (brightness>=1024){
    //     brightness = 1023;
    //   }
    // }
    // if (aName == "brightness"){
    //   blinking = server.arg(i).toInt();
    // }
  }
  //server.send(200, "text/plain",  webContent["/index.html"]); // change
}

void handleNotFound() {
  /*if (webContent(server.uri())) {
    server.send(200, mime::getContentType(server.uri()), webContent[server.uri()]);
    return;
  }*/
  std::string uri = string(server.uri().c_str());
  if (uri == "/") uri = "/index.html";
  int index = findWebContent(uri);
  if (index != -1) {
    int len = webContent[index][1].length();
    server.send(200, "text/html", webContent[index][1].c_str(), len);
    return;
  }


  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleLedSet() {
  int r,g,b = 0;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "rgb") {
      String rgb = server.arg(i);
      r = hexToDec(rgb.substring(0,2));
      g = hexToDec(rgb.substring(2,4));
      b = hexToDec(rgb.substring(4,6));
      Serial.println("R"+ r);
      Serial.println("G"+ g);
      Serial.println("B"+ b);
      // set led PWM

      analogWrite(PWM_R,r*4);
      analogWrite(PWM_G,g*4);
      analogWrite(PWM_B,b*4);

      server.send(200, "text/plain", String()+r+"-"+g+"-"+b); return;
    }
    //message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(500, "text/plain", "missing rgb parameter");
}

void web_setup() {
  pinMode(PWM_R, OUTPUT);
  pinMode(PWM_G, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("4");
  Serial.println(webContent[4][1].length());

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/api/setLed", handleLedSet);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

int counter = 0;
void web_loop() {
  server.handleClient();
  MDNS.update();
  
  counter++;
  //analogWrite(PWM_R,(int)((sin(counter/10000)+1)/2*1023));
}
