
#include <Wire.h>
#include <SPI.h> 
#include <MFRC522.h> 
#include <SoftwareSerial.h>



#define SS_PIN 10 
#define RST_PIN 9
#define pinPIR 7

 
MFRC522 rfid(SS_PIN, RST_PIN);

int pinoLedVerde = 3; 
int pinoLedVermelho = 2; 
const int pinoRX = 0; 
const int pinoTX = 1; 
const int pinoLed = 2; 
int dadoBluetooth = 0; 
boolean loopLED = false; 
const char* mqtt_server = "http://127.0.0.1:1883/"; 



void setup(){
 
  Wire.begin(); 
  SPI.begin(); 
  rfid.PCD_Init();
  
  pinMode(pinPIR, INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$"); 
  bluetooth.print("$"); 
  bluetooth.print("$"); 
  delay(100); 
  pinMode(pinoLed, OUTPUT);
  Serial.println("Trava eletronica");
  Serial.println("Aproxime do leitor");
  pinMode(pinoLedVerde, OUTPUT);
  pinMode(pinoLedVermelho, OUTPUT);
  digitalWrite(pinoLedVerde, LOW); 
  digitalWrite(pinoLedVermelho, LOW); 


}

 
 
void loop() {
  leituraRfid();

  bool valorPIR = digitalRead(pinPIR);
   if (valorPIR) {
     Serial.print("DETECTADO");
  }  

   
}

void leituraRfid(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) 
    return;
 
  
  String strID = ""; 
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  
  strID.toUpperCase();

  if (strID.indexOf ("5C:B3:CD:22" && "DA 1C 49 19")) {
        
    digitalWrite(pinoLedVerde, HIGH);
    delay(500); 
    digitalWrite(pinoLedVerde, LOW); 
  }else{ 
          
   digitalWrite(pinoLedVermelho, HIGH);
   delay(500); 
   digitalWrite(pinoLedVermelho,LOW);
    }
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1(); 
  } 



 
