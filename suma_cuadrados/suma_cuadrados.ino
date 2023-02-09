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
int Num=0; //Entrada
int Resultado=0; //Entrada
char dato[6]={48,48,48,48,48,48}; //Entrada
int valor=0; //Entrada
int pantalla=0; //Entrada

void setup() {
  lcd.begin(16,2);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(12,INPUT);
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

void loop() {
   key = keypad.getKey();
   delay(80);
   
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
      Resultado=0;
    }
    
    if (pantalla>2){
        pantalla=0;
      }

   if (pantalla==0){ //Cambio de pantalla
    lcd.setCursor(0,0);
    lcd.write("Numero"); //Imprimir
    numero();
    Num=valor;
    lcd.setCursor(0,1);
    lcd.print(Num); //Imprimir
   }

   if (pantalla==1){ //Cambio de pantalla
    for (int i=0; i<=Num;i++){ //proceso
      Resultado = Resultado + i*i; //proceso
    }
    pantalla++;
   }
   
   if (pantalla==2){ //Cambio de pantalla 
    lcd.setCursor(0,0);
    lcd.write("El resultado es:"); //Imprimir
    lcd.setCursor(0,1); 
    lcd.print(Resultado); //Imprimir
   }  
}
