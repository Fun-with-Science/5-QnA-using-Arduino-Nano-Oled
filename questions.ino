// Fun with science : youtube.com/channel/UCmXGznHZIeKiN7nSMAtD2Cw/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_A_PIN 2 // Change these pins according to your setup
#define BUTTON_B_PIN 3 // Change these pins according to your setup
#define BUZZER_PIN 4   // Change this pin according to your setup

int questionNumber = 0;
char userAnswers[5] = {' ', ' ', ' ', ' ', ' '}; // Store the user's answers
char correctAnswers[5] = {'A', 'A', 'B', 'B', 'A'}; // Define correct answers

void setup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display(); // Display logo screen
  delay(2000); // Delay for 2 seconds
  display.clearDisplay(); // Clear the buffer
}

void loop() {
  // Display questions and options
  switch(questionNumber) {
    case 0:
      displayQuestion("Who_is_your_Pet", "A) Alien", "B) Dinosaur");
      break;
    case 1:
      displayQuestion("Who_beats_most?", "A) Mom", "B) Dad");
      break;
    case 2:
      displayQuestion("Akkal_bari_ya_bhas", "A) Akkal", "B) bhas");
      break;
    case 3:
      displayQuestion("Object_you_get_Beat?", "A) chappal;", "B) Belan");
      break;
    case 4:
      displayQuestion("who_you_love", "A) family", "B) family");
      break;
    default:
      displayResults();
      break;
  }

  // Check button presses
  if (digitalRead(BUTTON_A_PIN) == LOW) {
    userAnswers[questionNumber] = 'A';
    questionNumber++;
    activateBuzzer();
    delay(500); // Debouncing delay
  }

  if (digitalRead(BUTTON_B_PIN) == LOW) {
    userAnswers[questionNumber] = 'B';
    questionNumber++;
    activateBuzzer();
    delay(500); // Debouncing delay
  }

  // End of questions, display results
  if (questionNumber >= 5) {
    displayResults();
  }
}

void displayQuestion(String title, String optionA, String optionB) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(title);
  display.setTextSize(2);
  display.println(optionA);
  display.println(optionB);
  display.display();
}

void displayResults() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Results:");
  for (int i = 0; i < 5; i++) {
    display.print("Q");
    display.print(i + 1);
    display.print(": ");
    display.print("Your Answer: ");
    display.print(userAnswers[i]);
    display.print(" Correct Answer: ");
    display.println(correctAnswers[i]);
  }
  display.display();
}

void activateBuzzer() {
  tone(BUZZER_PIN, 1000, 100); // Activate buzzer for 100 milliseconds
}
