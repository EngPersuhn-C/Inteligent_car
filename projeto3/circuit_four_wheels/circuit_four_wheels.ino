#include <NewPing.h> //Ping Library
#include <AFMotor.h> //Adafruit Motor Shield

#define TRIGGER_PIN_1 A1
#define ECHO_PIN_1 A0
#define TRIGGER_PIN_2 A3
#define ECHO_PIN_2 A5
#define MAX_DISTANCE 200

int magnetic_sensor = 3; //Digitar port
int magnetic_sensor_value = 1; //Value
int start = 1; //Value to init execution
int dist_sensor_1; //Variable
int dist_sensor_2; //Variable

NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); //Protoboard vermelha
NewPing sonar_2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); //Protoborad amarela

  AF_DCMotor  motorFL(1);
  AF_DCMotor  motorFR(4);
  AF_DCMotor  motorBL(2);
  AF_DCMotor  motorBR(3);

void setup() {
  
  // VELOCIDADE DOS MOTORES
  motorFR.setSpeed(255);
  motorBR.setSpeed(255);
  motorFL.setSpeed(255);
  motorBL.setSpeed(255);

  // INICIAM PARADOS
  motorFR.run(RELEASE);
  motorBR.run(RELEASE);
  motorFL.run(RELEASE);
  motorBL.run(RELEASE);

}

void loop() {

  endExecution(); //Verifica se chegou na origem após rodar o circuito todo
  firstExecution(); //Inicia o ciclo dando direção ao veículo

  dist_sensor_1 = sonar_1.ping_cm(); //Protoboard vermelha
  dist_sensor_2 = sonar_2.ping_cm(); //Protoboard amarela
  
  distance_correction();
  

//*****SE NÃO ENCONTRAR NADA A 15 CM DOS SENSORES, ENTÃO ANDA*****
  if(dist_sensor_1 > 10 && dist_sensor_2 > 10){
    
    moveForward();
  
  }
//****************************************************************

  else{

    halt(); //"Livra" os motores
    delay(10); //Delay para não ocorrer dois comandos simultaneamente
    moveBackward(); //Se move para trás
    delay(500);
    halt(); //"Livra" os motores
    
    int dist_difference = dist_sensor_1 - dist_sensor_2; //Calcula qual sensor possui um obstáculo em menor distância

    if(dist_difference > 5){ //Nesse caso, o objeto está mais próximo do lado esquerdo.

      moveLeft(); //Se move para a direita
      delay(1000);
      halt(); //"Livra" os motores

    }

    else if(dist_difference < -5){ //Nesse caso, o objeto está mais próximo do lado direito

      moveRight(); //Se move para a esquerda
      delay(1000);
      halt(); //"Livra" os motores
      delay(10);

    }

    else{ //Nesse caso, há obstáculo nos dois sensores apresentando risco de colisão (QUINAS)

      moveBackward(); //Move-se para trás
      delay(500);
      halt(); //"Livra" os motores
      delay(10);
      moveRight(); //Move-se para a esquerda
      delay(2000);
      halt(); //"Livra" os motores
      delay(10);
      
    }

  }

}

  void firstExecution() {

    if(magnetic_sensor_value == 1 && start == 1){

      moveRight();
      delay(1500);
      halt();

    }

    magnetic_sensor_value = 0;
    start = 0;

  }

  void endExecution() {

    if(magnetic_sensor_value == 1 && start != 1){

      //ESTACIONA O VEÍCULO NA ORIGEM
      //NECESSÁRIO TESTAR NO CIRCUITO O TEMPO PERFEITO DE CADA MANOBRA

    }

  }

  void moveForward() {
 
    motorBL.run(FORWARD);
    motorFL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFR.run(FORWARD);
    
  }

  void moveBackward() {
    motorBL.run(BACKWARD);
    motorFL.run(BACKWARD);
    motorBR.run(BACKWARD);
    motorFR.run(BACKWARD);
  }

  void moveRight() { //Acelera rodas direitas
    motorBL.run(RELEASE);
    motorFL.run(RELEASE);
    motorBR.run(FORWARD);
    motorFR.run(FORWARD);
  }

  void moveLeft() { //Acelera rodas esquerdas
    motorBR.run(RELEASE);
    motorFR.run(RELEASE);
    motorBL.run(FORWARD);
    motorFL.run(FORWARD);
  }

  void halt() {
    motorBL.run(RELEASE);
    motorBR.run(RELEASE);
    motorFL.run(RELEASE);
    motorFR.run(RELEASE);
  }

  void distance_correction() {

    //*****CASO NÃO LEIA NADA À SUA FRENTE, A DISTÂNCIA É "INFINITA"*****
    if(dist_sensor_1 == 0){

      dist_sensor_1 = 1000;

    }

    if(dist_sensor_2 == 0){

      dist_sensor_2 = 1000;

    }
    //*******************************************************************

  }