//#include "BluetoothSerial.h"
//BluetoothSerial SerialBT;
 

//#include <ESP32Encoder.h>
#define PUSH 12
#define LED 05
#define MOTOR_RIGTH_POSITIVE 16
#define MOTOR_RIGTH_NEGATIVE 17
#define MOTOR_RIGTH_A 34
#define MOTOR_RIGTH_B 35
#define MOTOR_LEFT_POSITIVE 18
#define MOTOR_LEFT_NEGATIVE 04
#define MOTOR_LEFT_A 23
#define MOTOR_LEFT_B 19
#define SPEED 70//55//80

#define CNY_0 36
#define CNY_1 33
#define CNY_2 25
#define CNY_3 26
#define CNY_4 27
#define CNY_5 32
#define CNY_6 39
#define LED_ON 13
#define RANGE 400//400
const String deviceName = "leviatan_esp32";
bool pushState = 0;

int estado = 0;
bool botonPresionado = false;

void setup() {
  // Serial.begin(9600);
  adcAttachPin(CNY_0);
  adcAttachPin(CNY_1);
  adcAttachPin(CNY_2);
  adcAttachPin(CNY_3);
  adcAttachPin(CNY_4);
  adcAttachPin(CNY_5);
  adcAttachPin(CNY_6);
  analogReadResolution(10);
     pinMode(PUSH, INPUT_PULLUP);
  /* Led de control*/
  pinMode(LED, OUTPUT);
  /* Control de encendido de los led emisores*/
  pinMode(LED_ON, OUTPUT);
  digitalWrite(LED_ON, 0);
  /* Motores sin movimiento*/
  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);
    //MANDAR DATOS POR BT A SERIAL DE PC
  //SerialBT.begin(deviceName);
  //Serial.println(deviceName + " está listo para emparejarse");
  while(digitalRead(PUSH)){
}
}
void loop() {
  digitalWrite(LED_ON, 1);
  Serial.println(String(analogRead(CNY_0)) + "-" + String(analogRead(CNY_1)) + "-" + String(analogRead(CNY_2)) + "-" + String(analogRead(CNY_3)) + "-" + String(analogRead(CNY_4)) + "-" + String(analogRead(CNY_5)) + "-" + String(analogRead(CNY_6)));
  int sensor0 = analogRead(CNY_0);
  int sensor6 = analogRead(CNY_6);
  int sensor3 = analogRead(CNY_3);
  int sensor4 = analogRead(CNY_4);
  int sensor2 = analogRead(CNY_2);
  int sensor1 = analogRead(CNY_1);
  int sensor5 = analogRead(CNY_5);
 digitalWrite(LED_ON, 0);
    if (digitalRead(PUSH) == LOW) {
        if (!botonPresionado) {
            botonPresionado = true;
            estado = (estado + 1); // Alterna entre 0, 1 y 2
        }
    } else {
        botonPresionado = false;
    }


    switch (estado) {
        case 0:
            detener(1,1);
            break;
        case 1:
        //MANO IZQUIERDA
                 if (sensor6 < RANGE && sensor4 < RANGE && sensor5 < 800) {
     // SerialBT.println("IZQUIERDA");

      izquierdaRueda();
    } else if (sensor5 >  800 && sensor6 > RANGE|| sensor4>800 && sensor3>800) {
     // SerialBT.println("DERECHA");
      derecha();
    }else if(sensor2 > RANGE && sensor4>RANGE && sensor1 >RANGE && sensor5>RANGE){
    //  SerialBT.println("DERECHA 2");
     derecha();
    } else {
    //  Serial.println("if 11"); SerialBT.println("AVANZAR");
     avanzarCI(sensor4);
    }
            break;
        case 2:
            detener(1,1);
            break;
        case 3:
        //MANO DERECHA
            if (sensor0 < RANGE && sensor2 < RANGE && sensor1 < 800) {
    //      SerialBT.println("DERECHA");
    
          derechaRueda();
        } else if (sensor1 > 800 && sensor0 > RANGE || sensor2 && sensor3>800) {
     //     SerialBT.println("IZQUIERDA");
          izquierda();
          }else if(sensor4 > RANGE && sensor2>RANGE && sensor5>RANGE && sensor1>RANGE ){
        //  SerialBT.println("IZQUIERDA 2");
          izquierda();
    
        } else {
        //  Serial.println("if 11"); SerialBT.println("AVANZAR");
          avanzarCD(sensor2);
        }
            break;
    }
}

void detenerRobot() {
    // Código para detener motores
}

void algoritmoManoIzquierda() {

}

void algoritmoManoDerecha() {
    
}


void avanzarCD(int sensor2) {
  if (sensor2 < RANGE ) {
    avanzarCentrado(SPEED , SPEED * .75);
    
  } else if (sensor2 > RANGE ) {
    avanzarCentrado(SPEED*.75, SPEED );
  } else {
    avanzarCentrado(SPEED, SPEED);
  }
}

void avanzarCI(int sensor4) {
  if (sensor4 < RANGE) {
    //avanzarCentrado(SPEED *.8, SPEED);
 avanzarCentrado(SPEED *.75, SPEED);
  } else if (sensor4 > RANGE) {

   // avanzarCentrado(SPEED, SPEED*.8);
    avanzarCentrado(SPEED, SPEED*.75);
  } else {
    avanzarCentrado(SPEED, SPEED);
  }


}
void izquierdaRueda() {
  /* Motor derecho con movimiento a enfrente*/
  analogWrite(MOTOR_RIGTH_POSITIVE,  0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, SPEED + SPEED * 1.9);
  /* Motor izequierdo con movimiento a enfrente*/
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, SPEED - SPEED * .7);
  //        delay(110);
}

void derechaRueda() {
  /* Motor derecho con movimiento a enfrente*/
  analogWrite(MOTOR_RIGTH_POSITIVE,  0);
  //analogWrite(MOTOR_RIGTH_NEGATIVE, SPEED *0.1);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 70 *0.1);
  /* Motor izquierdo con movimiento a enfrente*/
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  //analogWrite(MOTOR_LEFT_NEGATIVE, SPEED * 0.8);
  analogWrite(MOTOR_LEFT_NEGATIVE, 70 * 1.9);
  //        delay(110);
}

void derecha() {

  analogWrite(MOTOR_RIGTH_POSITIVE, 50);//analogWrite(MOTOR_RIGTH_POSITIVE, 40);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);

  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, 50);
}

void izquierda() {

  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
 analogWrite(MOTOR_RIGTH_NEGATIVE, 45);
  //analogWrite(MOTOR_LEFT_POSITIVE, 40);
  analogWrite(MOTOR_LEFT_POSITIVE, 45);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);
}



void detener(int mIzq, int mDer) {
  analogWrite(MOTOR_RIGTH_POSITIVE, mDer);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);

  analogWrite(MOTOR_LEFT_POSITIVE, mIzq);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);
  delay(100);
}

void avanzarCentrado(int mIzq, int mDer) {
  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, mDer);

  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, mIzq);
}
