//Librerias 

//Pantalla LCD
#include <LiquidCrystal.h>

//LiquidCrystal LCD( RS,E,D4,D5,D6,D7);
  LiquidCrystal LCD( 2, 3, 5, 7, 6, 4);

//Servo

#include <Servo.h>
Servo barrera;

//Variables

//led

int rojo = 13;
int verde = 12;

//sensor de distancia
int trig = 9;
int echo = 10;

//otras variables

int duracion;
int distancia;
int peaje = 0;
int llega_auto = 0;
int num1;
  
//////////////////////////////////////

void setup()
{

  //Pantalla LCD
            
    LCD.begin( 16 , 2 );
    LCD.setCursor( 0 , 0 );
  	Serial.begin(9600);
  
  //sensor distancia
  
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  //servo
  
  barrera.attach(8);
  
  //led
  
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  
  //pir
  
  pinMode(11,INPUT);
    
 
}//fin setup


void loop() 
{ 
  //el auto llega 
  //sensor pir 
  
   while(digitalRead(11)== LOW ){
     Serial.println(11);
     llega_auto=0;
     LCD.setCursor(0,0);
     LCD.print("ESPERANDO AUTO");
     delay(1000);
              
 	 }//fin
  
   while(peaje = 1){
    LCD.clear();
    LCD.print("DEBE ABONAR 100");
    delay(1000);
     
 //Evaluamos el momento en el cual recib imos un caracter
 //a través del puerto serie

 	if (Serial.available() > 0) {
 	
 //Se crea una variable que servirá como buffer
      String bufferString1 = "";
      String bufferString2 = "";
 /*
 * Se le indica a Arduino que mientras haya datos
 * disponibles para ser leídos en el puerto serie
 * se mantenga concatenando los caracteres en la
 * variable bufferString
 */  
      delay(1000);
      LCD.clear();  
   while (Serial.available() > 0) {
      bufferString1 += (char)Serial.read();

 }// fin while
   
 //Se transforma el buffer a un número entero
    int num1 = bufferString1.toInt();
    LCD.print("SU PAGO: ");
    LCD.print(num1);
      if (num1>=100) {
        
 		//Se imprime el número que se recibe
 		LCD.setCursor( 0 , 2 );
 		LCD.print("SU VUELTO: ");
 		LCD.print(num1 - 100);
		delay(1000); 
        peaje=0;
        digitalWrite(rojo,LOW);
        digitalWrite(verde,HIGH);
        barrera.write(180);
        LCD.clear();
        LCD.print("AVANCE");
   //barrera 
  // si pago abre la barrera
 //si se alejo entonces cierra barra
   
  //Serial.println(distancia);
  while(distancia<=30)
  {   
    digitalWrite(trig,HIGH);
  delay(1);
  digitalWrite(trig,LOW);
  
  duracion = pulseIn(echo,HIGH);
  distancia = duracion/58.2;
    Serial.print(distancia);
    barrera.write(0);
    digitalWrite(rojo,LOW);
    digitalWrite(verde,HIGH);
    peaje=0;

      }
        digitalWrite(trig,HIGH);
        Serial.print(distancia);
        barrera.write(180);
        digitalWrite(rojo,HIGH);
        digitalWrite(verde,LOW);
        peaje=0;
        
      }//while serial
      }//if serial
   }//while peaje
  
}// fin de loop