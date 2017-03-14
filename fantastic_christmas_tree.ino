#include "pitches.h"
#include <String.h>  
#include <avr/pgmspace.h>
#include <SPI.h>  
#include <Ethernet.h>   

const char page_default[] PROGMEM = {"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<title>The Fantastic Christmas Tree</title>"
"<meta charset='utf-8'>"
"<meta name='viewport' content='width=device-width, initial-scale=1'><meta http-equiv='Content-Type' content='text/html;charset=UTF-8' />"
"<link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css'>"
"<style> "
"body{background-color:#ffcced;}"
"#center{ text-align:center;}"
"#title{padding:5px 5px 5px 5px;background-color:#ccddff;color:#333;margin-bottom:20px;}"
"#center-table{margin:0 auto !important;float:none !important;}"
"#off{ width:50%;margin:0 auto;}"
"table td{text-align:center;vertical-align:middle;padding:5px 5px 5px 5px;}"
"</style>"
"<head>"
"<body>"
"<div id='center'><div id='title'>"
"<h2> The Fantastic Christmas Tree </h2>"
"</div>"
"</div>"
"<div id='center'>"
"<table id='center-table'>"
"<tr>"
"<td id='off' colspan='2'><a href='0' class='btn btn-danger btn-block btn-lg'>SWITCH OFF</a></td>"
"</tr>"
"<tr>"
"<td><a href='1' class='btn btn-success btn-block btn-lg'>Mode 1</a></td>"
"<td><a href='2' class='btn btn-success btn-block btn-lg'>Mode 2</a></td>"
"</tr>"
"<tr>"
"<td><a href='3' class='btn btn-success btn-block btn-lg'>Mode 3</a></td>"
"<td><a href='4' class='btn btn-success btn-block btn-lg'>Mode 4</a></td>"
"</tr>"
"<tr>"
"<td><a href='5' class='btn btn-success btn-block btn-lg'>Mode 5</a></td>"
"<td><a href='6' class='btn btn-success btn-block btn-lg'>Mode 6</a></td>"
"</tr>"
"<tr>"
"<td><a href='7' class='btn btn-success btn-block btn-lg'>Mode 7</a></td>"
"<td><a href='8' class='btn btn-success btn-block btn-lg'>Mode 8</a></td>"
"</tr>"
"<tr>"
"<td><a href='9' class='btn btn-success btn-block btn-lg'>Mode 9</a></td>"
"<td><a href='10' class='btn btn-success btn-block btn-lg'>Mode 10</a></td>"
"</tr>"
"<tr>"
"<td><a href='11' class='btn btn-success btn-block btn-lg'>Mode 11</a></td>"
"<td><a href='12' class='btn btn-success btn-block btn-lg'>Mode 12</a></td>"
"</tr>"
"<tr>"
"<td><a href='13' class='btn btn-warning btn-block btn-lg'>Jingle</a></td>"
"<td><a href='14' class='btn btn-warning btn-block btn-lg'>We Wish</a></td>"
"</tr></table>"
"</div>"
"</body>"
"</html>"};

//NETWORK

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   
//byte ip[] = { 192, 168, 1, 3 }; // indirizzo IP della shield  
byte gateway[] = { 192, 168, 1, 1 }; // indirizzo ip del router  
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask  
EthernetServer server(80);  

// MELODIES

byte tonePin = 35;
byte index = 0;

// jingle bells
int jingle_melody[] = {
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_D5, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_C5, NOTE_B4, NOTE_B4,
  NOTE_D5, NOTE_D5,
  NOTE_C5, NOTE_A4, NOTE_G4
};

// we wish you a merry christmas
int wish_melody[] = {
  NOTE_C4, NOTE_F4, NOTE_F4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_D4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_C4, NOTE_A4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_E4, NOTE_F4
};

// NOTE DURATIONS: 4 = quarter note, 8 = eighth note, etc..

// jingle_bells
byte jingle_duration[] = {
4, 4, 2,
4, 4, 2,
4, 4, 4, 4, 1,
4, 4, 2,
4, 4, 2,
4, 4, 4, 4, 1};

// we wish you a merry christmas
byte wish_duration[] = {
  4, 4, 8,
  8, 8, 8, 4, 4,
  4, 4, 8,
  8, 8, 8, 4, 4,
  4, 4, 8,
  8, 8, 8, 4, 4,
  8, 8, 4, 4, 4, 1
};

// LEDs arrays
byte red[] = {30, 42, 48, 44, 40, 38, 32};
byte red_len = 7;
byte green[] = {31, 37, 41, 47};
byte green_len = 4;
byte white[] = {49, 33};
byte yellow[] = {46, 39};
byte blue[] = {43, 45};

byte all[] = {30, 42, 48, 44, 40, 38, 32, 31, 37, 41, 47, 49, 33, 46, 39, 43, 45};
byte big[] = {46, 33, 43, 39, 49, 45};

byte randsN[4]; 

//TIMER variables
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

// FADE timer

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMicros = 0;        // will store the last time the blink cycle occured

long intervalLength = 500;     // interval at which to blink (microseconds)
long onInterval = 20;          // on or HIGH interval length
long currentInterval;          // length of the current interval
int  fadeLength = 200;
int  fadeCount = 0;
float  intervalDirection = 1;

// MISC

int k;
char myChar; 
String readMode;      

String global_read;
boolean new_code = true;

void setup() {
  
  Ethernet.begin(mac); 
  Serial.begin(9600);
  
  for (int i = 0; i <= 17; i++)
    pinMode(all[i], OUTPUT);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  pinMode(tonePin, OUTPUT);
  mode0();
}

void loop() {
  
  EthernetClient client = server.available();  
  char c;
  
  if (client) {  
    while (client.connected()) {  
      if (client.available()) { 
          c = client.read();

        if (c == '\n') {   
          global_read = readMode.substring(0, readMode.length()-2);   
          new_code = true;

          //print html page
            for (k = 0; k < strlen_P(page_default); k++){
              myChar =  (char)pgm_read_byte_near(page_default + k);
              client.print(myChar);
            }
          
           readMode = "";
           
          client.stop();  
        
        } else{ //keep reading
          if(isdigit(c))
            readMode.concat(c);   
            
        }
      }   
    }   
  }   

  if(new_code)
    mode0();
    
  currentMillis = millis();

  switch(global_read.toInt()){
    case 1: mode1();
      break;
    case 2: mode2();
      break;
    case 3: mode3();
      break;
    case 4: mode4();
      break;
    case 5: mode5();
      break;
    case 6: mode6();
      break;
    case 7: mode7();
      break;
    case 8: mode8();
      break;
    case 9: mode9();
      break;
    case 10: mode10();
      break;
    case 11: mode11();
      break;
    case 12: mode12();
      break;
    case 13: mode13();
      break;
    case 14: mode14();
      break;
    case 0: mode0();
      break;
  }

}

// all on
void mode12(){
  for (int i = 0; i <= 17; i++)
   digitalWrite(all[i], HIGH);
}

//all off
void mode0(){
  Serial.println("MODE 0");
  for (int i = 0; i <= 17; i++)
   digitalWrite(all[i], LOW);
  //digitalWrite(tonePin, LOW);
  new_code = false;
}
