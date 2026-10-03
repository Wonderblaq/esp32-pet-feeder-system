#include <ESP32Servo.h>
const int BUTTON_PIN = 4; 
const int LED_PIN = 13;
bool ledStatus = false;
Servo servo;
int SERVO_PIN = 18;
const int TRIG_PIN = 5;
const int ECHO_PIN = 17; 
int lastButtonState = HIGH; /* default lastbuttonstate to high
because of input pullup, which means hgih == led off
*/
// --- Telemetry Configurations ---
unsigned long lastSensorCheckTime = 0;   // Stores the timestamp of the last ultrasonic reading
const unsigned long sensorInterval = 2000; // 2000ms (2 seconds) background task interval

const float HOPPER_TOTAL_DEPTH = 30.0;   // The maximum empty depth we calibrated
const float LOW_FOOD_THRESHOLD = 5.0;    // Warning threshold for remaining food height

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  servo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);
  // Configures GPIO 4 as an Input AND activates the internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  servo.write(0);
  Serial.println("--- CPE 400: Ultrasonic Calibration Mode ---");
  Serial.println("Place your sensor at the top of your empty container.");
}

void loop() {
  // put your main code here, to run repeatedly:
  // check the eelctrical state of our input button
  int currentButtonState = digitalRead(BUTTON_PIN);
  if( // logic of condition means check  if button is pressed 
    currentButtonState == LOW && lastButtonState == HIGH){
      ledStatus = !ledStatus; // flip or toggle the ledSatus
      servo.write(180);
      digitalWrite(LED_PIN, ledStatus);
      delay(3000);
      servo.write(90);
      delay(3000);
      servo.write(0);
      digitalWrite(LED_PIN, LOW);
      
  }
  
  lastButtonState = currentButtonState;
  
}
