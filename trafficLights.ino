// Code from API connect Arduino to adafruit
//adafruitio_08_analog_in1

// board WeMos D1 R1
// NodeMCU 1.0 (ESP -12E MODULE)

//#define IO_USERNAME    "*********"
//#define IO_KEY         "*********" 


// Adafruit IO Analog In Example
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


String inString = "";    // string to hold input
 
int incomingByte ;
//String incomingByte;

// analog pin 0
#define GAS_PIN A0

// LED 1 , D3 ,D4, D9
#define red_light_pin 5 // D3
#define green_light_pin 4 //D4
#define blue_light_pin 2 //D9


int current = 0;
String currentSTR = "";
int last = -1;

AdafruitIO_Feed *analog = io.feed("analog");

AdafruitIO_Feed *digital = io.feed("digital");




void setup() {

  pinMode(red_light_pin, OUTPUT); // LED
  pinMode(green_light_pin, OUTPUT);  // LED
  pinMode(blue_light_pin, OUTPUT); // LED

  


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


  RGB_color(255, 255, 255); // White
  delay(1000);


  digital->onMessage(handleMessage);

   digital->get();

}

void loop() {


  io.run();

  


 if (Serial.available() > 0) {

  incomingByte = Serial.readStringUntil('\n').toInt();
  Serial.println("incomingByte ");
  Serial.print(incomingByte);
  

    current = incomingByte; // to analog feed
    analog->save(current);  // to analog feed

    
    if (incomingByte >= 1) {
       RGB_color(255, 0, 0); // Red
      Serial.println(" Led on");
    }

    else if (incomingByte == 0) {
       RGB_color(0, 255, 0); // Green
      Serial.println(" Led on ");
    }
//     else if (incomingByte == "B") {
//      RGB_color(0, 0, 255); // Blue
//      Serial.println(" Led on ");
//    }
    else{
     Serial.write(" invald input ");
    }
  }
  

  delay(2000);
}


void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received.. <- ");
 Serial.println (data->toPinLevel());
  if(data->toPinLevel() == 1 ){
     RGB_color(255, 255, 255); // WHITE
  }
  else{
    Serial.println("OFF");
    RGB_color(0, 0, 0); // NO COLOR  
  }

  //digitalWrite(LED_PIN4, data->toPinLevel());
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
