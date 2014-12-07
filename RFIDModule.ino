


void storeUserCard()
{
   if(readCard())
 {  
      //Storing the UID  
      for(byte i = 0; i < rfidReader.uid.size; i++)
      {  
         //Writes the sequentially read bytes from the RFID reader to the userCard array     
         userCard[i] = rfidReader.uid.uidByte[i];
      }
     //Set the card as read
     cardIsRead = true;
     //Returns to main 
      return;
 }
}

boolean readCard()
{
      //Returns if there is no new card
      if(!rfidReader.PICC_IsNewCardPresent())
      {
           //Return false to the storeUserCard function if there is no card
           return false;
      }
      
      //Returns if card cannot be read
      if(!rfidReader.PICC_ReadCardSerial())
      {
          //Return false to the storeUserCard function if the card cannot be read
          return false;
      }
      //Otherwise return true and store the card info
      return true;
}

String stringUserCard()
{
  //Create a temporary variable to hold the Card ID
  String userCardString;
  for(int i = 0; i<4; i++)
  {
     //Sequentially add each byte to the string
     userCardString += userCard[i];
  }
   //Set the card as no longer read
   cardIsRead = false;
   //Return the decimal version of the card ID
   return userCardString;
}

void displayUserCard()
{
    Serial.print(" UserCard = ");
    for(byte i = 0; i<4; i++)
    {
      Serial.print(userCard[i]);
      Serial.print(" ");
    }
    Serial.println();
}
