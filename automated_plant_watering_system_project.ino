#include <LiquidCrystal.h>
// Include the LiquidCrystal library, which provides functions to control the LCD display.

// Declaring variables
const int BuzzerPin = 10;             // Pin connected to the piezo buzzer
const int LedRed = 12;                // Pin connected to the red LED
const int LedGreen = 11;              // Pin connected to the green LED
const int SoilMoistureSensor = A0;    // Pin connected to the soil moisture sensor
const int WaterPump = 13;             // Pin connected to the water pump relay

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Create an instance of the LiquidCrystal class to control the LCD

void setup()
{
  pinMode(WaterPump, OUTPUT);         // Set the water pump pin as output
  pinMode(LedRed, OUTPUT);            // Set the red LED pin as output
  pinMode(LedGreen, OUTPUT);          // Set the green LED pin as output
  pinMode(BuzzerPin, OUTPUT);         // Set the piezo buzzer pin as output
  
  Serial.begin(9600);                // Initialize serial communication at 9600 bps
  
  lcd.begin(16, 2);                  // Initialize the LCD with 16 columns and 2 rows
  pinMode(BuzzerPin, OUTPUT);        // Set the piezo pin as output

  lcd.clear();                       // Clear the LCD display
  lcd.setCursor(0, 0);               // Set the cursor to the first column and first row

  String message1 = "Automated Plant";
  String message2 = "Watering System";

  // Display "Automated Plant" on the first row of the LCD with a delay of 100ms between characters
  for (int i = 0; i < message1.length(); i++) {
    lcd.print(message1.charAt(i));
    delay(100);
  }

  lcd.setCursor(0, 1);               // Set the cursor to the first column and second row

  // Display "Watering System" on the second row of the LCD with a delay of 100ms between characters
  for (int i = 0; i < message2.length(); i++) {
    lcd.print(message2.charAt(i));
    delay(100);
  }

  delay(2500);                       // Delay for 2.5 seconds to display the messages
  lcd.clear();                       // Clear the LCD display again
  lcd.setCursor(0, 0);               // Set the cursor to the first column and first row
  lcd.print("Moisture =");           // Display "Moisture =" on the first row
  lcd.setCursor(0, 1);               // Set the cursor to the first column and second row
  lcd.print("Water Pump =");         // Display "Water Pump =" on the second row
}

void loop()
{
  int Sensor = analogRead(SoilMoistureSensor);  // Read the value from the soil moisture sensor
  int mappedValue = map(Sensor, 0, 876, 0, 99); // Map the sensor value to a range from 0 to 99

  lcd.setCursor(11, 0);              // Set the cursor to the 12th column and first row
  lcd.print(mappedValue);            // Display the mapped value (moisture percentage) on the first row
  lcd.setCursor(14, 0);              // Set the cursor to the 15th column and first row
  lcd.print("%");                    // Display the percentage symbol on the first row
  lcd.setCursor(13, 1);              // Set the cursor to the 14th column and second row

  // Control the water pump and LEDs based on the moisture percentage
  if (mappedValue < 50) {
    digitalWrite(WaterPump, HIGH);   // Turn on the water pump
    digitalWrite(LedGreen, HIGH);    // Turn on the green LED
    digitalWrite(LedRed, LOW);       // Turn off the red LED
    lcd.print("ON ");                // Display "ON" on the second row
    playSound();                     // Play a sound using the piezo buzzer
  }
  else {
    digitalWrite(WaterPump, LOW);    // Turn off the water pump
    digitalWrite(LedGreen, LOW);     // Turn off the green LED
    digitalWrite(LedRed, HIGH);      // Turn on the red LED
    lcd.print("OFF");                // Display "OFF" on the second row
  }
}

void playSound() {
  tone(BuzzerPin, 87, 100);  // Play a tone of 87 Hz for 100 milliseconds on the piezo buzzer
  delay(1000);               // Delay for 1 second
}