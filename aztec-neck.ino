#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <Fonts/Picopixel.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include "font5x.h"


#define mw 64
#define mh 16
#define PIN 25

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 2, 2, PIN,
  NEO_MATRIX_TOP+ NEO_MATRIX_LEFT  + NEO_MATRIX_COLUMNS   + NEO_MATRIX_ZIGZAG +
  NEO_TILE_TOP + NEO_TILE_LEFT +NEO_TILE_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

// Variables to control the bouncing water drop animation.
int waterDropPositions[30];
int waterDropSpeeds[30];
uint32_t waterDropColor;

// Variables to control the color interpolation.
uint8_t r = 70;  // Start with a medium red color.
int direction = -1;  // Start by decreasing the brightness.
bool isRed = true;

#define DELAYVAL 50  
int t = 0;  


#define FIREWORKS 20  // Número de "fuegos artificiales"

struct Firework {
  float x, y;   // Posición actual
  float vx, vy; // Velocidad
  int age;      // Edad del fuego artificial
};

Firework fireworks[FIREWORKS];  

const char text1[] = "AZTEC";
const char text2[] = "ROBOT";

// Variables para controlar el fundido
int fadeDirection = 1; // 1 para el fade in, -1 para el fade out
int fadeValue = 0; // Valor inicial del brillo (0 = apagado)
#define DELAY_MS2 50
#define STAR_BRIGHTNESS 80
#define EXPLOSION_BRIGHTNESS 255
#define EXPLOSION_PROBABILITY 1000 // 1 in 1000 chance per frame

#include <ESP32Servo.h>

// create four servo objects 
Servo servo1;
Servo servo2;

// Published values for SG90 servos; adjust if needed
int minUs = 500;
int maxUs = 2500;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42
// for the ESP32-S3 the GPIO pins are 1-21,35-45,47-48
// for the ESP32-C3 the GPIO pins are 1-10,18-21

int servo1Pin = 16;
int servo2Pin = 22;

int mytime = 39;

int pos = 0;      // position in degrees
ESP32PWM pwm;

// Función para generar colores para el arco iris
uint16_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
   WheelPos -= 85;
   return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	Serial.begin(115200);
	servo1.setPeriodHertz(250);      // Standard 50hz servo
	servo2.setPeriodHertz(250);      // Standard 50hz servo
  servo1.attach(servo1Pin, minUs, maxUs);
	servo2.attach(servo2Pin, minUs, maxUs);
  normal_pose();
  matrix.begin();


  matrix.setTextWrap(false);
  matrix.setBrightness(30);  // Reduced brightness.
  matrix.setFont(&Font5x7FixedMono);

  // Initialize the water drops.
  for (int i = 0; i < 30; i++) {
    waterDropPositions[i] = random(matrix.height());  // Random y position.
    waterDropSpeeds[i] = random(1, 3);  // Random speed.
  }

  for(int i=0; i<FIREWORKS; i++) {
    startFirework(fireworks[i]);
  }

}

void startFirework(Firework &f) {
  f.x = random(mw);
  f.y = mh;
  f.vx = random(-10, 11) / 10.0;
  f.vy = random(-20, -10) / 10.0;
  f.age = 0;
}

void normal_pose(){
  servo1.write(100);
  delay(1000);   
  servo2.write(72);
  delay(1000); 
}

void loop() {
   aztec();
  //aztec2();
  //aztec3();
  //aztec4();
  //aztec5();
}

void aztec5(){
  matrix.setBrightness(128); 
  matrix.fillScreen(0);

  // "Stars"
  for (int i=0; i < (mw*mh); i++) {
    if (random(10) < 1) { // ~10% of LEDs will be "stars"
      matrix.drawPixel(random(mw), random(mh), matrix.Color(STAR_BRIGHTNESS, STAR_BRIGHTNESS, STAR_BRIGHTNESS));
    }
  }

  // "Explosion"
  if (random(EXPLOSION_PROBABILITY) == 0) {
    int x = random(mw);
    int y = random(mh);
    for (int i=EXPLOSION_BRIGHTNESS; i > 0; i-=5) {
      matrix.drawPixel(x, y, matrix.Color(i, i, i));
      matrix.show();
      delay(DELAY_MS2);
    }
  }

  matrix.show();
  delay(DELAY_MS2);
}

void aztec() {
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);

  matrix.setTextColor(matrix.Color(60, 0, 0));  
  // Draw "AZTEC" in the center.
  int x = (matrix.width() - 15*2 - (6*5)) / 2 + 15;  // Calculate the starting x position for the text.
  
  matrix.setCursor(x, 7);
  matrix.println("AZTEC");
  
  // Draw "ROBOT" below "AZTEC".
  matrix.setCursor(x, 16);  // Change the y position to draw the text on the second row.
  matrix.println("ROBOT");
  // Draw the bouncing water drop animation.
  drawBouncingWaterDrops();
  
  matrix.show();
  delay(100);

}	

void aztec2() {
  matrix.setBrightness(128); 
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);

  matrix.setTextColor(matrix.Color(128, 0, 0));  
  // Draw "AZTEC" in the center.
  int x = (matrix.width() - 15*2 - (6*5)) / 2 + 15;  // Calculate the starting x position for the text.
  
  matrix.setCursor(x, 7);
  matrix.println("AZTEC");
  
  // Draw "ROBOT" below "AZTEC".
  matrix.setCursor(x, 16);  // Change the y position to draw the text on the second row.
  matrix.println("ROBOT");
  // Draw the bouncing water drop animation.
  drawBouncingWaterDropsBlue();
  
  matrix.show();
  delay(100);

}	

void aztec3() {
  matrix.setBrightness(100); 
  matrix.fillScreen(0);
  for(int x=0; x<mw; x++) {
    for(int y=0; y<mh; y++) {
      int wave = 64 + 63 * sin(2 * PI * (float)t / 256 + (x+y)/3.0);
      if(wave > 0) {
        matrix.drawPixel(x, y, Wheel(((x + y + wave) & 255)));
      }
    }
  }
  matrix.show();
  delay(DELAYVAL);
  t++;
  if(t >= 256) t = 0;

}	

void aztec4() {
  matrix.setBrightness(255); 
 matrix.fillScreen(0);

  for(int i=0; i<FIREWORKS; i++) {
    Firework &f = fireworks[i];

    int x = (int)f.x;
    int y = (int)f.y;
    if(x >= 0 && x < mw && y >= 0 && y < mh) {
      matrix.drawPixel(x, y, Wheel((f.age * 10) % 256));
    }

    f.x += f.vx;
    f.y += f.vy;
    f.vy += 0.11;  // Gravedad
    f.age++;

    if(f.y >= mh) {
      startFirework(f);
    }
  }

  matrix.show();
  delay(DELAYVAL);

}	



void drawBouncingWaterDrops() {
  // Update the color of the water drops.
  waterDropColor = matrix.Color(r, 0, 0);  // Only red component varies.

  // Update the red component for the next loop iteration.
  r += direction;  // Change the brightness by 1 each time.
  if (r <= 55 || r >= 70) {
    direction = -direction;  // Reverse direction when the red component reaches a limit.
  }

  for (int i = 0; i < 30; i++) {
    // Draw the water drop pixel.
    matrix.drawPixel(i % 15, waterDropPositions[i], waterDropColor);
    
    // Draw the water drop pixel on the other side of the display.
    matrix.drawPixel(matrix.width() - 1 - (i % 15), waterDropPositions[i], waterDropColor);

    // Update the y position of the water drop.
    waterDropPositions[i] += waterDropSpeeds[i];

    // If the water drop has moved off the display, make it "bounce" back.
    if (waterDropPositions[i] < 0 || waterDropPositions[i] >= matrix.height()) {
      waterDropSpeeds[i] = -waterDropSpeeds[i];
      waterDropPositions[i] += waterDropSpeeds[i];  // Move the water drop back within the display.
    }
  }
}



void drawBouncingWaterDropsBlue() {
  // Update the color of the water drops.
  if (isRed) {
    waterDropColor = matrix.Color(255, 0, 0);  // Red color.
  } else {
    waterDropColor = matrix.Color(0, 0, 255);  // Blue color.
  }
  isRed = !isRed;  // Switch color for the next loop iteration.

  for (int i = 0; i < 30; i++) {
    // Draw the water drop pixel.
    matrix.drawPixel(i % 15, waterDropPositions[i], waterDropColor);
    
    // Draw the water drop pixel on the other side of the display.
    matrix.drawPixel(matrix.width() - 1 - (i % 15), waterDropPositions[i], waterDropColor);

    // Update the y position of the water drop.
    waterDropPositions[i] += waterDropSpeeds[i];

    // If the water drop has moved off the display, make it "bounce" back.
    if (waterDropPositions[i] < 0 || waterDropPositions[i] >= matrix.height()) {
      waterDropSpeeds[i] = -waterDropSpeeds[i];
      waterDropPositions[i] += waterDropSpeeds[i];
    }
  }
}