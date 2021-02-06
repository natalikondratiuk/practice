/* Практичне завдання
 * Відстеження потоку людей у ТЦ
 * студентки ПІ-18-1
 * Кондратюк Наталії
 * Головний файл проекту:
 *  - підключення всіх необхідних бібліотек:
 *  - для зв'язку з веб-сервером Tingspeak;
 *  - для створення веб-сервера на ESP 8266;
 *  - для відображення графіку потоку людей на OLED дисплеї
**************************************************************/
// Thingspeak
#include <WiFiClientSecure.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

// Web server
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// OLED display 128x64 SH1106
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#define DELAY 20000
#define workTime 720 // робочий час у хвилинах
#define wDisp 128
#define hDisp 64

// Індикатор поточної зони
#define greenLed 16
#define yellowLed 0
#define redLed 2

const PROGMEM int dataTest[] = { 0, 2, 3, 3, 5, 7, 7, 8, 9, 10, 8, 10, 9, 12, 12, 14, 13, 14, 13, 14, 13, 14, 16, 18, 16, 18, 18, 17, 18, 19, 19, 23, 20, 22, 23, 25, 25, 26, 26, 30, 29, 32, 33, 36, 38, 40, 39, 44, 42, 47, 47, 51, 50, 52, 54, 56, 56, 60, 60, 63, 63, 67, 67, 73, 74, 75, 76, 80, 79, 84, 84, 86, 85, 85, 85, 88, 88, 90, 93, 92, 92, 95, 94, 94, 94, 97, 96, 98, 99, 100, 100, 99, 97, 98, 101, 100, 100, 100, 100, 102, 100, 103, 101, 100, 101, 100, 101, 103, 102, 104, 103, 102, 101, 104, 101, 104, 103, 104, 104, 103, 104, 104, 103, 103, 102, 103, 106, 104, 103, 107, 107, 105, 107, 106, 108, 108, 109, 106, 108, 108, 107, 111, 110, 110, 112, 110, 111, 112, 111, 113, 113, 114, 116, 117, 116, 117, 115, 119, 118, 120, 117, 121, 119, 123, 122, 122, 121, 124, 123, 126, 125, 126, 128, 129, 127, 127, 127, 131, 131, 132, 132, 132, 135, 133, 135, 137, 135, 137, 139, 138, 141, 138, 138, 141, 139, 142, 143, 146, 145, 149, 148, 152, 152, 152, 154, 158, 157, 163, 160, 167, 166, 170, 168, 172, 174, 179, 177, 182, 181, 187, 185, 191, 193, 196, 195, 202, 201, 204, 203, 209, 209, 211, 211, 214, 213, 217, 219, 220, 220, 225, 226, 225, 225, 228, 227, 231, 231, 232, 229, 232, 230, 233, 231, 233, 233, 235, 234, 235, 233, 234, 233, 233, 234, 233, 232, 233, 232, 232, 231, 232, 229, 228, 230, 227, 227, 229, 227, 227, 224, 223, 223, 224, 222, 220, 223, 222, 219, 218, 220, 216, 218, 215, 215, 213, 213, 209, 210, 210, 211, 206, 206, 204, 207, 205, 204, 201, 202, 197, 199, 195, 194, 192, 193, 191, 191, 187, 187, 183, 185, 180, 179, 176, 175, 174, 173, 168, 168, 165, 164, 161, 161, 159, 159, 153, 156, 150, 153, 150, 150, 146, 146, 141, 141, 142, 142, 138, 139, 137, 134, 136, 134, 135, 133, 132, 131, 134, 131, 131, 132, 131, 134, 133, 134, 133, 135, 136, 134, 134, 135, 138, 137, 140, 138, 139, 141, 143, 143, 145, 143, 147, 148, 148, 149, 152, 149, 152, 153, 152, 153, 156, 156, 157, 157, 160, 161, 163, 163, 163, 164, 164, 165, 166, 167, 169, 168, 170, 171, 171, 172, 171, 170, 170, 170, 172, 172, 173, 175, 175, 175, 176, 173, 173, 175, 173, 176, 173, 173, 176, 176, 175, 174, 173, 173, 174, 173, 175, 174, 174, 176, 174, 173, 175, 174, 173, 174, 176, 173, 173, 175, 176, 176, 174, 175, 174, 173, 173, 175, 173, 176, 175, 176, 177, 175, 177, 177, 177, 176, 180, 181, 183, 183, 184, 184, 187, 189, 192, 192, 195, 196, 201, 201, 207, 205, 212, 210, 215, 216, 221, 221, 224, 226, 233, 233, 238, 239, 243, 244, 249, 248, 253, 255, 259, 258, 264, 264, 267, 265, 269, 269, 271, 272, 276, 277, 278, 279, 278, 281, 280, 280, 279, 279, 281, 278, 279, 278, 276, 277, 274, 276, 271, 273, 269, 269, 265, 265, 259, 259, 257, 255, 252, 253, 246, 246, 242, 243, 238, 239, 231, 233, 228, 229, 224, 221, 218, 219, 212, 214, 207, 210, 203, 203, 200, 202, 195, 195, 195, 193, 192, 189, 188, 189, 186, 188, 186, 185, 183, 184, 183, 184, 185, 183, 185, 187, 186, 185, 188, 186, 188, 191, 190, 193, 194, 192, 196, 193, 198, 197, 200, 200, 199, 202, 204, 203, 206, 206, 206, 206, 210, 208, 211, 208, 212, 211, 211, 212, 213, 210, 211, 212, 210, 210, 208, 208, 208, 208, 205, 207, 204, 206, 202, 199, 198, 198, 192, 193, 187, 184, 180, 179, 170, 172, 162, 162, 158, 158, 151, 148, 140, 143, 134, 131, 123, 125, 115, 115, 106, 106, 96, 97, 88, 86, 81, 80, 73, 75, 67, 65, 58, 61, 52, 52, 48, 46, 41, 41, 38, 36, 35, 34, 33, 33, 29, 31, 30, 29, 25, 26, 26, 24, 22, 21, 21, 23, 18, 20, 19, 20, 15, 17, 17, 15, 12, 12, 13, 11, 12, 12, 11, 10, 9, 10, 7, 5, 5, 4, 4, 3, 2, 0, 0 }; // тестові дані, які будуть підставлятися у реальний масив
int sizetestM = sizeof ( dataTest ) / sizeof(dataTest[0]);
ESP8266WebServer server(80);

WiFiClient  client;

U8G2_SH1106_128X64_WINSTAR_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 15, /* dc=*/ 4, /* reset=*/ 5);    // same as the NONAME variant, but uses updated SH1106 init sequence

uint8_t led = 16;

char* ssid = "ATN-139";
char* password = "TerVA1912w";

// Thingspeak
unsigned long myChannelNumber = 1296934;
const char * myWriteAPIKey = "30KQ3L0WJ9U1X57T";

int shift = 0; // зсув
unsigned long int timing = 0; // період отримання даних
int timeNow = 0; // лічильник поточного часу
int dataReal[workTime]; //масив для збереження поточних даних

// Змінні, що показуватимуть зони
int greenZone = 0; // зелена зона: 0-100
int yellowZone = 0; // жовта зона: 100-200
int redZone = 0; // червона зона: 200 і вище

// Для відображення поточного часу
int dispM = 0;
int t = 540; // 9:00 ранку
int stepH = 60; // 1 хв = 60 с

String personStr = "";

int countPersons = 0;
String outTimeWeb = "";


float pi = 3.1415926;

void HTTP_handleRoot( void );
void printOled ( int *m, int sizeM );

void test (){
  digitalWrite(led, HIGH);
  server.send(200, "text/plain", "hello from esp8266!");
  delay(3000);
  digitalWrite(led, 0);
}//test

void counter (){
  String counter = String ( countPersons );
  server.send(200, "text/plain", counter);
} // counter

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.setDisplayRotation(U8G2_R2);
}

void setup() {
  // put your setup code here, to run once:
  // indicators of zones
  pinMode( greenLed, OUTPUT );
  pinMode( yellowLed, OUTPUT );
  pinMode( redLed, OUTPUT );
  
  // webServer
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  
  WiFi.begin( ssid, password );
  Serial.begin( 115200 );
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



  server.on("/", HTTP_handleRoot);
  server.on("/inline", test );
  server.on("/counter", counter );
  server.begin();

  // display
  u8g2.begin();
  u8g2_prepare();

  for ( int i = 0; i < 720; i++ ){
    dataReal[i] = -1;
  } // for i
}


void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  unsigned long int timingNow = millis();
   
  if ( timingNow - timing > DELAY ){
    timing = timingNow;

    // default settings of indicators
    digitalWrite ( greenLed, LOW );
    digitalWrite ( yellowLed, LOW );
    digitalWrite ( redLed, LOW );
     
    countPersons = dataTest[timeNow];    
    
    int x = ThingSpeak.writeField(myChannelNumber, 1, countPersons, myWriteAPIKey); //відправка показника в thingspeak
     if(x == 200){
      Serial.println("Channel update successful.");
  }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    //формування строки часу
    
    dispM++; // + 1 хв
    if ( dispM == stepH ){
      dispM = 0;
      t += stepH;
    } // if dispM - якщо лічильник хвилин досягне 60 -> лічильник хвилин = 0, а до годин, що у хвилинах + 60 (1 год)
    int dispH = t/60; // хв переводимо у год
    if ( dispH == 21 ) t = 540;
    String outTime = ""; // для заливки на веб сервер
    if ( dispH < 10 ) outTime += "0";
    outTime += dispH;
    outTime += ":";
    if ( dispM < 10 ) outTime += "0";
    outTime += dispM;
    outTimeWeb = outTime;

    //керування світлодіодами
    
    if ( countPersons < 100 ){
      greenZone++;
      digitalWrite ( greenLed, HIGH );
    } // if greenZone
    else if ( countPersons >= 100 && countPersons < 200 ){
      yellowZone++;
      digitalWrite ( yellowLed, HIGH );
    } // if yellowZone
    else if ( countPersons >= 200 ){
      redZone++;
      digitalWrite ( redLed, HIGH );
    } // if redZone

    
    dataReal[timeNow] = countPersons; // занесення даних у масив для подальшого відтворення

    //формування строки для виводу на OLED
    
    personStr += countPersons;
    personStr += ", ";
    if ( timeNow ) printOled ( dataReal, timeNow+1 );
    if ( timeNow < sizetestM - 1 ){
      timeNow++;
    }
    else {
      timeNow = 0;
      personStr = "";
    }
  } //if main
}
