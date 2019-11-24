#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "awesomo-3000";
const char* password = "12345678";

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  String msg = "hello from ESP8266!\n\n";
  msg += "Instructions:\n";
  msg += "/w -> Write a value to the RDAC of a Digipot. [POST]\n";
  msg += "/r -> Read the RDAC res. value of a Digipot. [GET]\n";
  msg += "/s -> Store the RDAC res. value to memory. [POST]\n";
  msg += "/sr -> Reset the Digipot to the stored RDAC res. value. [POST]\n\n\n\n";
  msg += "After [GET] command letter add `?`, the position number of digipot you want to interact.\n";
  msg += "e.g. /r?2       -> read the resistance value of Digipot in position 2.\n\n\n";
  msg += "After [POST] command letter add as request body a string with 1st digit the \nposition of Digipot and next the value you want to write to RDAC.\n";
  msg += "e.g. /w & req body: `124000` -> write to digipot in pos 1 the \nresistance value 24000 ohm.";
  
  server.send(200, "text/plain", msg);
  digitalWrite(led, 0);
}

void handleWrite() {
  digitalWrite(led, 1);
  String cmd = "Write to Digipot\n\n";
  cmd += "URI: ";
  cmd += server.uri();
  cmd += "\nArguments: ";
  cmd += server.args();
  cmd += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    cmd += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.arg(i));
  }
  server.send(200, "text/plain", cmd);
  digitalWrite(led, 0);
}

void handleRead() {
  digitalWrite(led, 1);
  String cmd = "Read Digipot\n\n";
  cmd += "URI: ";
  cmd += server.uri();
  cmd += "\nArguments: ";
  cmd += server.args();
  cmd += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    cmd += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.arg(i));
  }
  server.send(200, "text/plain", cmd);
  digitalWrite(led, 0);
}

void handleStore() {
  digitalWrite(led, 1);
  String cmd = "Read Digipot\n\n";
  cmd += "URI: ";
  cmd += server.uri();
  cmd += "\nArguments: ";
  cmd += server.args();
  cmd += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    cmd += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.arg(i));
  }
  server.send(200, "text/plain", cmd);
  digitalWrite(led, 0);
}

void handleReset() {
  digitalWrite(led, 1);
  String cmd = "Read Digipot\n\n";
  cmd += "URI: ";
  cmd += server.uri();
  cmd += "\nArguments: ";
  cmd += server.args();
  cmd += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    cmd += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.arg(i));
  }
  server.send(200, "text/plain", cmd);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String msg = "You tried to type something forbidden try again reading the instructions.\n\n";
  msg += "URI: ";
  msg += server.uri();
  msg += "\nArguments: ";
  msg += server.args();
  msg += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    msg += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
  server.send(404, "text/plain", msg);
  digitalWrite(led, 0);
}

void setup() {
  delay(1000);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600);

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/w", HTTP_POST, handleWrite);
  server.on("/r", HTTP_GET, handleRead);
  server.on("/s", HTTP_POST, handleStore);
  server.on("/sr", HTTP_POST, handleReset);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("AP started");
}

void loop() {
  server.handleClient();
}