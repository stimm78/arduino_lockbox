#include <Key.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

// Define the states for the lock state machine
#define LOCKED 1
#define UNLOCKED 0

// State Variables:   Initialize to the locked state
int LockState = LOCKED;
long StartTime = 0;
int position = 0;

// Define your password key sequence here
String secretCode = "1423";

// Keypad key matrix: 
char keys[4][3] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Keypad pin definitions
byte rowPins[4] = {2, 3, 4, 5};  //connect to the row pinouts of the keypad
byte colPins[3] = {6, 7, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 3);

// More pin definitions:
int LedPin = 10;
int SolenoidPin = 11;

void setup()                    
{
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
  pinMode(SolenoidPin, OUTPUT);
   
  // Flash hello (Temporary)
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LedPin, HIGH);
    delay(100);
    digitalWrite(LedPin, LOW);
    delay(100);
  }
}


void loop()                    
{   
   // Locked State - Monitor keypad for valid Password code entry
   if (LockState == LOCKED)
   {
      char key = keypad.getKey();

      if (key == '*' || key == '#')
      {
         position = 0;
         setLockState(LOCKED);
      }
      if (key == secretCode.charAt(position))  // Valid key in Password sequence
      {
        Serial.print("Matched ");   
        Serial.print(key);   
        Serial.print("-at-");   
        Serial.println(position);   
        position++;
      }
      else  // Invalid key - start all over again
      {
         Serial.println("Invalid Code!");   
         position = 0;
      }

      // Let the LED 'breathe' while we wait
      analogWrite(LedPin, sin((millis() % 3142) / 1000.0) * 255);

      if (position == secretCode.length())  // Password successfully entered - advance state
      {
         setLockState(UNLOCKED);
         position = 0;
      }
      delay(100);
   }

   // UNLOCKED state - hold the solenoid open for a limited time
   else if (LockState == UNLOCKED)
   { 
      for (int i = 0; i < 30; i++)
      {
         // Flash the led to indicate the lock is open
         digitalWrite(LedPin, LOW);
         delay(50);
         digitalWrite(LedPin, HIGH);
         delay(50);
      }
      setLockState (LOCKED);  // Time-out - go back to the locked state.
   }
}



// Set the state and the time of the state change
void setLockState(int state)
{
   LockState = state;
   StartTime = millis ();
   if (state == LOCKED)
   {
      Serial.println("Locked!");
      digitalWrite(LedPin, HIGH);
      digitalWrite(SolenoidPin, LOW);  
   }    
   else if (state == UNLOCKED)
   {
      Serial.println("Unlocked!");
      digitalWrite(LedPin, LOW);
      digitalWrite(SolenoidPin, HIGH);      
   }
}
