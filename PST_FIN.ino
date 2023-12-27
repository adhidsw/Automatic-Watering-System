#include <LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
Servo myservo;

const int relayPin = 8; 
const int ldrPin = A0;
const int ledPin = 9;
int pos=90;
int mode=0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);  
  myservo.attach(10);
}

void umode(){
  mode = (mode + 1) % 4;
  lcd.setCursor(0,1);
  lcd.print("M:");
  lcd.print(mode);
  Serial.print("M:");
  Serial.println(mode);
  delay(1000);
}

void mode0(){
    lcd.setCursor(10,1);
    lcd.print("kering");
}

void mode1(){
    lcd.setCursor(0,0);
    lcd.print("    Menyiram    ");
    lcd.setCursor(10,1);
    lcd.print("kering");
    myservo.write(pos);   

  
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);
}

void mode2(){
    lcd.setCursor(0,0);
    lcd.print("    Menyiram    ");
    lcd.setCursor(10,1);
    lcd.print("kering");
         

    for (pos = 90; pos >= 60; pos -= 1) { 
    myservo.write(pos);              
    delay(10);                      
    }
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);
    
    for (pos = 60; pos <= 120; pos += 1) { 
    myservo.write(pos);              
    delay(10);                      
    }
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);

    for (pos = 120; pos >= 90; pos -= 1) { 
    myservo.write(pos);            
    delay(10);
    }
}

void mode3(){
    lcd.setCursor(0,0);
    lcd.print("    Menyiram    ");
    lcd.setCursor(10,1);
    lcd.print("kering");
          
    
    for (pos = 90; pos >= 30; pos -= 1) { 
    myservo.write(pos);              
    delay(10);                      
    }
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);
    
    for (pos = 30; pos <= 90; pos += 1) { 
    myservo.write(pos);              
    delay(10);                      
    }
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);

    for (pos = 90; pos <= 150; pos += 1) { 
    myservo.write(pos);            
    delay(10);
    }
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);

    for (pos = 150; pos >= 90; pos -= 1) { 
    myservo.write(pos);            
    delay(10);
    }
}

void loop() {
  digitalWrite(ledPin,HIGH);
  lcd.setCursor(0,1);
  lcd.print("M:");
  lcd.print(mode);

  int Sensor_Value;
  int moisture_percentage;
  int br=analogRead(ldrPin);
  if (br < 40){
    umode();
  }
  
  char status;
  Sensor_Value = analogRead(A1);
  moisture_percentage= map(Sensor_Value,512, 201, 0, 100 );
  moisture_percentage= constrain(moisture_percentage, 0, 100);
  if (moisture_percentage >=100){
    lcd.setCursor(13,0);
    lcd.print(" ");
  }

  lcd.setCursor(0,0);
  lcd.print("Moisture : ");
  lcd.print(moisture_percentage);
  lcd.setCursor(14,0);
  lcd.print("%");
  lcd.setCursor(0,1);


  if (moisture_percentage < 40){
    if (mode==0){
      mode0();
    }
    else if (mode==1){
      mode1();
    }
    else if (mode==2){
      mode2();
    }  
    else if (mode==3){
      mode3();
    }      
  }  

  else if (moisture_percentage < 70){
    digitalWrite(relayPin, LOW);
    lcd.setCursor(10,1);
    lcd.print("Normal");
    }  

  else{
    digitalWrite(relayPin, LOW);
    lcd.setCursor(10,1);
    lcd.print("Basah ");
    }
  delay(250);
}