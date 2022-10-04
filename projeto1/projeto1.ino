#include <NewPing.h>
#include <AFMotor.h> //Adafruit Motor Shield


#define TRIGGER_PIN_1 A1
#define ECHO_PIN_1 A0
#define TRIGGER_PIN_2 A3
#define ECHO_PIN_2 A2
#define MAX_DISTANCE 200

NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar_2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

  AF_DCMotor  motorFL(1);
  AF_DCMotor  motorFR(4);
  AF_DCMotor  motorBL(2);
  AF_DCMotor  motorBR(3);

int ativa = 0;

void setup() {

  delay(2000);
  
  Serial.begin(115200);
  
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
  
  if(sonar_1.ping_cm() > 20 || sonar_1.ping_cm() == 0){
    
   moveForward();
  
  }

    
  else{
    halt();
    moveBackward();
    delay(1000); 
    moveRight();
    delay(800);
    halt();
    
  }

   if(sonar_2.ping_cm() > 20 || sonar_2.ping_cm() == 0){
    
   moveForward();
  
  }
  
  else{

    halt();
    moveBackward();
    delay(1000); 
    moveLeft();
    delay(800);
    halt();
    
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

  void moveRight() {
    motorBL.run(RELEASE);
    motorFL.run(RELEASE);
    motorBR.run(FORWARD);
    motorFR.run(FORWARD);
  }

  void moveLeft() {
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

  void twooccuped(){
    halt();
    delay(100);
    moveBackward();
    delay(2000);
    halt();
  }