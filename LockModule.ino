void unlockDoor()
{
  digitalWrite(lockPin, HIGH);
  delay(1500);
  digitalWrite(lockPin, LOW);
}
