/// The pin number of the reset button.
const int resetPin = 2;

/// An array of input pins.
const int buttonPins[] = {4};
/// An array of output pins corresponding to each player or input pin in `buttonPins`.
const int ledPins[] = {13};

/// Whether the system locks others out.
bool isLockedOut = false;
/// A default value representing the fact that no one has the buzz.
const int NO_PLAYER = -1;
/// The player who currently has the buzz. Initializes to `NO_PLAYER`.
int currentPlayer = NO_PLAYER;

void setup() {
  // put your setup code here, to run once:
  // Configure the reset pin.
  pinMode(resetPin, INPUT);

  // Configure the input and output pins, assuming `buttonPins` and `ledPins` are the same size.
  for (int i = 0; i < sizeof(buttonPins); i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if the reset button is pressed.
  int resetButtonState = digitalRead(resetPin);
  if (resetButtonState == HIGH) {
    // If it is, stop locking others out, and turn off all the output pins.
    isLockedOut = false;
    for (int i = 0; i < sizeof(ledPins); i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  // If players are not locked out,
  if (!isLockedOut) {
    // Loop through the input pins and see who buzzed, assuming no one ever buzzes at exactly the same loop.
    for (int i = 0; i < sizeof(buttonPins); i++) {
      int buttonState = digitalRead(buttonPins[i]);
      // If someone buzzed, turn on that player's light and lock others out.
      if (buttonState == HIGH) {
        digitalWrite(ledPins[i], HIGH);
        isLockedOut = true;
        currentPlayer = i;
        return;
      }
    }
  }
}
