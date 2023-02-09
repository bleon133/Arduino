#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <Wire.h>
//variables de pausador de emergencia

int LED = 4;
int pulsador = 2;

// estado del pulsador

volatile int estado = HIGH;
volatile int estadoAnterior = HIGH;

//Variables frecuencia

int pin = 3;
volatile long int Time=0;
volatile unsigned int i = 0;
volatile unsigned int fc = 0;


//variables lcd

LiquidCrystal lcd(8,9,10,11,12,13);

//frecuencia cardíaca, contador y temporizador
void setup() {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin),incremento,RISING);
  Timer1.initialize(1000000);      //Configura el TIMER en 1 Segundo
  Timer1.attachInterrupt(Temporizador) ; //Configura la interrupción del Timer 1
  lcd.begin(16,2);
  lcd.clear();
  Wire.begin();

// parada de emergencia
  pinMode (LED, OUTPUT); //lED
  pinMode (pulsador, INPUT); //BOTON
  attachInterrupt(digitalPinToInterrupt(pulsador), manejadorPulsador, RISING);
  digitalWrite(LED, estado);
}

void incremento(){
  i++;
}

void manejadorPulsador (){ //lo que quiero que ocurra cuando se presione el pulsador
  estado =!estado;
}

void loop() {
  pantalla();
  if (estado == HIGH){
    if(Time==61){
      i = 0;
    }
  } 
  else {
    i=0;
    fc=0;
    Time=0;
  }
  
  // LED
  digitalWrite(LED, estado);
  limpieza();
  comunicacion();
}

void Temporizador(){
  Time++;
  //Resetea el contador cuando llega a 60 segundos
  if(Time==60){
    fc = i;
  }
  if(Time>61){
    Time=0;
    lcd.setCursor(11,1);
    lcd.print("0");
  }
}

void pantalla(){
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
}

void limpieza(){
  if(Time==61 || estado != estadoAnterior){
    lcd.clear();
    estadoAnterior = estado;
  }
}

void comunicacion(){
  Wire.beginTransmission(9);
  Wire.write(fc);
  Wire.write(Time);
  Wire.endTransmission();
  delay(100);
}


