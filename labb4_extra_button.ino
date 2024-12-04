#define GREEN_LED 12  // Pin for the green LED
#define RED_LED 11    // Pin for the red LED
#define BTN_1 5       // Pin for button 1
#define BTN_2 4       // Pin for button 2
#define BTN_3 3       // Pin for button 3
#define BTN_4         // Pin for button 4
#define PROG_BTN 6    // Button for programming mode

const int passcodeLength = 4; // Length of the passcode
int passcode[passcodeLength] = {BTN_4, BTN_2, BTN_1, BTN_4};  // Default passcode (buttons)
int new_passcode[passcodeLength] = {0, 0, 0, 0};  // Temporary storage for new passcode
int input_passcode[passcodeLength] = {0, 0, 0, 0};  // Array to store recent button presses

bool isLocked = true;
bool isProgrammingMode = false;

void setup() {
  // Set up LED pins as output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Set up button pins as input with internal pull-up resistors
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);
  pinMode(PROG_BTN, INPUT_PULLUP);

  // Start the Serial Monitor for debugging
  Serial.begin(9600);

  // Initially, the system is locked, so the red LED is on and green LED is off
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  // If the programming button is pressed, toggle programming mode
  if (digitalRead(PROG_BTN) == LOW) {
    delay(200);  // Simple debounce
    isProgrammingMode = !isProgrammingMode;  // Toggle programming mode

    if (isProgrammingMode) {
      // Start programming mode: blink both LEDs
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    } else {
      // End programming mode: save the new passcode and reset to locked state
      for (int i = 0; i < passcodeLength; i++) {
        passcode[i] = new_passcode[i]; // Save the new passcode
      }
      isLocked = true;
      digitalWrite(RED_LED, HIGH);  // Red LED on to indicate locked state
      digitalWrite(GREEN_LED, LOW); // Green LED off
    }

    // Wait for the button to be released to prevent multiple toggles
    while (digitalRead(PROG_BTN) == LOW);
  }
  // Handle button presses depending on whether we are in programming mode or locked
  if (isProgrammingMode) {
    // In programming mode, check all buttons and store inputs in new_passcode
    checkButtonPressAndStoreInNewPasscode(BTN_1);
    checkButtonPressAndStoreInNewPasscode(BTN_2);
    checkButtonPressAndStoreInNewPasscode(BTN_3);
    checkButtonPressAndStoreInNewPasscode(BTN_4);
  } else {
    // In normal mode, check button presses and store them in input_passcode
    checkButtonPress(BTN_1);
    checkButtonPress(BTN_2);
    checkButtonPress(BTN_3);
    checkButtonPress(BTN_4);

    // If the input matches the passcode, unlock the system
    if (isCorrectPasscode()) {
      isLocked = false;
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH); // Green LED on to indicate unlocked state
      delay(5000);  // Stay unlocked for 5 seconds
      isLocked = true;
      digitalWrite(RED_LED, HIGH);  // Red LED on
      digitalWrite(GREEN_LED, LOW); // Green LED off
    }
  }
  delay(50);  // Small delay to prevent fast repeated inputs and provide a debounce effect
}

// Function to check if a button is pressed and store the input in the input_passcode array
void checkButtonPress(int button) {
  if (digitalRead(button) == LOW) {
    storeButtonPress(button); // Store the button press in the input passcode
    delay(200);  // Simple debounce
  }
}

// Function to check if a button is pressed and store the input in the new passcode (for programming)
void checkButtonPressAndStoreInNewPasscode(int button) {
  if (digitalRead(button) == LOW) {
    storeButtonPressInNewPasscode(button); // Store the button press in the new passcode
    delay(200);  // Simple debounce
  }
}
  // Function to store a button press in the input passcode (FIFO)
void storeButtonPress(int button) {
  // Shift existing inputs (FIFO)
  for (int i = 1; i < passcodeLength; i++) {
    input_passcode[i - 1] = input_passcode[i];
  }
  input_passcode[passcodeLength - 1] = button;  // Store the new input at the last index
  Serial.print("Button pressed: ");
  Serial.println(button);
}

// Function to store a button press in the new passcode (FIFO)
void storeButtonPressInNewPasscode(int button) {
  // Shift existing inputs (FIFO)
  for (int i = 1; i < passcodeLength; i++) {
    new_passcode[i - 1] = new_passcode[i];
  }
  new_passcode[passcodeLength - 1] = button;  // Store the new input at the last index
  Serial.print("New passcode button pressed: ");
  Serial.println(button);
}

// Function to check if the input passcode matches the stored passcode
bool isCorrectPasscode() {
  for (int i = 0; i < passcodeLength; i++) {
    if (input_passcode[i] != passcode[i]) {
      return false;
    }
  }
  return true;
}
