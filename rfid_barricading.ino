#include <Servo.h>


#include <Servo.h>

Servo myservo;  // create servo object to control a servo




#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//int rled = 8;
//int gled = 1;
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance. 
void setup() 
{
  myservo.attach(8);
  SPI.begin();     
  mfrc522.PCD_Init();   
  lcd.begin(16, 2);
  lcd.print("Scan RFID Card");
 // pinMode(rled,OUTPUT);
 // pinMode(gled,OUTPUT);
//  digitalWrite(rled,LOW);
 // digitalWrite(gled,LOW);
  myservo.write(0);
  

}
void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    lcd.setCursor(0, 1);
     lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     lcd.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
lcd.clear();
lcd.begin(16, 2);
 lcd.print("Access: ");
 content.toUpperCase();

//                                 || -------------------- Main -------------------- ||                                (Servo Control)

  if (content.substring(1) == "39 FF F1 15" ) //cards UID
  {
   lcd.setCursor(0,1);
    lcd.print(" Granted");
    delay(500);
  //  digitalWrite(rled,LOW);
    //digitalWrite(gled,HIGH);
    myservo.write(90);
    delay(5000);
   lcd.clear();
    setup();
  }
 
 else   {
  lcd.setCursor(0, 1);
  //digitalWrite(gled,LOW);
  //digitalWrite(rled,HIGH);
    lcd.print(" Denied");
    delay(2000);
     //Door Open
    myservo.write(0);
    delay(3000);
    lcd.clear();
      setup();
      }
} 

/*
  
All Credit OF the Code Goes to
      - Ishan
      
*/
