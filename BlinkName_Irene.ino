// Define LED pin
const int ledPin = LED_BUILTIN;

// Define push button pin
const int buttonPin = 2;

// Define Morse code for letters
const String morseCodes[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

// Define Morse code for letters of the name "Irene"
const String ireneMorse = ". .-. . -. .";

// Define timing constants
const int dotDuration = 250; // in milliseconds
const int dashDuration = dotDuration * 3;

// Define state variables
bool blinking = false;
bool buttonState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize push button pin as input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Read the state of the push button
  int reading = digitalRead(buttonPin);
  
  // Check if the push button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // Check for button debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update the button state
    if (reading != buttonState) {
      buttonState = reading;
      
      // If the button is pressed
      if (buttonState == HIGH) {
        // Toggle blinking state
        blinking = !blinking;
        
        // If blinking is enabled, start blinking "Irene" in Morse code
        if (blinking) {
          blinkMorse(ireneMorse);
        }
        // If blinking is disabled, turn off LED
        else {
          digitalWrite(ledPin, LOW);
        }
      }
    }
  }
  
  // Update last button state
  lastButtonState = reading;
}

// Function to blink Morse code
void blinkMorse(String morse) {
  for (int i = 0; i < morse.length(); i++) {
    char c = morse.charAt(i);
    if (c == '.') {
      digitalWrite(ledPin, HIGH);
      delay(dotDuration);
      digitalWrite(ledPin, LOW);
      delay(dotDuration);
    } else if (c == '-') {
      digitalWrite(ledPin, HIGH);
      delay(dashDuration);
      digitalWrite(ledPin, LOW);
      delay(dotDuration);
    } else if (c == ' ') {
      delay(dotDuration * 3);
    }
  }
}
