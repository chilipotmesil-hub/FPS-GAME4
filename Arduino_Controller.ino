/*
 * Arduino Controller for FPS Game - 5-Pin Joystick Version
 *
 * Hardware Requirements:
 * - 1x Arduino (Uno, Nano, or compatible)
 * - 1x Analog Joystick Module (5-pin)
 * - 2x Push Buttons (Fire and Reload)
 * - Optional: 2x 10kΩ resistors for buttons (if not using INPUT_PULLUP)
 *
 * 5-Pin Joystick Pinout:
 * - VCC (power)
 * - GND (ground)
 * - X (X-axis analog)
 * - Y (Y-axis analog)
 * - SW (built-in button - NOT USED in this setup)
 *
 * Wiring:
 * - Joystick VCC  -> Arduino 5V
 * - Joystick GND  -> Arduino GND
 * - Joystick X    -> Arduino A0
 * - Joystick Y    -> Arduino A1
 * - Joystick SW   -> Leave disconnected (not used)
 * - Fire Button   -> Arduino Pin 2 (external button with INPUT_PULLUP)
 * - Reload Button -> Arduino Pin 3 (external button with INPUT_PULLUP)
 *
 * Data Format:
 * Sends serial data in format: "joyX,joyY,fire,reload\n"
 * Example: "512,480,1,0" means joystick at (512, 480), fire pressed, reload not pressed
 */

// Pin Definitions
const int JOY_X = A0;        // Joystick X-axis (analog)
const int JOY_Y = A1;        // Joystick Y-axis (analog)
const int BTN_FIRE = 2;      // Fire button (digital) - external button
const int BTN_RELOAD = 3;    // Reload button (digital) - external button

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Configure button pins with internal pullup resistors
  pinMode(BTN_FIRE, INPUT_PULLUP);      // Fire button
  pinMode(BTN_RELOAD, INPUT_PULLUP);    // Reload button

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
