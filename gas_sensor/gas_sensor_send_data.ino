//adafruitio_08_analog_in1

// board WeMos D1 R1
// NodeMCU 1.0 (ERSP -12E MODULE)

//#define IO_USERNAME    "**********"
//#define IO_KEY         "**********" 


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

// digital pin 4
#define LED_PIN4 4

// digital pin 5
#define LED_PIN5 5

// photocell state
int current = 0;
int last = -1;


AdafruitIO_Feed *analog = io.feed("analog");

void setup() {

  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);

  Serial.begin(115200);

  while(! Serial);

  // print to serial
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  io.run();

  current = analogRead(GAS_PIN);

  if(current == last)
    return;

  Serial.print("sending -> ");
  Serial.println(current);



  if(current  >  500){
    Serial.println("HIGH");
    digitalWrite(LED_PIN4,HIGH);
  }
  else
  {
    Serial.println("LOW");
    digitalWrite(LED_PIN4,LOW);
  } 
  
  
  analog->save(current);

  
  last = current;

  delay(2000);
}

