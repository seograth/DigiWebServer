#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "awesomo-3000";
const char* password = "12345678";

ESP8266WebServer server(80);

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}

void handleRoot() {
  String msg = "hello from ESP8266!\n\n";
  msg += "Instructions:\n";
  msg += "/w -> Write a value to the RDAC of a Digipot. [POST]\n";
  msg += "/r -> Read the RDAC res. value of a Digipot. [GET]\n";
  msg += "/s -> Store the RDAC res. value to memory. [POST]\n";
  msg += "/q -> Reset the Digipot to the stored RDAC res. value. [POST]\n";
  msg += "/f -> Change the functionality of the operational amplifier. [POST]\n\n\n\n";
  msg += "After [GET] command letter add `?`, the position number of digipot you want to interact.\n";
  msg += "e.g. /r?2       -> read the resistance value of Digipot in position 2.\n\n\n";
  msg += "After [POST] command letter add as request body a string with 1st digit the \nposition of Digipot and next the value you want to write to RDAC.\n";
  msg += "e.g. /w & req body: `w 1 24000` -> write to digipot in pos 1 the \nresistance value 24000 ohm.";
  
  server.send(200, "text/plain", msg);
}

void handleWrite() {
  String res = "Write to Digipot\n\n";
  String cmd = "";
  res += "URI: ";
  res += server.uri();
  cmd += server.uri();
  res += "\nArguments: ";
  res += server.args();
  res += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    res += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    cmd += server.arg(i);
    // Serial.println(server.arg(i));
  }
  writeString(cmd);
  server.send(200, "text/plain", res);
}

void handleRead() {
  String res = "Read Digipot\n\n";
  String cmd = "";
  res += "URI: ";
  res += server.uri();
  cmd += server.uri();
  res += "\nArguments: ";
  res += server.args();
  res += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    res += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    cmd += server.arg(i);
    // Serial.println(server.arg(i));
  }
  writeString(cmd);
  //TODO kane kati me to diavasma
  server.send(200, "text/plain", res);
}

void handleStore() {
  String res = "Read Digipot\n\n";
  String cmd = "";
  res += "URI: ";
  res += server.uri();
  cmd += server.uri();
  res += "\nArguments: ";
  res += server.args();
  res += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    res += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    cmd += server.arg(i);
    // Serial.println(server.arg(i));
  }
  writeString(cmd);
  server.send(200, "text/plain", res);
}

void handleReset() {
  String res = "Read Digipot\n\n";
  String cmd = "";
  res += "URI: ";
  res += server.uri();
  cmd += server.uri();
  res += "\nArguments: ";
  res += server.args();
  res += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    res += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    cmd += server.arg(i);
    // Serial.println(server.arg(i));
  }
  writeString(cmd);
  server.send(200, "text/plain", res);
}

void handleFunction() {
  String res = "Modify the functionality of op-amp:\n\n";
  String cmd = "";
  res += "URI: ";
  res += server.uri();
  cmd += server.uri();
  res += "\nArguments: ";
  res += server.args();
  res += "\n";
  for(uint8_t i=0; i < server.args(); i++) {
    res += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    cmd += server.arg(i);
    // Serial.println(server.arg(i));
  }
  writeString(cmd);
  server.send(200, "text/plain", res);
}

void handleNotFound() {
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
}

void setup() {
  delay(1000);
  Serial.begin(9600);

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/w", HTTP_POST, handleWrite);
  server.on("/r", HTTP_GET, handleRead);
  server.on("/s", HTTP_POST, handleStore);
  server.on("/q", HTTP_POST, handleReset);
  server.on("/f", HTTP_POST, handleFunction);

  server.onNotFound(handleNotFound);

  server.begin();
  // Serial.println("AP started");
}

void loop() {
  server.handleClient();
}