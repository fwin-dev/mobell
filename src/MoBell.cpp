#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "INdigital Guest";
const char *password = "2604692010";

String strQueue = "";

MDNSResponder mdns;
ESP8266WebServer server ( 80 );
void handleRegBus() {
  String strOut = "<html><head><title>MoBell</title></head>";
  for (uint8_t i=0; i<server.args(); i++){
    if(server.argName(i) == "dev_id"){
      strQueue = server.arg(i);
    }
  }
  strOut += "</body></html>";

  server.send ( 200, "text/html", strOut );
}
void handleDeRegBus() {}
void handlePollBus() {
  String strOut = "<html><head><title>MoBell</title></head>";
  strOut += "<H1>" + strQueue + "</H1>";
  strOut += "</body></html>";

  server.send ( 200, "text/html", strOut );
}

void handleRoot() {
    //digitalWrite ( led, 1 );
  String strOut = "<html><head><title>MoBell Status</title></head>";
  strOut += "<body style='background-color:gray'>";
  strOut += "<H1>" + server.uri() + server.args() + "</H1>";
  strOut += "</body></html>";

  server.send ( 200, "text/html", strOut );
}
void handleNotFound() {
    //digitalWrite ( led, 1 );
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
        message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
    }
    server.send ( 404, "text/plain", message );
    //digitalWrite ( led, 0 );
}
void setup() {
  Serial.begin ( 115200 );
    WiFi.begin ( ssid, password );
    Serial.println ( "" );
    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 500 );
        Serial.print ( "." );
    }
    Serial.println ( "" );
    Serial.print ( "Connected to " );
    Serial.println ( ssid );
    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );

    //if ( mdns.begin ( "mobell", WiFi.localIP() ) ) {
    if ( mdns.begin ( "mobell" ) ) {
        Serial.println ( "MDNS responder started" );
    }
    mdns.addService("boip", "tcp", 80);
    server.on ( "/", []() {handleRoot();} );
    server.on ( "/reg", []() {handleRegBus();} );
    server.on ( "/dereg", []() {handleDeRegBus();} );
    server.on ( "/poll", []() {handlePollBus();} );
    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );
}

void loop() {
  mdns.update();
  server.handleClient();
}
