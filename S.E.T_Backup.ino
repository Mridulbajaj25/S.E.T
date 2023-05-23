#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
byte accessUID[4] = {0x53, 0x57, 0x2D, 0x13};
byte ACCESSUID[4] = {0xC3, 0xAB, 0x26, 0x0C};

void setup() {
  pinMode (8,OUTPUT);    //g
  pinMode (7,OUTPUT);    //r
  pinMode (6,OUTPUT);    //g
  pinMode (5,OUTPUT);    //r
  pinMode (4,OUTPUT);    //g
  pinMode (3,OUTPUT);    //r
  pinMode (2,OUTPUT);    //g
  pinMode (A0,OUTPUT);    //r
  Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);       // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  delay(4);              // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
}

void loop() {

  

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  
   return (0);
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return (0);
  }
 
  // Dump debug info about the card; PICC_HaltA() is automatically called
  if (mfrc522.uid.uidByte[0] == accessUID[0] && mfrc522.uid.uidByte[1] == accessUID[1] && mfrc522.uid.uidByte[2] == accessUID[2] && mfrc522.uid.uidByte[3] == accessUID[3] ){
   Serial.println("Access Granted");
         
  digitalWrite (4,HIGH);
  digitalWrite (5,HIGH);
  digitalWrite (7,HIGH);
  digitalWrite (A0,HIGH);
  digitalWrite (8, LOW);
  digitalWrite (6, LOW);
   digitalWrite (3, LOW);
   digitalWrite (2, LOW);
   
    
 }else {
   Serial.println("Access Denied");
  }
 if (mfrc522.uid.uidByte[0] == ACCESSUID[0] && mfrc522.uid.uidByte[1] == ACCESSUID[1] && mfrc522.uid.uidByte[2] == ACCESSUID[2] && mfrc522.uid.uidByte[3] == ACCESSUID[3] ){
   Serial.println("Access Granted");

    digitalWrite (8,HIGH);
  digitalWrite (5,HIGH);
  digitalWrite (3,HIGH);
  digitalWrite (A0,HIGH);
   digitalWrite (2, LOW);
   digitalWrite (7, LOW);
   digitalWrite (4, LOW);
  
  delay(4000);

   digitalWrite (6,HIGH);
  digitalWrite (7,HIGH);
  digitalWrite (3,HIGH);
  digitalWrite (A0,HIGH);
  digitalWrite (5, LOW);
  digitalWrite (8, LOW);
  digitalWrite (4, LOW);
  delay(4000);

   digitalWrite (4,HIGH);
  digitalWrite (5,HIGH);
  digitalWrite (7,HIGH);
  digitalWrite (A0,HIGH);
  digitalWrite (8, LOW);
  digitalWrite (6, LOW);
   digitalWrite (3, LOW);
  
  delay(4000);

   digitalWrite (2,HIGH);
  digitalWrite (5,HIGH);
  digitalWrite (3,HIGH);
  digitalWrite (7,HIGH);
  digitalWrite (4, LOW);
  digitalWrite (A0, LOW);
    
}  else {
   Serial.println("Access Denied");
  }
  
 

  mfrc522.PICC_HaltA();
}
