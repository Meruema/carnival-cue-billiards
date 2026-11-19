// Carnival Cue - 6 pocket wiring test

const int GREEN[6]  = {4, 5, 13, 14, 2, 12};
const int RED[6]    = {18, 19, 23, 25, 26, 27};
const int BUTTON[6] = {32, 15, 34, 35, 36, 39};
const int BUZZER_PIN = 33;

bool lastPressed[6] = {false};
unsigned long lastHit[6] = {0};
const unsigned long DEBOUNCE_MS = 300;

void allOff() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(GREEN[i], LOW);
    digitalWrite(RED[i], LOW);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  for (int i = 0; i < 6; i++) {
    pinMode(GREEN[i], OUTPUT);
    pinMode(RED[i], OUTPUT);
    // 32 and 15 have built-in pull-ups; 34, 35, 36, 39 use the 10k resistors
    if (BUTTON[i] == 32 || BUTTON[i] == 15) pinMode(BUTTON[i], INPUT_PULLUP);
    else pinMode(BUTTON[i], INPUT);
  }
  allOff();

  // ---- LED test: each pocket green, then red ----
  Serial.println("=== LED TEST ===");
  for (int i = 0; i < 6; i++) {
    Serial.printf("Pocket %d: GREEN\n", i + 1);
    digitalWrite(GREEN[i], HIGH);
    delay(500);
    digitalWrite(GREEN[i], LOW);

    Serial.printf("Pocket %d: RED\n", i + 1);
    digitalWrite(RED[i], HIGH);
    delay(500);
    digitalWrite(RED[i], LOW);
  }

  // ---- Check for stuck buttons ----
  Serial.println("=== BUTTON CHECK ===");
  for (int i = 0; i < 6; i++) {
    if (digitalRead(BUTTON[i]) == LOW) {
      Serial.printf("WARNING: Pocket %d button reads PRESSED without touching it. Check wiring / 10k resistor.\n", i + 1);
    }
  }

  // All red = ready
  for (int i = 0; i < 6; i++) digitalWrite(RED[i], HIGH);
  Serial.println("Ready! Press any pocket button.");
}

void loop() {
  for (int i = 0; i < 6; i++) {
    bool pressed = (digitalRead(BUTTON[i]) == LOW);

    if (pressed && !lastPressed[i] && millis() - lastHit[i] > DEBOUNCE_MS) {
      lastHit[i] = millis();
      Serial.printf("Pocket %d button PRESSED\n", i + 1);

      // That pocket turns green, beep pitch goes up with pocket number
      digitalWrite(RED[i], LOW);
      digitalWrite(GREEN[i], HIGH);
      tone(BUZZER_PIN, 800 + i * 200, 150);
    }

    if (!pressed && lastPressed[i]) {
      // Back to red when released
      digitalWrite(GREEN[i], LOW);
      digitalWrite(RED[i], HIGH);
    }

    lastPressed[i] = pressed;
  }
}
