#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int moisturePin = 2;    // Digital pin connected to moisture sensor
const int servoPin = 9;       // Digital pin connected to servo motor

Servo servo;

void setup() {
  pinMode(moisturePin, INPUT);
  servo.attach(servoPin);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  int moistureLevel = digitalRead(moisturePin);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Moisture: ");
  display.println(moistureLevel == LOW ? "HIGH" : "LOW");
  display.display();

  if (moistureLevel == LOW) {
    rotateServo();
  } else {
    servo.write(0); // Stop the servo if moisture is low
  }
}

void rotateServo() {
  for (int angle = 0; angle <= 180; angle++) {
    servo.write(angle);
    delay(10); // Adjust the delay according to the speed of rotation
  }
  for (int angle = 180; angle >= 0; angle--) {
    servo.write(angle);
    delay(10); // Adjust the delay according to the speed of rotation
  }
}
