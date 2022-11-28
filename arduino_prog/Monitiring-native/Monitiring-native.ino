
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#define DHT11_PIN 7
#define REQ_BUF_SZ 20

File webFile;
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0; // index into HTTP_req buffer
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 20);

EthernetServer server(80);
bool pin1;
bool pin2;
bool pin3;
bool pin4;
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  SD.begin(4);
  Ethernet.begin(mac, ip);
  server.begin();
  pin1 = pin2 = pin3 = pin4 = 0;
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (req_index < (REQ_BUF_SZ - 1)) {
          HTTP_req[req_index] = c; // save HTTP request character
          req_index++;
        }
        if (c == '\n' && currentLineIsBlank) {
          if (StrContains(HTTP_req, "GET / ") || StrContains(HTTP_req, "GET /index.htm")) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
            webFile = SD.open("index.htm");
          } else if (StrContains(HTTP_req, "GET /favicon.ico")) {
            webFile = SD.open("favicon.ico");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /temp.png")) {
            webFile = SD.open("temp.png");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /humid.png")) {
            webFile = SD.open("humid.png");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /flame.png")) {
            webFile = SD.open("flame.png");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /my.css")) {
            webFile = SD.open("my.css");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } /*else if (StrContains(HTTP_req, "ajax_flame")) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: keep-alive");
            client.println();
            int smoke_gas = 0; //пин на котором подключен MQ-2
            int sensorReading = analogRead(smoke_gas);
            int chk;
            chk = DHT.read(DHT11_PIN);
            client.print(sensorReading);
            client.print(":");
            client.print(DHT.temperature);
            client.print(":");
            client.print(DHT.humidity);
            client.print(":");
            client.print((digitalRead(2)) ? "1" : "0");
            client.print(":");
            client.print((digitalRead(3)) ? "1" : "0");
            client.print(":");
            client.print((digitalRead(5)) ? "1" : "0");
            client.print(":");
            client.print((digitalRead(6)) ? "1" : "0");

          } else if (StrContains(HTTP_req, "setpin?pin=1")) {
            pin1 = !pin1;
            digitalWrite(2, pin1);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
          } else if (StrContains(HTTP_req, "setpin?pin=2")) {
            pin2 = !pin2;
            digitalWrite(3, pin2);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
          } else if (StrContains(HTTP_req, "setpin?pin=3")) {
            pin3 = !pin3;
            digitalWrite(5, pin3);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
          } else if (StrContains(HTTP_req, "setpin?pin=4")) {
            pin4 = !pin4;
            digitalWrite(6, pin4);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
          }*/

          if (webFile) {
            while (webFile.available()) {
              client.write(webFile.read()); // send web page to client
            }
            webFile.close();
          }
          req_index = 0;
          StrClear(HTTP_req, REQ_BUF_SZ);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

void StrClear(char *str, char length)
{
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

char StrContains(char *str, char *sfind)
{
  char found = 0;
  char index = 0;
  char len;
  len = strlen(str);
  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    }
    else {
      found = 0;
    }
    index++;
  }
  return 0;
}