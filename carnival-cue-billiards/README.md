# Carnival Cue: Smart Target Pocket Billiards

An ESP32-based carnival pocket-billiards game built on a kids' billiard table.
Each of the 6 pockets has a **green LED** (shoot here) and a **red LED** (don't shoot here),
plus a button sensor under the pocket that detects when a ball drops in.

## Intelligent System features
1. **Smart Target Picker** - heuristic search (evaluation function + greedy selection) that picks the next target pocket from the player's miss history
2. **Adaptive Difficulty Engine** - fuzzy logic / rule-based difficulty adjustment
3. **Player Skill Classifier** - k-Nearest Neighbors classification (Beginner / Regular / Pro)
4. **Smart Attract & Wave-to-Start** - rule-based expert system using PIR + IR sensors

## Hardware
- ESP32 Development Board
- 6 green LEDs, 6 red LEDs, 220 ohm resistors
- 6 push buttons (pocket sensors), 10k pull-up resistors
- Passive buzzer, 0.96" OLED, potentiometer, PIR motion sensor, IR obstacle sensor
- 830 tie-point breadboard, jumper wires

See [`docs/pin_map.md`](docs/pin_map.md) for wiring.

## Firmware
| Sketch | Purpose |
|---|---|
| `firmware/01_one_pocket_test` | First single-pocket prototype (LEDs, button, buzzer, scoring) |
| `firmware/02_one_pocket_instant_lights` | Single pocket with instant LED switching on hit |
| `firmware/03_six_pocket_wiring_test` | Tests all 12 LEDs in sequence and all 6 pocket buttons |
| `firmware/04_all_leds_on` | Diagnostic: turns on every LED to check wiring |
| `firmware/05_smart_target_picker` | **IS Feature 1:** heuristic search target picker with live pocket scores |

Open a sketch in Arduino IDE, select **ESP32 Dev Module**, and upload. Serial Monitor: 115200 baud.

## Course
Intelligent Systems (IS) - Ms. Mikaela Arciaga
