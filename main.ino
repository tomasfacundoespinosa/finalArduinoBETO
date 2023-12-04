#include <SoftwareSerial.h> //libreria modulobt

SoftwareSerial bluetooth(6, 7); // RX (pin 6) y TX (pin 7)
// Definimos pines para el sensor de color TCS3200
int S0 = 8;
int S1 = 9;
int S2 = 10;
int S3 = 11;
int salidaTCS = 12;
//definicion de pines de los motores
const int IN1 = A1;
const int IN2 = A0;
const int IN3 = 2;
const int IN4 = 3;

//definicion de movimientos
void Avanzar();
void GirarDER();
void GirarIZQ();
void giro180();
void Parar();
void LeerColores();
void marchaAtras();   
void GirarDERa();

// Variables booleanas para representar el estado de los colores
bool BLANCO_COLOR = false;
bool NEGRO_COLOR = false;
bool ROJO_COLOR = false;
bool AZUL_COLOR = false;
bool VERDE_COLOR = false;
bool AMARILLO_COLOR = false;
bool VIOLETA_COLOR = false;

void setup() {
  // Inicialización de la comunicación Bluetooth a 9600 bps
  bluetooth.begin(9600); 
  //setup de sensor rgb  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(salidaTCS, INPUT);

  //setup de motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuración del sensor de color TCS3200
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Inicialización de la comunicación serial para la depuración
  Serial.begin(9600); 
}

//definicion de  los movimientos que puede hacer el robot

void GirarDER() {
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
}

void GirarDERa(){
   digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
}

void GirarIZQ() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
}

void marchaAtras(){
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void Avanzar() {
    GirarDER();
    GirarIZQ();
}

void Parar() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
}

void giro180(){
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
}

// Leer los valores de los colores del sensor TCS3200
void LeerColores() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int azul = pulseIn(salidaTCS, LOW);
    delay(100);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    int verde = pulseIn(salidaTCS, LOW);
    delay(100);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int rojo = pulseIn(salidaTCS, LOW);
    delay(100);

    // Mostrar los valores de los colores en la consola
    Serial.print("R:");
    Serial.print(rojo);

    Serial.print("\t");

    Serial.print("V:");
    Serial.print(verde);

    Serial.print("\t");

    Serial.print("A:");
    Serial.println(azul);

    //definicion de colores
    BLANCO_COLOR = (rojo >= 0 && rojo <= 0 && verde >= 0 && verde <= 0 && azul >= 0 && azul <= 0);
    NEGRO_COLOR = (rojo >= 0 && rojo <= 0 && verde >= 0 && verde <= 0 && azul >= 0 && azul <= 0);
    ROJO_COLOR = (rojo >= 130 && rojo <= 160 && verde >= 30 and verde <= 60 && azul >=60 && azul <= 90);
    AZUL_COLOR = (rojo >= 20 && rojo <= 50 && verde >= 10 && verde <= 30 && azul >= 80 && azul <= 110);
    VERDE_COLOR = (rojo >= 55 && rojo <= 85 && verde >= 15 && verde <= 30 && azul >= 50 && azul <= 90);
    AMARILLO_COLOR = (rojo >= 100 && rojo <= 130 and verde >= 15 && verde <= 35 && azul >= 40 && azul <= 65);
    VIOLETA_COLOR = (rojo >= 45 && rojo <= 70 && verde >= 25 && verde <= 40 && azul >= 105 && azul <= 130);
}

//definimos c
byte c = 0;
  
void loop() {

  if (bluetooth.available()) {
    c = bluetooth.read();
  }
  
  if (c == '1') {

    while(true){
    
    LeerColores();

    while(!AZUL_COLOR && !VERDE_COLOR && !ROJO_COLOR && !VIOLETA_COLOR && !AMARILLO_COLOR){
      LeerColores();
      Avanzar();
    } 
      if(VERDE_COLOR){
      Parar();
      delay(1000);
      marchaAtras();
      delay(500);
      Parar();
      delay(500);
      GirarDERa();
      delay(800);
      Avanzar();
      delay(300);
      GirarDERa();
      delay(1600);
      Parar();
      delay(1000);
    }

    if(!AMARILLO_COLOR){
      Avanzar();
    } else{
      Parar();
      break;
    }
    }

    c = 0;

  }

  if (c == '2') {

    while(true){
    
    LeerColores();

    while(!AZUL_COLOR && !VERDE_COLOR && !ROJO_COLOR && !VIOLETA_COLOR && !AMARILLO_COLOR){
      LeerColores();
      Avanzar();
    } 
      if(AZUL_COLOR){
      Parar();
      delay(1000);
      marchaAtras();
      delay(500);
      Parar();
      delay(500);
      GirarDERa();
      delay(800);
      Avanzar();
      delay(300);
      GirarDERa();
      delay(1600);
      Parar();
      delay(1000);
    }

    if(!AMARILLO_COLOR){
      Avanzar();
    } else{
      Parar();
      break;
    }
    }

    c = 0;
    
  }

  if (c == '3') {

    while(true){
    
    LeerColores();

    while(!AZUL_COLOR && !VERDE_COLOR && !ROJO_COLOR && !VIOLETA_COLOR && !AMARILLO_COLOR){
      LeerColores();
      Avanzar();
    } 
      if(ROJO_COLOR){
      Parar();
      delay(1000);
      marchaAtras();
      delay(500);
      Parar();
      delay(500);
      GirarDERa();
      delay(800);
      Avanzar();
      delay(300);
      GirarDERa();
      delay(1600);
      Parar();
      delay(1000);
    }

    if(!AMARILLO_COLOR){
      Avanzar();
    } else{
      Parar();
      break;
    }
    }

    c = 0;

  }

}