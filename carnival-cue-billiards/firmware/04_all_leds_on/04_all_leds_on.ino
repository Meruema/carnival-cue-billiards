// Carnival Cue - all LEDs ON (diagnostic)

const int GREEN[6] = {4, 5, 13, 14, 2, 12};
const int RED[6]   = {18, 19, 23, 25, 26, 27};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 6; i++) {
    pinMode(GREEN[i], OUTPUT);
    pinMode(RED[i], OUTPUT);
    digitalWrite(GREEN[i], HIGH);
    digitalWrite(RED[i], HIGH);
  }
  Serial.println("All 12 LEDs should be ON");
}

void loop() {
}
