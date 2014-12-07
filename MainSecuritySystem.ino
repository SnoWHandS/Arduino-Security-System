//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  Libraries
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Keypad.h>                  //Importing Keypad Library      
#include <Wire.h>                    //Importing I2C communication Library
#include <LiquidCrystal_I2C.h>       //Importing LCD library
#include <Password.h>                //Importing Password Libary
#include <SPI.h>                     //Importing SPI Communication Library
#include <MFRC522.h>                 //Importing RFID Reader Library

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  Variables
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------Beginning of Other variables---------------------------------------------------------
Password password = Password("BADDAD");
Password doorPass = Password("ACBA");
boolean alarmActive = false;
boolean passwordEntered = false;
boolean doorPassEntered = false;
boolean alarmSiren = false;
int lockPin = 48;
//---------------------------End of Other variables---------------------------------------------------------------

//---------------------------Beginning of RFID variables---------------------------------------------------------
#define SS_PIN 53                               //Define the SDA pin on the Arduino
#define RST_PIN 49                              //Define the reset pin on the Arduino
boolean cardIsRead = false;                     //True if card has been read, false if not
byte userCard[4];                               //Create a byte array to store user entered Card ID
String validUserCard = "10013811726";           //Create a string to store the the valid user Card ID
MFRC522 rfidReader(SS_PIN, RST_PIN);            //Initialises the RFID reader
//---------------------------End of RFID variables---------------------------------------------------------------

//---------------------------Beginning of Motion Sensor variables---------------------------------------------------------
volatile long previousInterrupt = millis();      //Previous interrupt = the current length the program has been running
volatile long debounceVal = 5;                   //Debounce value of 5 milliseconds
volatile boolean motionDetectedBol = false;      //Boolean to trigger the motion detected output
//---------------------------End of Motion Sensor variables---------------------------------------------------------------

//---------------------------Beginning of Keypad variables--------------------------------------------------------
const byte ROWS = 4;                 //four rows                                                                //
const byte COLS = 4;                 //four columns                                                             //
                                                                                                                //
 //define the cymbols on the buttons of the keypads                                                             //
char hexaKeys[ROWS][COLS] =                                                                                     //
{                                                                                                               //
  {'1','2','3','A'},                                                                                            //
  {'4','5','6','B'},                                                                                            //
  {'7','8','9','C'},                                                                                            //
  {'*','0','#','D'}                                                                                             //
};                                                                                                              //                                                                                                                //
byte rowPins[ROWS] = {23, 25, 27, 29};   //connect to the row pinouts of the keypad                             //
byte colPins[COLS] = {22, 24, 26, 28};   //connect to the column pinouts of the keypad                          //
                                                                                                                //
                                     //initialize an instance of class NewKeypad                                //
                                     // Hexakey array                                                           //
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);                              //
//---------------------------End of Keypad variables--------------------------------------------------------------

//---------------------------Beginning of LCD variables-----------------------------------------------------------
                      //LCD I2C address
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//For carriage manager
int rowCounter = 0;                  //Row selector
int charCounter = 0;                 //Character selecter
//---------------------------End of LCD variables-----------------------------------------------------------------



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  Setup
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
//---------------------------Beginning of LCD Setup--------------------------------------------------------------

   lcd.begin(20,4);                  //Initialise for 20x4 line display
   lcd.backlight();                  //Turn on LCD backlight
   lcd.clear();
   lcdMainScreen(); 

//---------------------------End of LCD Setup--------------------------------------------------------------------   
//---------------------------Beginning of Keypad Setup-----------------------------------------------------------
  
   //Setting Keypad event listener
   customKeypad.addEventListener(keypadEvent);
   //Setting the keypad hold time to 5 seconds
   customKeypad.setHoldTime(1500);
   
//---------------------------End of Keypad Setup-----------------------------------------------------------------   
//---------------------------Beginning of Motion Sensor Setup-----------------------------------------------------------
  pinMode(2, INPUT);
  pinMode(lockPin, OUTPUT);
  attachInterrupt(0, motionDetected, CHANGE);      //Attaches a interupt to pin2 (interrupt pin 4) on Arduino Mega
//---------------------------End of Motion Sensor Setup-----------------------------------------------------------------   

//---------------------------Beginning of RFID Setup-----------------------------------------------------------
  SPI.begin();                          //Beginning the SPI communication to the card reader
  rfidReader.PCD_Init();                //Initialise the RFID reader module
//---------------------------End of RFID Setup-----------------------------------------------------------------   

Serial.begin(9600);
}

void loop()
{                                                                                       
  char keypadInput = customKeypad.getKey();
  checkMotion();
  storeUserCard();
  if(cardIsRead)
  {
    lcdDisplayUserAccessScreen();
  }
  //If there is an input on the keypad
  if(keypadInput)
  {
   //Display that input using lcdKeypadWriter function
   //lcdKeypadWriter( keypadInput );
  }
}
