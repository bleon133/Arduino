#include <LiquidCrystal.h>    //Libreria pantalla lcd
#include <Keypad.h>           //Libreria teclado

LiquidCrystal lcd (1,2,4,5,6,7);   //Inicializa la lcd
 
const byte rowsCount = 4;          //filas
const byte columsCount = 4;        //Columnas
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};
 
const byte rowPins[rowsCount] = { 11, 10, 9, 8 };
const byte columnPins[columsCount] = { 16, 17, 18, 19 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

char key; //Entrada
double base  =0; //Entrada
double altura=0; //Entrada
double radio =0; //Entrada
double area  =0; //Entrada
char dato[6]={48,48,48,48,48,48}; //Entrada
double valor=0; //Entrada
int pantalla=0; //Entrada

void setup() {
  lcd.begin(16,2);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(12,INPUT);
}

void cambio(){
     if (key == 'A'){
      lcd.clear();
      valor=0;
      dato[0]=48;
      dato[1]=48;
      dato[2]=48;
      dato[3]=48;
      dato[4]=48;
      dato[5]=48;
      pantalla++;
      area=0;
    }
}

void numero(){

  if ( key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#' && key != 0){
    dato[0]=dato[1];
    dato[1]=dato[2];
    dato[2]=dato[3];
    dato[3]=dato[4];
    dato[4]=dato[5];
    dato[5]=key;
    valor=(dato[0]-48)*100000+(dato[1]-48)*10000+(dato[2]-48)*1000+(dato[3]-48)*100+(dato[4]-48)*10+(dato[5]-48);    
  }
}

void triangulo(){
  cambio();
  if (pantalla>3){
    pantalla=0;
  }
  if (pantalla==1){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Valor Base"); //Salida
    numero();
    base=valor;
    lcd.setCursor(0,1);
    lcd.print(base);    
  }
  if (pantalla==2){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Valor Altura"); //Salida
    numero();
    altura=valor;
    lcd.setCursor(0,1);
    lcd.print(altura);    
  }
  if (pantalla==3){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("El area es:"); //Salida
    area= (base*altura)/2; //Proceso
    lcd.setCursor(0,1);
    lcd.print(area);    
  }
}

void cuadrado(){
  cambio();
  if (pantalla>7){
    pantalla=0;
  }
  if (pantalla==5){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Valor Base");
    numero();
    base=valor;
    lcd.setCursor(0,1);
    lcd.print(base);    
  }
  if (pantalla==6){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Valor Altura"); //Salida
    numero();
    altura=valor;
    lcd.setCursor(0,1);
    lcd.print(altura);    
  }
  if (pantalla==7){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("El area es:"); //Salida
    area= base*altura;
    lcd.setCursor(0,1);
    lcd.print(area);    
  }
}

void circulo(){
   cambio();
  if (pantalla>10){
    pantalla=0;
  }
  if (pantalla==9){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Valor radio"); //Entrada
    numero();
    radio=valor;
    lcd.setCursor(0,1);
    lcd.print(radio); //Salida    
  }
  if (pantalla==10){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("El area es"); //Salida
    area=(3.141592)*radio*radio; //Proceso
    lcd.setCursor(0,1);
    lcd.print(area); //Salida    
  }
}

void loop() {
   key = keypad.getKey();
   delay(50);
      
   if (pantalla==0){
    lcd.setCursor(0,0);
    lcd.write("Elige una figura"); //Salida
    lcd.setCursor(0,1);
    lcd.write("B:TR C:CU D:CI"); //Salida
   } 
    
   if (key=='B'){
     lcd.clear();
     pantalla=1;
   }    
    if (pantalla<=3 && pantalla>=1){
      triangulo();
    }

   if (key=='C'){
     lcd.clear();
     pantalla=5;
   }    
    if (pantalla<=7 && pantalla>=5){
      cuadrado();
    }

    if (key=='D'){
     lcd.clear();
     pantalla=9;
   }    
    if (pantalla<=10 && pantalla>=9){
      circulo();
    }
}
