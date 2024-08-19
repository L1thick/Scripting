#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
const int buttonPin = 7;            // Pin connected to the start button
const int resetButtonPin = 8;       // Pin connected to the reset button
int pos = 0;
unsigned long previousMillis = 0;   // Store the last time the position was updated
const long interval = 1000;         // Interval at which to update the position (milliseconds)
String message = "}==>";            // Initial message
int countdown = 5;                  // Countdown starting value
bool countdownStarted = false;      // Flag to check if the countdown has started
bool displayOn = true;              // Flag to check if the display is on

void setup()
{
  lcd_1.begin(16, 2);               // Set up the number of columns and rows on the LCD
  pinMode(buttonPin, INPUT_PULLUP); // Set the start button pin as input with pull-up resistor
  pinMode(resetButtonPin, INPUT_PULLUP); // Set the reset button pin as input with pull-up resistor

  // Display the static message and "Go for Launch" initially
  lcd_1.setCursor(0, 0);
  lcd_1.print(message);
  lcd_1.setCursor(0, 1);
  lcd_1.print("Go for Launch");
}

void loop()
{
  // Check if the reset button is pressed
  if (digitalRead(resetButtonPin) == LOW) {
    // Turn off the display and reset the animation
    lcd_1.noDisplay();
    pos = 0;
    countdown = 5;
    countdownStarted = false;
    displayOn = false;
    delay(50); // Debounce delay
  } else if (!displayOn) {
    // Turn on the display and reset the loop
    lcd_1.display();
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(message);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Go for Launch");
    displayOn = true;
    delay(50); // Debounce delay
  } else {
    if (!countdownStarted) {
      // Wait for the start button press to start the countdown
      if (digitalRead(buttonPin) == LOW) {
        countdownStarted = true;
        delay(50); // Debounce delay
        lcd_1.clear(); // Clear the LCD after the button press
      }
    } else {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Clear the LCD
        lcd_1.clear();

        // Display the message on the first line
        lcd_1.setCursor(0, 0);
        if (countdown >= 0) {
          lcd_1.print(message);
        } else {
          // Create the new message with the current position
          lcd_1.setCursor(pos, 0);
          lcd_1.print(message);

          // Update the position
          pos++;

          // Reset the position if the message has completely left the screen
          if (pos > 16 - message.length()) {
            pos = 0;
          }
        }

        // Display the countdown or BLAST OFF! on the second line
        lcd_1.setCursor(0, 1);
        if (countdown >= 0) {
          lcd_1.print("Countdown: ");
          lcd_1.print(countdown);
          countdown--;
        } else {
          lcd_1.print("BLAST OFF!");
        }
      }
    }
  }
}
