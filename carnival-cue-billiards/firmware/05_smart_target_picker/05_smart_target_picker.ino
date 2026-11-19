// Carnival Cue - Smart Target Picker (heuristic search)
// One pocket is GREEN (target), the rest are RED.
// After each shot, every pocket gets a heuristic score and the highest one
// becomes the next target (greedy selection).
//   +3 per past miss on that pocket   (practice weak spots)
//   +1 per turn since it was a target (fairness)
//   -10 if it was the last target     (no repeats)
//   +0..2 random                      (tie-break / surprise)

const int GREEN[6]  = {4, 5, 13, 14, 2, 12};
const int RED[6]    = {18, 19, 23, 25, 26, 27};
const int BUTTON[6] = {32, 15, 34, 35, 36, 39};
const int BUZZER_PIN = 33;

const unsigned long DEBOUNCE_MS  = 300;
const unsigned long SHOT_TIME_MS = 15000;   // no ball in target for 15 s = miss

int missCount[6]  = {0};
int turnsSince[6] = {0};
int lastTarget    = -1;
int target        = 0;
int score         = 0;

bool lastPressed[6] = {false};
unsigned long lastPress = 0;
unsigned long targetSince = 0;

void showTarget() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(GREEN[i], i == target ? HIGH : LOW);
    digitalWrite(RED[i],   i == target ? LOW  : HIGH);
  }
  Serial.printf(">> TARGET: Pocket %d\n", target + 1);
  targetSince = millis();
}

int pickSmartTarget() {
  int bestPocket = 0;
  int bestScore  = -1000;

  Serial.println("--- Pocket scores ---");
  for (int i = 0; i < 6; i++) {
    int s = 0;
    s += missCount[i] * 3;
    s += turnsSince[i];
    if (i == lastTarget) s -= 10;
    s += random(0, 3);

    Serial.printf("Pocket %d: %d  (misses=%d, waited=%d)\n", i + 1, s, missCount[i], turnsSince[i]);
    if (s > bestScore) {
      bestScore  = s;
      bestPocket = i;
    }
  }

  for (int i = 0; i < 6; i++) turnsSince[i]++;
  turnsSince[bestPocket] = 0;
  lastTarget = bestPocket;
  return bestPocket;
}

void nextTarget() {
  target = pickSmartTarget();
  showTarget();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  for (int i = 0; i < 6; i++) {
    pinMode(GREEN[i], OUTPUT);
    pinMode(RED[i], OUTPUT);
    if (BUTTON[i] == 32 || BUTTON[i] == 15) pinMode(BUTTON[i], INPUT_PULLUP);
    else pinMode(BUTTON[i], INPUT);   // 10k external pull-up
  }
  randomSeed(esp_random());
  Serial.println("=== Carnival Cue: Smart Target Picker ===");
  nextTarget();
}

void loop() {
  for (int i = 0; i < 6; i++) {
    bool pressed = (digitalRead(BUTTON[i]) == LOW);

    if (pressed && !lastPressed[i] && millis() - lastPress > DEBOUNCE_MS) {
      lastPress = millis();

      if (i == target) {
        score++;
        if (missCount[i] > 0) missCount[i]--;   // getting better at this pocket
        Serial.printf("HIT pocket %d! Score: %d\n", i + 1, score);
        tone(BUZZER_PIN, 2000, 150);
      } else {
        score--;
        missCount[target]++;                    // target was missed
        Serial.printf("WRONG pocket %d (target was %d). Score: %d\n", i + 1, target + 1, score);
        tone(BUZZER_PIN, 300, 300);
      }
      nextTarget();
    }
    lastPressed[i] = pressed;
  }

  // Ran out of time on this target = miss
  if (millis() - targetSince > SHOT_TIME_MS) {
    missCount[target]++;
    Serial.printf("TIME UP on pocket %d. Counted as a miss.\n", target + 1);
    tone(BUZZER_PIN, 300, 300);
    nextTarget();
  }
}
