#include <LiquidCrystal.h>
#include <TimerOne.h>

//Conexiones LCD
LiquidCrystal lcd (23,6,7,8,9,11);

//Resistencia
const int resBtn  = 43; 
boolean resMode = LOW;
int ledRes = 5;
volatile long int timeRes=0;


//Extractor
const int extBtn  = 37; 
boolean extMode = LOW;
int ledExt = 27;
volatile long int timeExt=0;
int right1 = 2;
int left1 = 4;

//Flujo
const int fluBtn  = 33; 
boolean fluMode = LOW;
int ledFlu = 3;
volatile long int timeFlu=0;
int PWMFloatOut = 10;
int right2 = 13;
int left2 = 12;

//Entrada del potenciometro Flujo y Resistencia Manual
float potentiometerReading = 0.0;
float convertPotentiometerReading = 0.0;
float potentiometerReadingRes = 0.0;
float convertPotentiometerReadingRes = 0.0;

void setup() {
  pinMode(resBtn, INPUT);
  pinMode(extBtn, INPUT);
  pinMode(fluBtn, INPUT);
  pinMode(ledRes, OUTPUT);
  pinMode(ledExt, OUTPUT);
  pinMode(ledFlu, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A8, INPUT);

  Timer1.initialize(1000000);      //Configura el TIMER en 1 Segundo
  Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1

  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Bienvenidos");
  lcd.setCursor(0,1);
  lcd.print("Parcial 4");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Brayan Leon");
  lcd.setCursor(0,1);
  lcd.print("Patricia Vidal");
  delay(2000);
  lcd.clear();
}

void loop() {
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    parametros();
    Clear();
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(100);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    parametros();
    Clear();
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(100);
  }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    parametros();
    Clear();
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(100);
  }
  
  // delay at the end of the full loop:
  delay(950);
}

void Temporizador(){
  //Resetea el contador cuando llega a 60 segundos
  if(resMode == HIGH){
    timeRes++;
    if(timeRes>60){
      timeRes=0;
      resMode = LOW;
    }
  }
  if(extMode == HIGH){
    timeExt++;
    if(timeExt>60){
      timeExt=0;
      extMode = LOW;
    }
  }
  if(fluMode == HIGH){
    timeFlu++;
    if(timeFlu>60){
      timeFlu=0;
      fluMode = LOW;
    }
  }
}

void parametros(){
  if(digitalRead(resBtn) == HIGH){
    resMode =! resMode;
  }
  if(digitalRead(extBtn) == HIGH){
    extMode =! extMode;
  }
  if(digitalRead(fluBtn) == HIGH){
    fluMode =! fluMode;
  }
  ActuatorManual();

  //Resistencia
  lcd.setCursor(0,0);
  lcd.print("Res:");
  lcd.setCursor(4,0);
  lcd.print(potentiometerReadingRes);
  lcd.setCursor(0,1);
  lcd.print(timeRes);
  lcd.setCursor(2,1);
  lcd.print("seg");

  //Extractor
  lcd.setCursor(11,0);
  lcd.print("Ext:");
  if(extMode == HIGH){
    lcd.setCursor(15,0);
    lcd.print("Si");
  }
  else{
    lcd.setCursor(15,0);
    lcd.print("No");
  }
  lcd.setCursor(11,1);
  lcd.print(timeExt);
  lcd.setCursor(13,1);
  lcd.print("seg");

  //Flujo
  lcd.setCursor(18,0);
  lcd.print("Flu:");
  lcd.setCursor(22,0);
  lcd.print(potentiometerReading);
  lcd.setCursor(18,1);
  lcd.print(timeFlu);
  lcd.setCursor(20,1);
  lcd.print("seg");
}

void ActuatorManual(){
  if(extMode==HIGH){
    digitalWrite(ledExt, HIGH);
    digitalWrite(right1, LOW);
    digitalWrite(left1, HIGH);
  }
  else{
    digitalWrite(ledExt, LOW);
    digitalWrite(right1, LOW);
    digitalWrite(left1, LOW);
  }
  if(fluMode==HIGH){
    digitalWrite(right2, HIGH);
    digitalWrite(left2, LOW);
    potentiometerReading=analogRead(A4);
    potentiometerReading = potentiometerReading*100/1023;
    convertPotentiometerReading = potentiometerReading*255/100;
    analogWrite(ledFlu, convertPotentiometerReading);
    analogWrite(PWMFloatOut,convertPotentiometerReading);
  }
  else{
    digitalWrite(ledFlu, LOW);
    digitalWrite(right2, LOW);
    digitalWrite(left2, LOW);
    potentiometerReading = 0.00;
    digitalWrite(PWMFloatOut, LOW);
  }
  if (resMode==HIGH){
    potentiometerReadingRes=analogRead(A8);
    potentiometerReadingRes = potentiometerReadingRes*100/1023;
    convertPotentiometerReadingRes = potentiometerReadingRes*255/100;
    analogWrite(ledRes,convertPotentiometerReadingRes);
  }
  else{
    potentiometerReadingRes = 0.00;
    digitalWrite(ledRes, LOW);
  }
}

void Clear(){
  if(timeRes == 60 || timeExt == 60 || timeFlu == 60){
    lcd.clear();
  }
}