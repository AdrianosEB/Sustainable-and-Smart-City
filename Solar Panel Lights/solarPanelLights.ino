int ledPin2 = 2;
int ledPin3 = 3;
int ledPin5 = 5;
int ledPin6 = 6;
int ledPin9 = 9;
int ledPin10 = 10;
int ledPin11 = 11;
int InputPin12 = 12;
int InputPin12Val= 0;
int PanelPin = A0;
int PanelPinValue = 0;
int brightness = 0;
int interval = 50; 
int PanelLimitValue = 550; //330; // threshold
int SwitchIs = 1; // 1 = ON , 0 = OFF


void setup() {
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(ledPin5, OUTPUT);
pinMode(ledPin6, OUTPUT);
pinMode(ledPin9, OUTPUT);
pinMode(ledPin10, OUTPUT);
pinMode(ledPin11, OUTPUT);
pinMode(8, OUTPUT);
pinMode(13, OUTPUT);
pinMode(InputPin12, INPUT);
Serial.begin(9600);

}


void loop() {
  InputPin12Val = 0;
  InputPin12Val = digitalRead(InputPin12);
   PanelPinValue = analogRead(PanelPin);
   //Serial.print("PanelValue is : ");
   //Serial.println(PanelPinValue);
   //Serial.println(SwitchIs);
   Serial.print("InputPin12Val is --- : ");
    Serial.println(InputPin12Val);
  SwitchIs = 1;

   while (InputPin12Val == 1  ){

      digitalWrite(ledPin2,  HIGH);
      digitalWrite(8,  HIGH);
      digitalWrite(13,  HIGH);
      analogWrite(ledPin3,  250);
      analogWrite(ledPin5,  250);
      analogWrite(ledPin6,  250);
      analogWrite(ledPin9,  250);
      analogWrite(ledPin10, 250);
      analogWrite(ledPin11, 250);
      delay(200);
      digitalWrite(ledPin2,  LOW);
      digitalWrite(8,  LOW);
      digitalWrite(13,  LOW);
      analogWrite(ledPin3,  0);
      analogWrite(ledPin5,  0);
      analogWrite(ledPin6,  0);
      analogWrite(ledPin9,  0);
      analogWrite(ledPin10, 0);
      analogWrite(ledPin11, 0);
      delay(2000);
      brightness = 0;
      digitalWrite(13, HIGH);
      Serial.print("InputPin12Val inside  : ");
   Serial.println(InputPin12Val);
       InputPin12Val = digitalRead(InputPin12);
      
    
   }
  
  digitalWrite(13, LOW);
  //Serial.print("PanelValue is : ");
  //Serial.println(PanelPinValue);
   Serial.print("InputPin12Val is : ");
   Serial.println(InputPin12Val);
   //Serial.println("brightness  ");
   //Serial.print(brightness);

  
   
//   if(PanelPinValue < PanelLimitValue && SwitchIs == 1 ){
   if(PanelPinValue > PanelLimitValue && SwitchIs == 1 ){
     while (brightness < 250  ) {
   Serial.println("MPIKA WILE ");
   Serial.println(brightness);
      digitalWrite(ledPin2,  HIGH);
      analogWrite(ledPin3,  brightness);
      analogWrite(ledPin5,  brightness);
      analogWrite(ledPin6,  brightness);
      analogWrite(ledPin9,  brightness);
      analogWrite(ledPin10, brightness);
      analogWrite(ledPin11, brightness);
      brightness = brightness + interval;
      delay(200);
     }
   }  

  SwitchIs = 0;
  
//  if(PanelPinValue > PanelLimitValue){
  if(PanelPinValue < PanelLimitValue){

    brightness = 0;
    SwitchIs = 1;
    digitalWrite(ledPin2,  LOW);
    analogWrite(ledPin3,  brightness);
    analogWrite(ledPin5,  brightness);
    analogWrite(ledPin6,  brightness);
    analogWrite(ledPin9,  brightness);
    analogWrite(ledPin10, brightness);
    analogWrite(ledPin11, brightness);
  }
  delay(100);
 }

  
