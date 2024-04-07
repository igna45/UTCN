#include <LiquidCrystal_I2C.h>

#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo ServoMotor;
String password = "4758";  //change the password here
String enteredPassword;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int RedpinLock = 13;    //red led
int GreenpinUnlock = 12; //green led

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  lcd.init(); 
  lcd.backlight();

  Serial.begin(9600);
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  ServoMotor.attach(11);
  LockedPosition(true);
  enteredPassword.reserve(3); 
  
  //welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome         ");
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN:      ");
  //lcd.clear(); 
}


void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '*' || key == '#') {
      //reset password and lock the door
      enteredPassword = "";
      LockedPosition(true);
      Serial.println("Password reset and door locked.");
    } else {
      enteredPassword += key;
      if (enteredPassword.length() == 4) {
        digitalWrite(RedpinLock, LOW);
        digitalWrite(GreenpinUnlock, LOW);

        Serial.print("Enter PIN:      ");
        Serial.println(enteredPassword);

        if (enteredPassword == password) {
          Serial.println("Password correct!");
          LockedPosition(false); //unlock
        } else {
          Serial.println("Incorrect password.");
          LockedPosition(true);  //keep locked and show red led
        }

        //reset entered password after checking
        enteredPassword = "";
      }
    }
  }
}

void LockedPosition(int locked) {
  if (locked) {
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    ServoMotor.write(0);  //update to the locked servo position if different
    Serial.println("Locked Position");
    lcd.clear();
    lcd.print("Door is locked");
    lcd.setCursor(0, 1);
    lcd.print("Enter PIN again:");
  } else {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90); //update to the unlock servo position if different
    Serial.println("Unlocked Position");
    lcd.clear();
    lcd.print("Door is unlocked");
  }
}
