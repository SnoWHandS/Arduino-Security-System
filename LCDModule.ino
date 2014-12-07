

//---------------------------Beginning of LCD menu prompts----------------------------------------
void lcdMainScreen()
{
  lcd.clear();
   lcdWrite("Heald Security v1.1",0,0);
   if(alarmActive)
   {
    lcdWrite("Alarm Active!",0,2);
    lcdWrite("Hold * to disable",0,1);
   }
   else
   {
    lcdWrite("Hold * to arm",0,1);
    lcdWrite("Hold # to Unlock",0,2);  
   }
}

void lcdResetScreen()
{
 lcd.clear();
  lcdWrite("All inputs reset!",0,1);
  delay(1500);
 lcdMainScreen(); 
}

void lcdDoorPassScreen()
{
   lcd.clear();
    lcdWrite("Enter Password:",0,0);
    lcdWrite("Hold # to confirm",0,2);
}

void lcdDisplayUserAccessScreen()
{
  lcd.clear();
  if(stringUserCard() == validUserCard)
  {
     lcdWrite("Welcome user:", 0, 0);
     lcdWrite(stringUserCard(), 3, 1);
     lcdWrite("ACCESS GRANTED", 2, 2);
     unlockDoor();
  }
  else
  {
     lcdWrite("Invalid user:", 0, 0);
     lcdWrite(stringUserCard(), 3, 1);
     lcdWrite("ACCESS DENIED", 2, 2);
     delay(1500);
  }
   lcdMainScreen();
}

void lcdStartupPrompt()
{
  lcd.clear();
   lcdWrite("Enter * for Clear", 0, 0);
   lcdWrite("Enter # for Space", 0, 1);
   lcdWrite("Enter code followed", 0, 2);
   lcdWrite("by * to begin test", 0, 3); 
}

void lcdDoorUnlocked()
{
   lcdWrite("Door Unlocked",3,1); 
}

void lcdPassIncorrectScreen()
{
 lcd.clear();
   lcdPrintln("False Try again!"); 
}

void lcdPasswordScreen()
{
   lcd.clear();
    lcdWrite("Enter password:",0,0);
    lcdWrite("Hold * to confirm",0,2);
}

void lcdPasswordCorrectScreen()
{
  if(alarmActive)                //Verifying if password is correct
  {
   lcdWrite("Correct!", 6, 1);
   delay(1500);
   lcdMainScreen();
  }
  else
  {
     lcdWrite("Deactivated",3,1);
     delay(1500);
     lcdMainScreen();  
  }
}

//---------------------------End of LCD menu prompts----------------------------------------------

//---------------------------Beginning of LCD Functions-------------------------------------------

//For printing a continous string of 80 characters or less
void lcdPrintln(String input)
{
  if(input.length() <= 80)
  { 
    String line0 = input.substring(0, 20);
    String line1 = input.substring(20, 40);
    String line2 = input.substring(40, 60);
    String line3 = input.substring(60, 80);
    
    if(input.length() > 0)
    {
      lcdWrite(line0,0,0);                //Write line 0 if input length larger than 0
      if(input.length() > 20)
      {
       lcdWrite(line1,0,1);               //Write line 1 if input length larger than 20
       if(input.length() > 40)
       {
         lcdWrite(line2,0,2);             //Write line 2 if input length larger than 40
         if(input.length() > 60)
         {
           lcdWrite(line3,0,3);           //Write line 3 if input length larger than 60
         }
       }
      }   
    }
  }
  else
  {            
     lcdWrite("cant fit string",0,0);  
  }
}

//For printing to a specific line & character on the LCD
void lcdWrite(String input, int lineNo, int rowNo)
{
 lcd.setCursor(lineNo, rowNo);
 lcd.print(input); 
}

void lcdKeypadWriter(char input)
{
 lcdWrite((String)input, charCounter, rowCounter);
 carriageManager(input);
}

void lcdClearLine(int lineNo)
{
 lcdWrite("                    ",0, lineNo);
}

//For managing the carriage location on the LCD
void carriageManager(char customKey)
{
  //If there is a key pressed
  if(customKey)       
  {
    //Increment character counter
    charCounter++;
    //If the character counter is greater than 19
    if(charCounter > 19)
    {
     //Reset the character counter
     charCounter = 0;
     //Increment the row counter
     rowCounter++;
    }
    //If the row counter is greater than 3
    if(rowCounter > 3)
    {
     //Reset the row counter
     rowCounter = 0;
     //Clear the LCD
     lcd.clear();
    }
  }
}
//---------------------------End of LCD Functions-------------------------------------------------
