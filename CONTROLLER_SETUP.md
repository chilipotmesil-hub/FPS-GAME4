# Arduino Controller Setup Guide - 5-Pin Joystick Version

This guide explains how to set up Arduino-based controllers with 5-pin joysticks for the two-player split-screen FPS game.

## Hardware Requirements

For each controller (2 total):
- 1x Arduino board (Uno, Nano, Leonardo, or compatible)
- 1x Analog Joystick Module (5-pin with VCC, GND, X, Y, SW)
- 1x Push Button (for Reload action)
- Optional: 1x 10kΩ resistor for reload button (if not using INPUT_PULLUP)
- USB cable to connect Arduino to computer

## 5-Pin Joystick Pinout

The 5-pin joystick includes:
- **VCC** - Power (5V)
- **GND** - Ground
- **X** - X-axis analog output (0-1023)
- **Y** - Y-axis analog output (0-1023)
- **SW** - Built-in button (press down on joystick to activate)

## Wiring Diagram

### Controller Wiring (for each Arduino):

```
5-Pin Joystick Module:
  VCC  -> Arduino 5V
  GND  -> Arduino GND
  X    -> Arduino A0 (Analog Pin 0)
  Y    -> Arduino A1 (Analog Pin 1)
  SW   -> Arduino Pin 2 (FIRE - press joystick down to shoot!)

External Reload Button:
  One side -> Arduino Pin 3
  Other side -> GND
```

**Note:** We use INPUT_PULLUP mode, so the reload button connects to GND when pressed. The joystick SW pin also uses INPUT_PULLUP.

## Arduino Setup Steps

### 1. Install Arduino IDE
- Download from [arduino.cc](https://www.arduino.cc/en/software)
- Install the Arduino IDE on your computer

### 2. Upload the Controller Sketch

1. Open the `Arduino_Controller.ino` file in Arduino IDE
2. Connect your first Arduino via USB
3. Select the correct board: `Tools > Board > Arduino Uno` (or your board type)
4. Select the correct port: `Tools > Port > [Your Arduino Port]`
5. Click "Upload" button (→) to upload the sketch
6. Repeat for the second Arduino

### 3. Test the Controllers

1. Open `Tools > Serial Monitor` in Arduino IDE
2. Set baud rate to 9600
3. Move the joystick and press buttons
4. You should see data like: `512,480,0,1`
   - First two numbers: joystick X and Y position (0-1023)
   - Third number: fire button state (0 or 1)
   - Fourth number: reload button state (0 or 1)

## Processing Game Setup

### 1. Determine Serial Ports

Before running the game, note which USB ports your Arduinos are connected to:
- **Windows:** COM3, COM4, etc.
- **Mac/Linux:** /dev/ttyUSB0, /dev/ttyACM0, etc.

### 2. Adjust Serial Port Indices (if needed)

In the Processing sketch (`gungameversion7.pde`), you may need to adjust the port indices in the `initializeControllers()` function:

```java
port1 = new Serial(this, ports[0], 9600);  // Change [0] to match your controller 1
port2 = new Serial(this, ports[1], 9600);  // Change [1] to match your controller 2
```

To find the correct indices:
1. Run the game once in keyboard mode
2. Check the Processing console for "Available serial ports" list
3. Note the index numbers next to your Arduino ports
4. Update the code with the correct indices

### 3. Run the Game

1. Connect both Arduino controllers via USB
2. Run the Processing sketch
3. At the title screen, press any key
4. Choose **'C' for CONTROLLER** mode
5. The game will initialize the controllers
6. Select your map and kills to win
7. Start playing!

## Troubleshooting

### "Need at least 2 serial ports" Error
- **Cause:** Both Arduinos not detected
- **Solution:**
  - Check USB connections
  - Make sure Arduino sketches are uploaded
  - Try reconnecting the Arduinos

### Controllers Not Responding
- **Cause:** Wrong serial ports selected
- **Solution:**
  - Check Processing console for port list
  - Update port indices in `initializeControllers()`
  - Restart the game

### Joystick Movement Inverted or Incorrect
- **Cause:** Joystick orientation or center calibration
- **Solution:**
  - Adjust `joyCenterX` and `joyCenterY` in the code (default: 512)
  - Flip X/Y axis comparisons in `updatePlayerFromController()` if needed

### Buttons Not Working
- **Cause:** Wiring or button polarity
- **Solution:**
  - Check button connections to GND
  - Verify buttons work in Serial Monitor test
  - Try removing the `!` (NOT operator) in Arduino code if using different wiring

## Joystick Calibration

The default center position is 512 (middle of 0-1023 range) with a dead zone of 100.

To adjust:
```java
int joyDeadZone = 100;     // Increase if joystick is too sensitive
int joyCenterX = 512;      // Adjust if joystick center is off
int joyCenterY = 512;      // Adjust if joystick center is off
```

## Tips for Best Experience

1. **Test Each Controller Separately:** Upload and test one Arduino at a time using Serial Monitor
2. **Secure Connections:** Use breadboards or solder connections for stable gameplay
3. **Label Controllers:** Mark which Arduino is Player 1 and Player 2
4. **USB Extension Cables:** Use longer USB cables so players can sit comfortably apart
5. **Check Serial Console:** If controllers don't work, check Processing console for error messages

## Game Controls Summary

### Keyboard Mode (K):
- **Player 1:** WASD (move) + SPACE (fire) + Q (reload)
- **Player 2:** Arrow Keys (move) + ENTER (fire) + / (reload)

### Controller Mode (C):
- **Both Players:**
  - Joystick: Move and turn
  - Press Joystick Down (SW button): Shoot 🔫
  - External Button: Reload weapon 🔄

## Advanced: Custom Pin Assignments

To use different pins, modify the Arduino sketch:

```cpp
const int JOY_X = A0;        // Change to your X-axis pin
const int JOY_Y = A1;        // Change to your Y-axis pin
const int JOY_SW = 2;        // Change to your joystick button pin (fire)
const int BTN_RELOAD = 3;    // Change to your reload button pin
```

Then re-upload the sketch to your Arduinos.

## Why 5-Pin Joystick?

The 5-pin joystick's built-in button (SW) provides a more intuitive firing mechanism:
- **Press down on the joystick to shoot** - feels natural and responsive
- **Reduces button count** - only need 1 external button instead of 2
- **Better ergonomics** - thumb naturally rests on joystick for firing
- **Arcade-style feel** - similar to classic arcade stick button layout

---

**Enjoy your Arduino-powered split-screen FPS battles!** 🎮🔫
