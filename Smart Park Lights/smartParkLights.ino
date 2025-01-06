int ledPin2 = 2;
int ledPin3 = 3;
int ledPin5 = 5;
int ledPin6 = 6;
int ledPin9 = 9;
int ledPin10 = 10;
//int ledPin11 = 11;
int PhotoResPin = A0;
int PhotoResValue = 0;
int brightness = 0;
int interval = 20; 
int PhotoResLimitValue = 500;
int SwitchIs = 1; // 1 = ON , 0 = OFF


void setup() {
//pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(ledPin5, OUTPUT);
pinMode(ledPin6, OUTPUT);
pinMode(ledPin9, OUTPUT);
pinMode(ledPin10, OUTPUT);
//pinMode(ledPin11, OUTPUT);
Serial.begin(9600);

}


void loop() {
   PhotoResValue = analogRead(PhotoResPin);
   //PanelVal = map(PhotoResistorVal, 0, 1023, 0, 255);
   Serial.print("PhotoValue is : ");
   Serial.println(PhotoResValue);
   Serial.println(SwitchIs);
   
   if(PhotoResValue < PhotoResLimitValue && SwitchIs == 1 ){
     while (brightness < 250  ) {
   
     //analogWrite(ledPin, brightness);
    //digitalWrite(ledPin2,  HIGH);
      analogWrite(ledPin3,  brightness);
      analogWrite(ledPin5,  brightness);
      analogWrite(ledPin6,  brightness);
      analogWrite(ledPin9,  brightness);
      analogWrite(ledPin10, brightness);
   // analogWrite(ledPin11, brightness);
     brightness = brightness + interval;
     delay(100);
    
    //PhotoResistorVal = analogRead(PanelPin);
    //PanelVal = map(PhotoResistorVal, 0, 1023, 0, 255);
    
    Serial.print("Brightnes is --- : ");
     Serial.println(brightness);
     }
   }  

  SwitchIs = 0;
  
  if(PhotoResValue > PhotoResLimitValue){
    brightness = 0;
    SwitchIs = 1;
    analogWrite(ledPin3,  brightness);
    analogWrite(ledPin5,  brightness);
    analogWrite(ledPin6,  brightness);
    analogWrite(ledPin9,  brightness);
    analogWrite(ledPin10, brightness);
  }
  delay(100);
  // brightness = 0;
   //if(PanelVal < OnOffValue){
    //digitalWrite(ledPin2,  LOW);
    //analogWrite(ledPin3,  brightness);
   // analogWrite(ledPin5,  brightness);
    //analogWrite(ledPin6,  brightness);
    //analogWrite(ledPin9,  brightness);
    //analogWrite(ledPin10, brightness);
    //analogWrite(ledPin11, brightness);
   //}
   
 }
  
  
