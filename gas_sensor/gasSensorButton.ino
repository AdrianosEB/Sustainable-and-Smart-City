// Code from Arduino-Adafruit connection docs
//adafruitio_08_analog_in1

// board WeMos D1 R1
// NodeMCU 1.0 (ESP -12E MODULE)

//#define IO_USERNAME    "******"
//#define IO_KEY         "*************" 


// Adafruit IO Analog In Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-analog-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// analog pin 0
#define GAS_PIN A0

// patch
// digital pin 4 LED
#define LED_PIN4 4

// digital pin 5 beep
#define LED_PIN5 5

// digital pin 2
#define LED_PIN2 2

// photocell state
int current = 0;
int last = -1;

// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("analog");

AdafruitIO_Feed *digital = io.feed("digital");


void setup() {
//patch
  pinMode(LED_PIN4, OUTPUT); // LED
  pinMode(LED_PIN5, OUTPUT);  // beep
  pinMode(LED_PIN2, OUTPUT); // controling Arduino City Panels 

  Serial.begin(115200);

  while(! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());


  digital->onMessage(handleMessage);

   digital->get();

}

void loop() {


  io.run();

  // grab the current state of the photocell
  current = analogRead(GAS_PIN);

  if(current == last)
    return;

  Serial.print("sending -> ");
  Serial.println(current);

//patch
  while(current  >  500){
    analog->save(current);
    digitalWrite(LED_PIN5,HIGH);
    digitalWrite(LED_PIN2,HIGH);
    digitalWrite(LED_PIN4, HIGH);
    delay(500);
    digitalWrite(LED_PIN4, LOW);
    delay(500);
    current = analogRead(GAS_PIN);
  }
    digitalWrite(LED_PIN5,LOW);
    digitalWrite(LED_PIN2 ,LOW);
    analog->save(current);
  
  
//  if(current  >  500){
//    digitalWrite(LED_PIN5,HIGH);
//     digitalWrite(LED_PIN4, HIGH);
//     delay(500);
//      digitalWrite(LED_PIN4, LOW);
//      delay(500);
//      digitalWrite(LED_PIN4, HIGH);
//       delay(500);
//      digitalWrite(LED_PIN4, LOW);
//  }
//  else
//  {
//    digitalWrite(LED_PIN5,LOW);
//  } 
//  
//  
//  analog->save(current);

  

  // store last photocell state
  last = current;

  delay(2000);
}


void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
 Serial.println (data->toPinLevel());
  if(data->toPinLevel() == 1 ){
    digitalWrite(LED_PIN4, HIGH);
     
    
  }
    
  else{
    Serial.println("OFF");
    digitalWrite(LED_PIN4, LOW);
    
  }

  //digitalWrite(LED_PIN4, data->toPinLevel());
}
