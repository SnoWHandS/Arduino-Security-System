void checkPassword()                      //For checking the alarm password
{
  if(password.evaluate())                    //If password is correct
 {
   if(!alarmActive)                            //If the alarm has not been set and password correct
   {
     alarmActive = true;                         //Set alarm system active
     charCounter = 0;                            //Clear char counter buffer
     lcdPasswordCorrectScreen();                 //Display user message
   }
   else if(alarmSiren)                         //If the alarm siren is active and password correct
   {
      alarmActive = false;                        //Turn off the alarm
      disableAlarm();                             //Turn off the siren
      charCounter = 0;                            //Reset char counter buffer
      lcdPasswordCorrectScreen();                 //Display user message
   }
   else if(alarmActive)                        //If the alarm is set and password correct
   {
     alarmActive = false;                        //Turn off the alarm
     charCounter = 0;                            //Clear char counter buffer
     lcdPasswordCorrectScreen();                 //Display user message
   }
 }
 else                                           //If password is incorrect
 {
   lcdPassIncorrectScreen();                         //Display user message
   password.reset();                             //Reset the password
   charCounter = 0;                              //Clear the char counter buffer
   delay(2000);                                  //Delay the output for 2 seconds
   lcdMainScreen();                              //Return to main screen
 }
}

void checkDoorPass()                  //For checking the door lock password
{
   if(doorPass.evaluate())                  //If the password is correct
  {
    charCounter = 0;                          //clear the char counter buffer
    lcdDoorUnlocked();                        //Display user message
    unlockDoor();                             //unlock door solenoid
    lcdMainScreen();                          //Go back to main screen
  }
  else 
  {
     charCounter = 0;
     lcdPassIncorrectScreen();
     delay(2000);
     lcdMainScreen(); 
  }
}
