# Pin Map (ESP32)

| Pocket | Green LED | Red LED | Pocket Button | Breadboard rows |
|---|---|---|---|---|
| 1 | GPIO 4  | GPIO 18 | GPIO 32 | 24 / 25 / 26 |
| 2 | GPIO 5  | GPIO 19 | GPIO 15 | 28 / 29 / 30 |
| 3 | GPIO 13 | GPIO 23 | GPIO 34* | 32 / 33 / 34 |
| 4 | GPIO 14 | GPIO 25 | GPIO 35* | 36 / 37 / 38 |
| 5 | GPIO 2  | GPIO 26 | GPIO 36 (VP)* | 40 / 41 / 42 |
| 6 | GPIO 12 | GPIO 27 | GPIO 39 (VN)* | 44 / 45 / 46 |

- Passive buzzer: GPIO 33
- OLED (I2C): SDA GPIO 21, SCL GPIO 22
- LEDs: GPIO -> 220 ohm resistor -> LED (+) ... LED (-) -> GND
- Buttons: GPIO -> button -> GND. GPIO 32 and 15 use internal pull-up.
- \* Input-only pins with no internal pull-up: 10k resistor from the pin to 3.3V.
- GPIO 16/17 are not available on our board, so pocket 5/6 green use GPIO 2 and 12.
