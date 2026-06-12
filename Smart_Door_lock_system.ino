
//------------------SERVO-------------------------------------------------------------------------------------------------------//

#include <Servo.h>
Servo myServo;
int servoPin = 7;
float angle;
int servoDelay = 100;


//--------------------------RC522--------------------------------------------------------------------------------------------------//

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte id[4];
byte allowed[4] = {0x73, 0xEB, 0x40, 0x11};


//------------------------BUZZ---------------------------------------------------------------------------------------------------//

int Buzzpin = 6;
int Buzz_grantedDelay = 100;
int Buzz_deniedDelay = 1000;



//-------------------------------LEDs--------------------------------------------------------------------------------------------//

int greenLED = 4;
int redLED = 5;




//---------------------------SETUP---------------------------------------------------------------------------------------------------//

void setup() {
  Serial.begin(9600);
  
  //SERVO
 myServo.attach(servoPin);
 myServo.write(180);

 //RC522
  mfrc522.PCD_Init();
  SPI.begin();

  //BUZZ
  pinMode(Buzzpin, OUTPUT);

  //LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

}


//-------------------LOOP-------------------------------------------------------------------------------------------------------------//

void loop() {


 //--------------------------RC522 CODE------------------------------------------------------------------------------------------//

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  for (byte i = 0; i < 4; i++) {
    id[i] = mfrc522.uid.uidByte[i];
  }

  bool match = true;

  for (byte i = 0; i < 4; i++) {
    if (id[i] != allowed[i]) {
      match = false;
    }
  }

  if (match) {
    Serial.println("Access Granted");
  } else {
    Serial.println("Access Denied");
  }

  mfrc522.PICC_HaltA();

//-------------------------------------IF ACCESS GRANTED-------------------------------------------------------------------------------------------//


if(match){

//----------GREEN LED-------

  digitalWrite(greenLED, HIGH);


//--------BUZZ-----------------

  digitalWrite(Buzzpin,HIGH);
    delay(Buzz_grantedDelay);
  digitalWrite(Buzzpin,LOW);
    delay(Buzz_grantedDelay);

  digitalWrite(Buzzpin,HIGH);
    delay(Buzz_grantedDelay);
  digitalWrite(Buzzpin,LOW);
    delay(Buzz_grantedDelay);



 //-----------SERVO MOVEMENT-------

  for(int i=180; i>90; i--) {
  myServo.write(i);
  delay(servoDelay);
  
  }

  digitalWrite(greenLED, LOW);


}else{

//----------------------------------IF ACCESS DENIED-----------------------------------------------------------------------------------------------


//-----------RED LED------------------

  digitalWrite(redLED, HIGH);


//-----------BUZZ------------------

  digitalWrite(Buzzpin,HIGH);
    delay(Buzz_deniedDelay);
  digitalWrite(Buzzpin,LOW);
    delay(Buzz_deniedDelay);

  digitalWrite(Buzzpin,HIGH);
    delay(Buzz_deniedDelay);
  digitalWrite(Buzzpin,LOW);
    delay(Buzz_deniedDelay);


  digitalWrite(redLED, LOW);


}





















}