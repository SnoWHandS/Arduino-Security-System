void motionDetected()
{
   //If (current time - prevoius time) is smaller than 5uS debounce value
   if( (millis() - previousInterrupt) < debounceVal)    
  {
    return;                        //Leave this function & return to main
  }
  //If motion is detected
  if(digitalRead(2 == HIGH))
  {
    //Set the motion variable to true
    motionDetectedBol = true;
  }
 //Assign the timer value to previousInterrupt
 previousInterrupt = millis();
}

void checkMotion()
{
  //If motion was detected
  if(motionDetectedBol)
  {
    //If the alarm is set to active
    if(alarmActive)
    {
       //Trigger the siren
       triggerAlarm();
    }
    //If the alarm is not active
    if(!passwordEntered)
    {
     //Indicate that motion was detected
     lcdWrite("Motion Detected!",0,3);
     //Wait 1.5 seconds
     delay(1500);
     //Clear the line "Motion Detected"
     lcdClearLine(3);
     //Set the motion variable to false
     motionDetectedBol = false;
    }
  }
}
