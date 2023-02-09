#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <Wire.h>

int Time=0;
int i = 0;
int fc = 0;

//variables lcd

LiquidCrystal lcd(8,9,10,11,12,13);

//frecuencia cardíaca, contador y temporizador
void setup() {
  lcd.begin(16,2);
  lcd.clear();
  //Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  fc = Wire.read();
  Time = Wire.read();
  delay(100);
}
void loop() {
  lcd.setCursor(0,0);
  lcd.print("Frec. cardiaca");
  lcd.setCursor(0,1);
  lcd.print(fc);
  lcd.setCursor(4,1);
  lcd.print(" ppm");
  lcd.setCursor(10,1);
  lcd.print(Time);
  lcd.setCursor(13,1);
  lcd.print(" s");
  limpieza();
}

void limpieza(){
  if(Time==61){
    lcd.clear();
  }
}
