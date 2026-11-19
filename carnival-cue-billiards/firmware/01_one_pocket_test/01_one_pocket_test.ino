// Carnival Cue - single pocket test
// Green LED -> GPIO 4, Red LED -> GPIO 18, Pocket button -> GPIO 32, Passive buzzer -> GPIO 33

const int GREEN_PIN  = 4;
const int RED_PIN    = 18;
const int BUTTON_PIN = 32;
const int BUZZER_PIN = 33;

bool isTarget = true;          // true = green (shoot here), false = red (don't)
int score = 0;
unsigned long lastHit = 0;
const unsigned long DEBOUNCE_MS = 400;

void showState() {
  digitalWrite(GREEN_PIN, isTarget ? HIGH : LOW);
  digitalWrite(RED_PIN,   isTarget ? LOW  : HIGH);
  Serial.println(isTarget ? "Pocket is GREEN - shoot here!" : "Pocket is RED - don't shoot!");
}

void beepGood() {
  tone(BUZZER_PIN, 1500, 100); delay(130);
  tone(BUZZER_PIN, 2000, 150); delay(170);
}

void beepBad() {
  tone(BUZZER_PIN, 300, 400); delay(420);
}

void setup() {
  Serial.begin(115200);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // button between GPIO 32 and GND
  randomSeed(esp_random());
  showState();
}

void loop() {
  // Button reads LOW when pressed (ball dropped in)
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastHit > DEBOUNCE_MS) {
    lastHit = millis();

    if (isTarget) {
      score++;
      Serial.print("HIT! Score: ");
      Serial.println(score);
      beepGood();
    } else {
      score--;
      Serial.print("WRONG POCKET! Score: ");
      Serial.println(score);
      beepBad();
    }

    // Wait until the button is released so one ball = one hit
    while (digitalRead(BUTTON_PIN) == LOW) delay(10);

    // Randomly pick green or red for the next shot (70% green)
    isTarget = random(100) < 70;
    showState();
  }
}
