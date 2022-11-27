#include <SPI.h>
#include <Ethernet.h>

  

    byte D1 = 0;
    byte D2 = 0;
    byte D3 = 0;
    byte D4 = 0;
    byte D5 = 0;
    byte D6 = 0;
    byte D7 = 0;

// set up variables using the SD utility library functions:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 111);
EthernetServer server(80);

void setup() {
  pinMode(49, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
   
    D1 = digitalRead(49);
    /*D2 = digitalRead(24);
    D3 = digitalRead(26);
    D4 = digitalRead(28);
    D5 = digitalRead(30);
    D6 = digitalRead(32);
    D7 = digitalRead(34);*/
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html lang=\"ru\">");
          client.println("<meta charset=\"UTF-8\">");
          // output the value of each analog input pin
          /*for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }*/
          client.println("<title>Система мониторинка ЦС(СУС)</title>");
          client.println("<style>");
          client.println("html, body, div, span, applet, object, iframe, h1, h2, h3, h4, h5, h6, p, blockquote, pre, a, abbr, acronym, address, big, cite, code, del, dfn, em, img, ins, kbd, q, s, samp, small, strike, strong, sub, sup, tt, var, b, u, i, center, dl, dt, dd, ol, ul, li, fieldset, form, label, legend, table, caption, tbody, tfoot, thead, tr, th, td, article, aside, canvas, details, embed, figure, figcaption, footer, header, hgroup, menu, nav, output, ruby, section, summary, time, mark, audio, video {margin: 0;padding: 0;border: 0;font-size: 100%;font: inherit;vertical-align: baseline;}:focus {outline: 0;}article, aside, details, figcaption, figure, footer, header, hgroup, menu, nav, section {display: block;}body {line-height: 1;}ol, ul {list-style: none;}blockquote, q {quotes: none;}blockquote:before, blockquote:after, q:before, q:after {content: '';content: none;}table {border-collapse: collapse;border-spacing: 0;}input[type=search]::-webkit-search-cancel-button, input[type=search]::-webkit-search-decoration, input[type=search]::-webkit-search-results-button, input[type=search]::-webkit-search-results-decoration {-webkit-appearance: none;-moz-appearance: none;}input[type=search] {-webkit-appearance: none;-moz-appearance: none;-webkit-box-sizing: content-box;box-sizing: content-box;}textarea {overflow: auto;vertical-align: top;resize: vertical;}audio, canvas, video {display: inline-block;*display: inline;*zoom: 1;max-width: 100%;}audio:not([controls]) {display: none;height: 0;}[hidden] {display: none;}html {font-size: 100%;-webkit-text-size-adjust: 100%;-ms-text-size-adjust: 100%;}a:focus {outline: thin dotted;}a:active, a:hover {outline: 0;}img {border: 0;-ms-interpolation-mode: bicubic;}figure {margin: 0;}form {margin: 0;}fieldset {border: 1px solid #c0c0c0;margin: 0 2px;padding: 0.35em 0.625em 0.75em;}legend {border: 0;padding: 0;white-space: normal;*margin-left: -7px;}button, input, select, textarea {font-size: 100%;margin: 0;vertical-align: baseline;*vertical-align: middle;}button, input {line-height: normal;}");
          client.println("button, select {text-transform: none;}button, html input[type=\"button\"], input[type=\"reset\"], input[type=\"submit\"] {-webkit-appearance: button;cursor: pointer;*overflow: visible;}button[disabled], html input[disabled] {cursor: default;}input[type=\"checkbox\"], input[type=\"radio\"] {-webkit-box-sizing: border-box;box-sizing: border-box;padding: 0;*height: 13px;*width: 13px;}input[type=\"search\"] {-webkit-appearance: textfield;-webkit-box-sizing: content-box;box-sizing: content-box;}input[type=\"search\"]::-webkit-search-cancel-button, input[type=\"search\"]::-webkit-search-decoration {-webkit-appearance: none;}button::-moz-focus-inner, input::-moz-focus-inner {border: 0;padding: 0;}textarea {overflow: auto;vertical-align: top;}table {border-collapse: collapse;border-spacing: 0;}html, button, input, select, textarea {color: #222;}::-moz-selection {background: #b3d4fc;text-shadow: none;}::selection {background: #b3d4fc;text-shadow: none;}img {vertical-align: middle;}fieldset {border: 0;margin: 0;padding: 0;}textarea {resize: vertical;}.chromeframe {margin: 0.2em 0;background: #ccc;color: #000;padding: 0.2em 0;}*, *:before, *:after {-webkit-box-sizing: border-box;box-sizing: border-box;}@font-face {font-family: Roboto;src: url(..//fonts/RobotoMono-ExtraLight.ttf);font-weight: 100;}@font-face {font-family: Roboto;src: url(..//fonts/RobotoMono-Light.ttf);font-weight: 200;}@font-face {font-family: Roboto;src: url(..//fonts/RobotoMono-Medium.ttf);font-weight: 300;}body {font-family: 'Roboto';font-style: normal;font-weight: 100;color: white;font-size: 16px;background: #1d1c1c;overflow-x: hidden;counter-reset: section;}#p_preloader {background: #000;position: fixed;width: 100vw;height: 100vh;top: 0;left: 0;display: -webkit-box;display: -ms-flexbox;display: flex;-webkit-box-pack: center;-ms-flex-pack: center;justify-content: center;-webkit-box-align: center;-ms-flex-align: center;align-items: center;z-index: 9;opacity: 1;visibility: visible;-webkit-transition: 2s;transition: 2s;}.box {width: 100%;display: -webkit-box;");
          client.println("display: -ms-flexbox;display: flex;}.wrapper__1 {min-width: 15%;margin-right: 30px;margin-bottom: 20px;}.wrapper__1 h2 {font-family: serif;width: 90%;margin: 0 auto;text-align: center;padding-top: 30px;margin-bottom: 10px;font-weight: 200;font-size: 30px;}.main {width: 100%;position: relative;}.wrapper {max-width: 90%;padding: 0 20px;margin: 0 auto;overflow: hidden;position: relative;}.table {display: -ms-grid;display: grid;background: #333333;margin-top: 10px;border-radius: 5px;gap: 5px;}.table__grid {display: -ms-grid;display: grid;position: relative;text-align: center;-ms-grid-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-template-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-column: span 6;-webkit-box-align: center;-ms-flex-align: center;align-items: center;}.table__item {display: -ms-grid;display: grid;-ms-grid-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-template-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-column: span 6;-webkit-box-align: center;-ms-flex-align: center;align-items: center;padding: 7px 0;-webkit-transition: 0.2s;transition: 0.2s;border-radius: 5px;}.table__item:hover {background-color: rgba(0, 0, 0, 0.697);-webkit-transition: 0.2s;transition: 0.2s;cursor: pointer;}.table__title {text-align: center;display: -ms-grid;display: grid;position: relative;-ms-grid-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-template-columns: 0.3fr 1fr 1fr 1fr 1fr 1fr;grid-column: span 6;-webkit-box-align: center;-ms-flex-align: center;align-items: center;padding: 5px 0;font-weight: 300;cursor: auto;}.popup__bg {position: fixed;top: 0;left: 0;height: 100vh;width: 100%;display: none;-webkit-backdrop-filter: blur(2px);backdrop-filter: blur(2px);z-index: 3;}.popup {display: none;width: 80%;height: 25vh;position: fixed;left: 50%;top: 50%;-webkit-transform: translate(-50%, -50%);transform: translate(-50%, -50%);margin: 0 auto;background-color: #111111d0;border-radius: 5px;z-index: 4;}.close {position: absolute;top: 10px;right: 10px;z-index: 4;cursor: pointer;}.close img {width: 30px;height: 30px;}.popup__content {height: 90%;margin: 0 auto;");
          client.println("display: -webkit-box;display: -ms-flexbox;display: flex;-webkit-box-orient: vertical;-webkit-box-direction: normal;-ms-flex-direction: column;flex-direction: column;-webkit-box-pack: space-evenly;-ms-flex-pack: space-evenly;justify-content: space-evenly;width: 80%;}.popup__content-down {display: -webkit-box;display: -ms-flexbox;display: flex;-webkit-box-pack: justify;-ms-flex-pack: justify;justify-content: space-between;}.popup__content-down div {width: 50%;}.popup__on {display: block;}.search-form {padding-top: 20px;width: 80%;margin: 0 auto;display: -webkit-box;display: -ms-flexbox;display: flex;-webkit-box-orient: vertical;-webkit-box-direction: normal;-ms-flex-direction: column;flex-direction: column;}.system-search {color: white;border: none;background: #000;width: 40%;height: 30px;border-radius: 20px;padding: 0 20px;margin-bottom: 20px;}.system-search::-webkit-input-placeholder {color: #444444;}.system-search:-ms-input-placeholder {color: #444444;}.system-search::-ms-input-placeholder {color: #444444;}.system-search::placeholder {color: #444444;}#filter-on, #filter-off {background-color: #000;margin-top: 10px;}.state_on {color: greenyellow;}.state_off {color: red;}.hidden_search {display: none;}.show_search {display: block;}.hidden_check {display: none;}.row-number::before {counter-increment: section;content: counter(section) \".\";}d");
          client.println("</style>");
          client.println("<div class=\"wrapper__1\">");
        client.println("<h2>Система мониторинга систем передачи центра связи (СУС)</h2>");
        client.println("<form class=\"search-form\" action="" method=\"GET\">");
          client.println("<div><label hidden for=\"system-search\">Фильтр</label>");
            client.println("<input placeholder=\"Поиск...\" type=\"search\" name=\"system-search\" id=\"system-search\"class=\"system-search\"></div>");
          client.println("<div><input type=\"checkbox\" name=\"state-on\" value=\"В работе\" id=\"filter-on\"> Исправные</div>");
          client.println("<div><input type=\"checkbox\" name=\"state-off\" value=\"Авария\" id=\"filter-off\"> Неисправные</div></form></div>");
      client.println("<div class=\"main\">");
        client.println("<div class=\"wrapper\">");
          client.println("<div class=\"table\" id=\"table-systems\">");
            client.println("<div class=\"table__title\">");
              client.println("<div>№ <br>п/п</div>");
              client.println("<div>Система передачи</div>");
              client.println("<div>Приоритет</div>");
              client.println("<div>Корреспондент</div>");
              client.println("<div>Тип трассы</div>");
              client.println("<div>Состояние</div>");
            client.println("</div>");

            client.println("<div class=\"table__grid\">");
                client.println("<div class=\"table__item\">");
                  client.println("<div class=\"row-number\"></div>");
                  client.println("<div class=\"numberSystem\">${item.numberSystem}</div>");
                  client.println("<div>${item.priority}</div>");
                  client.println("<div>${item.correspondent}</div>");
                  client.println("<div>${item.type}</div>");
                client.println("<div class=\"state\">${item.state}</div></div>");
             client.println("<div class=\"popup__wrapper\">");
              client.println("<div class=\"popup\">");
                client.println("<div class=\"close\"><a class=\"close__img\">X</a></div>");
                 client.println("<div class=\"popup__content\">");
                   client.println("<div>Трасса: 595Б + 1122/2-1 + 111Г + 2203/2 + 666Б</div>");
                   client.println("<div class=\"popup__content-down\">");
                   client.println("<div>Загрузка:</div>");
                   client.println("<div class=\"popup__state\"> Состояние:</div>");
                   client.println("Работа");
            client.println("</div></div></div></div></div>");

            client.println("<div class=\"table__grid\">");
                client.println("<div class=\"table__item\">");
                  client.println("<div class=\"row-number\"></div>");
                  client.println("<div class=\"numberSystem\">${item.numberSystem}</div>");
                  client.println("<div>${item.priority}</div>");
                  client.println("<div>${item.correspondent}</div>");
                  client.println("<div>${item.type}</div>");
                client.println("<div class=\"state\">");
                client.println(D1);
                client.println("</div></div>");
             client.println("<div class=\"popup__wrapper\">");
              client.println("<div class=\"popup\">");
                client.println("<div class=\"close\"><a class=\"close__img\">X</a></div>");
                 client.println("<div class=\"popup__content\">");
                   client.println("<div>Трасса: 595Б + 1122/2-1 + 111Г + 2203/2 + 666Б</div>");
                   client.println("<div class=\"popup__content-down\">");
                   client.println("<div>Загрузка:</div>");
                   client.println("<div class=\"popup__state\"> Состояние:</div>");
                   client.println("Работа");
            client.println("</div></div></div></div></div>");


            client.println("<div class=\"table__grid\">");
                client.println("<div class=\"table__item\">");
                  client.println("<div class=\"row-number\"></div>");
                  client.println("<div class=\"numberSystem\">${item.numberSystem}</div>");
                  client.println("<div>${item.priority}</div>");
                  client.println("<div>${item.correspondent}</div>");
                  client.println("<div>${item.type}</div>");
                client.println("<div class=\"state\">${item.state}</div></div>");
             client.println("<div class=\"popup__wrapper\">");
              client.println("<div class=\"popup\">");
                client.println("<div class=\"close\"><a class=\"close__img\">X</a></div>");
                 client.println("<div class=\"popup__content\">");
                   client.println("<div>Трасса: 595Б + 1122/2-1 + 111Г + 2203/2 + 666Б</div>");
                   client.println("<div class=\"popup__content-down\">");
                   client.println("<div>Загрузка:</div>");
                   client.println("<div class=\"popup__state\"> Состояние:</div>");
                   client.println("Работа");
            client.println("</div></div></div></div></div>");


            client.println("<div class=\"table__grid\">");
                client.println("<div class=\"table__item\">");
                  client.println("<div class=\"row-number\"></div>");
                  client.println("<div class=\"numberSystem\">${item.numberSystem}</div>");
                  client.println("<div>${item.priority}</div>");
                  client.println("<div>${item.correspondent}</div>");
                  client.println("<div>${item.type}</div>");
                client.println("<div class=\"state\">${item.state}</div></div>");
             client.println("<div class=\"popup__wrapper\">");
              client.println("<div class=\"popup\">");
                client.println("<div class=\"close\"><a class=\"close__img\">X</a></div>");
                 client.println("<div class=\"popup__content\">");
                   client.println("<div>Трасса: 595Б + 1122/2-1 + 111Г + 2203/2 + 666Б</div>");
                   client.println("<div class=\"popup__content-down\">");
                   client.println("<div>Загрузка:</div>");
                   client.println("<div class=\"popup__state\"> Состояние:</div>");
                   client.println("Работа");
            client.println("</div></div></div></div></div>");

           client.println("</div>");
           client.println("</div>");
           client.println("</div>");
           client.println("</div>");
           client.println("</html>");
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
    Serial.println("client disconnected");
  }
}
