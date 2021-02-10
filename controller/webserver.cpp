#ifndef WEBSERVER
#define WEBSERVER

#include "credentials.hpp"
#include "webContent.hpp"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

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

void web_setup(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

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
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void web_loop(void) {
  server.handleClient();
  MDNS.update();
}

#endif
