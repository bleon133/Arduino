  //HOLA MUNDO
void setup() {
  pinMode(13, OUTPUT);  //DECLARAMOS EL PIN 13 COMO SALIDA

}
void loop() {
  digitalWrite(13, HIGH); // ENCENDEMOS EL LED DEL PIN 13  
  delay(500);             // se encendera el pin 13 poe un tiempo 500 milisegundos
  digitalWrite(13, LOW);  //apagamos el led
  delay(500);             //se apagara el led por un tiempo del 500 milisegundos
  
}
