#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define sensA 6       //pin donde va a estar el sensor A
#define sensB 7       //pin donde va a estar el sensor B
#define BUZZER 13     //pin donde va a estar el buzzer
#define BOTONS 9      //pin donde va a estar el boton que resta
#define BOTONR 8      //pin donde va a estar el boton que resta
#define BOTONOK 10    //pin donde va a estar el boton para entrar y salir al modo de seteo de variable "variable"


int     limite =5;      //variable para definir el limite de vueltas
int     vueltas = 0;    //variable en donde se va a guardar la cantidad de vueltas efectuadas por el usuario
bool    varA  = 0;      
bool    varB  = 0;
bool    flagA = 0;
bool    flagB = 0;
bool    presentacion  = 1;  //flag para activar la presentacion  
bool    botons=0;
bool    botonr=0;
bool    botonOK=0;
bool    setvueltas  = 1;    //flag para activa el menu para variar el limite de vueltas


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(sensA ,INPUT);
  pinMode(sensB ,INPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BOTONS, INPUT);
  pinMode(BOTONR, INPUT);

  digitalWrite(BUZZER, HIGH);
  
}

void loop() {
//PRESENTACION-----------------------------------------------------------------------------------------------------------------------------------

  if( presentacion == 1){
    lcd.print(" CUENTA VUELTAS");
    delay(1500);
    presentacion = 0;
    lcd.clear();
  }
//SETEO-------------------------------------------------------------------------------------------------------------------------------------------

  while( setvueltas == 1){
  
    botons = digitalRead(BOTONS);     //leemos el boton de suma
    botonr = digitalRead(BOTONR);     //leemos el boton de resta
    botonOK = digitalRead(BOTONOK);   //leemos es boton de OK
    lcd.setCursor(0,1);
    lcd.print(limite);
      if ( setvueltas == 1){
        lcd.setCursor(0,0);
        lcd.print("INGRESE MAX");
      }
                if (botons == 1){
                  limite= limite +5;
                  delay(20);
                  lcd.clear();
                }
              
                if (botonr == 1){
                  limite= limite -5;
                  delay(20);
                  lcd.clear();
                }

    if (botonOK == 1){
      delay(500);
      setvueltas=0;
      lcd.clear();
    break;

    }
  }


//SENSORES--------------------------------------------------------------------------------------------------------------------------------------------------
  
  varA = digitalRead(sensA);
  varB = digitalRead(sensB);
  botonOK = digitalRead(BOTONOK);

  
  lcd.setCursor(0,0);
  lcd.print(vueltas);
  lcd.setCursor(0,1);
  lcd.print(limite);


  if (botonOK == 1){
    setvueltas = 1;
    delay (500);
  }
  if (varA == 0){
      flagA = 1;
      if (flagB == 1){
          vueltas ++;
          flagA=0;
          flagB=0;
          delay(200);
          lcd.clear();
      
      }
  }
  if (varB == 0){
      flagB = 1;
      if (flagA == 1){
          vueltas --;
          flagA=0;
          flagB=0;
          delay(200);
          lcd.clear();
      
      }
  }
  /*if (limite == vueltas){
    digitalWrite(BUZZER, LOW); //
  }   */                         // 
                               //
  if (limite <= vueltas){       // SE PUEDEN CAMBIAR LOS HIGH POR LOW PARA CONECTAR EL BUZZER/LED (DEPENDE DONDE SE CONECTE EL PITUTO) 
    digitalWrite(BUZZER, LOW);//
  }                            //
  if (limite > vueltas){       //
    digitalWrite(BUZZER, HIGH);//
  }
}
  
