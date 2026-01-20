/*
 * Arduino Controller for FPS Game
 *
 * Hardware Requirements:
 * - 1x Arduino (Uno, Nano, or compatible)
 * - 1x Analog Joystick Module (4-pin)
 * - 2x Push Buttons
 * - 2x 10kΩ resistors (if buttons don't have built-in pullup)
 *
 * Wiring:
 * - Joystick VCC  -> 5V
 * - Joystick GND  -> GND
 * - Joystick X    -> A0
 * - Joystick Y    -> A1
 * - Fire Button   -> Pin 2 (with INPUT_PULLUP)
 * - Reload Button -> Pin 3 (with INPUT_PULLUP)
 *
 * Data Format:
 * Sends serial data in format: "joyX,joyY,fire,reload\n"
 * Example: "512,480,0,1" means joystick at (512, 480), fire not pressed, reload pressed
 */

// Pin Definitions
const int JOY_X = A0;      // Joystick X-axis (analog)
const int JOY_Y = A1;      // Joystick Y-axis (analog)
const int BTN_FIRE = 2;    // Fire button (digital)
const int BTN_RELOAD = 3;  // Reload button (digital)

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Configure button pins with internal pullup resistors
  pinMode(BTN_FIRE, INPUT_PULLUP);
  pinMode(BTN_RELOAD, INPUT_PULLUP);

  // Wait for serial port to connect
  delay(1000);
}

void loop() {
  // Read joystick position (0-1023 range)
  int joyX = analogRead(JOY_X);
  int joyY = analogRead(JOY_Y);

  // Read button states (inverted because of INPUT_PULLUP)
  // Pressed = LOW (0), Not pressed = HIGH (1)
  int fire = !digitalRead(BTN_FIRE);     // Invert: 0 = not pressed, 1 = pressed
  int reload = !digitalRead(BTN_RELOAD); // Invert: 0 = not pressed, 1 = pressed

  // Send data in CSV format: joyX,joyY,fire,reload
  Serial.print(joyX);
  Serial.print(",");
  Serial.print(joyY);
  Serial.print(",");
  Serial.print(fire);
  Serial.print(",");
  Serial.println(reload);  // println adds newline character

  // Update rate: 50ms = 20 updates per second
  delay(50);
}
