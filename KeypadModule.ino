

//---------------------------Beginning of Keypad Functions-------------------------------------------

void keypadEvent(KeypadEvent eKey)
{
   switch(customKeypad.getState())
   {
//Begin Case: Pressed
      case PRESSED:          
          switch(eKey)                                                                                                                                                                                                                                                           
          {
             case '*':  break;                       //prevents the password containing a *
             case '#':  break;                       //Prevents the password containt #
                     
             default:  if(passwordEntered)          //If the password is not entered, append password
                       {
                          password.append(eKey);              //Add the entered char to the password evaluation buffer
                          lcdWrite("*", charCounter, 3);      //Print a * for each char entered
                          charCounter++;                      //Increment the char counter
                       }
                       else if(doorPassEntered)
                       {
                           doorPass.append(eKey);              //Add the entered char to the password evaluation buffer
                           lcdWrite("*", charCounter, 3);      //Print a * for each char entered
                           charCounter++;                      //Increment the char counter
                       }
          }
      break;
//End Case: Pressed
//Begin Case: Hold
       case HOLD:
         switch(eKey)
         {
           //If * is held for 1.5 seconds
            case '*': 
                      if(!passwordEntered)                        //While the password has not been entered
                      {
                        password.reset();                         //Reset the alarm password input
                        lcdPasswordScreen();                      //Display the user password input screen
                        passwordEntered = true;                   //Set the passwordEntered as active
                      }
                      else
                      {
                        checkPassword();                          //Check the password
                        passwordEntered = false;                  //Set passwordEntered as false
                      }         
                      break;
            //If # is held for 1.5 seconds
            case '#': 
                      if(!doorPassEntered)                        //While the password has not been entered
                      {
                         doorPass.reset();                        //Reset the door password input
                         lcdDoorPassScreen();                     //Display the user password input screen
                         doorPassEntered = true;                  //Set the door passwordEntered as active
                      }
                      else
                      {
                         checkDoorPass();                         //Check the door password
                         doorPassEntered = false;                 //Set the door passwordEntered as active
                      }
                      break;
         }
//End Case: Hold
   } 
}

//---------------------------End of Keypad Functions-------------------------------------------------
