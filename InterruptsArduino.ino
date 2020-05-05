/*
  Shivam Mehrotra - 660104381
  Lab 8 - Interrupts
  Description: The lab is to have you use 2 buttons and the 16x2 LCD display. Each button is to trigger an
  interrupt. The interrupts are to toggle between two states/messages displayed on the 16x2 LCD.
  Assumptions LCD is connected to 12,11,10,9,8,7. The two buttons are connected to 3 and 2.
  References:
    http://arduino.cc/en/Reference/attachInterrupt
    https://www.arduino.cc/en/Reference/Millis
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// pins that will recieve the interrupt signals
const byte button1 = 2;
const byte button2  = 3;
int buttonStateDown = 0;         // variable for reading the pushbutton status
int previousStateDown =0;

int state = 0;
int time = millis();


// move lcd cursor to correct position to display time
void printTime() {
  int cursorS = 0; 
  for(int i = time; i > 9; i /= 10 ) cursorS++;
  lcd.setCursor(7-cursorS,1);
  lcd.print(time);
}

void run() {
  lcd.clear();
  time++;
  lcd.setCursor(0,0);
  lcd.print("We Have Been Waiting For");
  lcd.setCursor(8,1);
  lcd.print("seconds");
  printTime();
  delay(1000); 
}

// show prompt "Press 2 to continue..." on to the LCD
void pause() {
  lcd.setCursor(0,0);
  lcd.print("Interrupt Recieved");
  lcd.setCursor(0,1);
  lcd.print("Press Button 2 to continue");
  delay(200); 
}

void resume() { 
  // reset time and change back to running state
  if(state == 1)
  {
    time = -1;  
    state = 0;
    lcd.clear();
  }
} 

void stop() { 
  // change the state to stop and clear screen
  if(state == 0)
  {
    state = 1;
    lcd.clear();
  }
}

void setup() {
  lcd.begin(16, 2);  
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT);

  // interrupt signals
  attachInterrupt(digitalPinToInterrupt(button1), stop, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button2), resume, CHANGE);
}

void loop() 
{

  if(state == 0){
    run(); 
  }
  else {
    pause();
    // read the state of the pushbutton value:
    delay(2000);
    buttonStateDown = digitalRead(button2);   // Read the state of the down button
    if(buttonStateDown != previousStateDown){     // compare the presses
     if(buttonStateDown == HIGH){ 
      if(state == 1)
      {
        time = -1;  
        state = 0;
        lcd.clear();
      }
     }
    }
    previousStateDown = buttonStateDown;          // store the last press for down button   
  }
}
