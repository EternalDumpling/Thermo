/*
    Written By Joseph Rosw-Provey 2021

    Version 1.0

    Version Notes: Still trying to figure out how to compare card uids agaisnt a scope  
*/
#include <SPI.h>
#include <MFRC522.h>


#define RST_PIN         49          // Configurable
#define SS_PIN          53         // Configurable

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//List of Card UID with names assicoated with them | maybe put in a seperate function with check to fix scope error???



void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);    // Start serial interface with computer
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some boards do need more time after init to be ready
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  mlx.begin();
  
  }

void checktemp() {

  
      lcd.print(mlx.readObjectTempF());

       delay(2000);
      
 /*    lcd.print("Error");
       lcd.setCursor(0,1);
       lcd.print("Temp sensor Failed");

       delay(2000);
       lcd.clear(); */
      


  }

  void cardlookup() {

            String userid;
for (byte i = 0; i < mfrc522.uid.size; i++) {
  userid += String(mfrc522.uid.uidByte[i], HEX);
}
Serial.println(userid );
userid.toUpperCase();
lcd.print(userid);


    lcd.clear();

    

    String tagUIDS[][3] = {
      
      {"31D07BA5", "Jack"}, 
      {"B933389B", "Molly"}
    };

    // finds the length of the tag uids array...
    int len = *(&tagUIDS + 1) - tagUIDS;

    //...then prints to serial 
    Serial.print(len);

    lcd.clear();
    lcd.print("Hello");

    delay(2000);
    loop();
  } 

  void loop() {
    String tagUID = "B933389B";
    
    //probbaly Unnecessary to set to 0,0 but I do for peace of mind
    lcd.setCursor(0,0);
    lcd.print("Please Present ");
    lcd.setCursor(0,1);
    lcd.print("card to sensor");


   //look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }


    
     tone(8,3000.250);
     lcd.clear();
     String tag = "";
 


  
      //cardlookup();
      checktemp();


delay(3000);
    
  }

  
  




    