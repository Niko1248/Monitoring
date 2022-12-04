
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#define REQ_BUF_SZ 20
#define FIRST_PIN 40
#define LAST_PIN 47

File webFile;
char HTTP_req[REQ_BUF_SZ] = { 0 };  // buffered HTTP request stored as null terminated string
char req_index = 0;                 // index into HTTP_req buffer
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 101);


EthernetServer server(80);

void setup() {
  for (int i = FIRST_PIN; i <= LAST_PIN; i++){    // Установил все пины в input
    pinMode(i, INPUT);
  }
  SD.begin(4);
  Ethernet.begin(mac, ip);
  server.begin();
}


void loop() {
 
  EthernetClient client = server.available();
  if (client) {
    // если сервер поднят
    boolean currentLineIsBlank = true;
    while (client.connected()) { // и мы подключились
      if (client.available()) {
        char c = client.read(); //присваиваем реквесты переменной с
        if (req_index < (REQ_BUF_SZ - 1)) {
          HTTP_req[req_index] = c;  // читаем посимвольно запрос
          req_index++;
        }
        if (c == '\n' && currentLineIsBlank) { // если символы в запросе кончились то
          if (StrContains(HTTP_req, "GET / ") || StrContains(HTTP_req, "GET /index.htm")) {// содердит ли реквест GET /index.htm ?
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
          } else if (StrContains(HTTP_req, "GET /close.png")) {
            webFile = SD.open("close.png");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /sis.xml")) {
            webFile = SD.open("sis.xml");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /style.css")) {
            webFile = SD.open("style.css");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /R_EL.ttf")) {
            webFile = SD.open("R_EL.ttf");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /R_L.ttf")) {
            webFile = SD.open("R_L.ttf");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          } else if (StrContains(HTTP_req, "GET /R_M.ttf")) {
            webFile = SD.open("R_M.ttf");
            if (webFile) {
              client.println("HTTP/1.1 200 OK");
              client.println();
            }
          }
          /////////////////////////////////////Вот тут начинается Ajax///////////////////////////////////////////////
          else if (StrContains(HTTP_req, "readPinInfo")) { //если реквест содержит запрос readPinInfo то...     кстати, readPinInfo это и есть функция ответa ajax на js в index.htm 

            for (int i = FIRST_PIN; i <= LAST_PIN; i++){
              bool Dr = digitalRead(i);
              client.print(Dr);
            }
          }
          /////////////////////////////////////Вот заканчивается Ajax///////////////////////////////////////////////
          if (webFile) {
            while (webFile.available()) {
              client.write(webFile.read());  // отправляем готовые данные на страницу браузера
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

void StrClear(char *str, char length) {
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

char StrContains(char *str, char *sfind) {
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
    } else {
      found = 0;
    }
    index++;
  }
  return 0;
}
