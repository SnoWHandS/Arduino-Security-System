void triggerAlarm()
{
  tone(7, 500);                //Begins a tone of 500Hz of the Buzzer pin
  alarmSiren = true;           //Sets the alarm siren as active
}

void disableAlarm()
{
  noTone(7);                   //Ends the tone 
  alarmSiren = false;          //Sets the alarm siren as inactive
}
