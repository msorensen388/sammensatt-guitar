#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
const int NUM_KNOBS = 4;

class RotaryEncoder {
  public: 
    int clockPin;
    int dtPin;
    int swPin;
    int clockLastState;
    int counter;
    unsigned long lastButtonPress;
    
    RotaryEncoder(int c, int dt, int sw = 0) {
      clockPin = c;
      dtPin = dt;

      pinMode(c, INPUT);
      pinMode(dt, INPUT);

      if (sw != 0) {
        lastButtonPress = 0;
        swPin = sw;
        pinMode(sw, INPUT);
      }
    }
};

RotaryEncoder knob1(8, 9, 10);
RotaryEncoder knob2(6, 7);
RotaryEncoder knob3(4, 5);
RotaryEncoder knob4(2, 3);

RotaryEncoder knobs[NUM_KNOBS] = {knob1, knob2, knob3, knob4};

void setup() {
  Serial.begin(31250);

  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  

  // Rotary Encoders
  for (int i = 0; i < NUM_KNOBS; i++) {
    knobs[i].clockLastState = digitalRead(knobs[i].clockPin);
  }
  
  if (status == 0) {
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
    mpu.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
  }
  
}

void loop() {
  loopAccelerometer();
  loopRotaryEncoders();
}


void loopRotaryEncoders() {

  for (int i = 0; i < NUM_KNOBS; i++) {
    int clockState = digitalRead(knobs[i].clockPin);
    String message = "";

    // Rotation
    if (clockState != knobs[i].clockLastState) {
      if (digitalRead(knobs[i].dtPin) != clockState) {
        knobs[i].counter = incrementCounter(knobs[i].counter, true);
        message = "inc";
      } else {
        knobs[i].counter = incrementCounter(knobs[i].counter, false);
        message = "dec";
      }
      knobs[i].clockLastState = clockState;
      
      Serial.print("Rotary ");
      Serial.print(i + 1);
      Serial.print(" ");
      Serial.print(message);
      Serial.println();
    }

    //If we detect LOW signal, button is pressed
    if (digitalRead(knobs[i].swPin) == 0) {
      //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      if (millis() - knobs[i].lastButtonPress > 50) {
        Serial.print("Button ");
        Serial.print(i + 1);
        Serial.print(" ");
        Serial.print(message);
        Serial.println();
      }

      // Remember last button press event
      knobs[i].lastButtonPress = millis();
    }
  }
}

int incrementCounter(int currentVal, bool increment) {

  int newVal;
  if (increment) {
    newVal = currentVal + 1;
  } else {
    newVal = currentVal - 1;
  }

  return newVal;
}

void loopAccelerometer() {
  mpu.update();

  if ((millis() - timer) > 15) { // print data every 10ms
	  Serial.print("Angle ");
    Serial.print(mpu.getAngleX());
    Serial.print(" ");
    Serial.print(mpu.getAngleY());
    Serial.print(" ");
    Serial.println(mpu.getAngleZ());
    timer = millis();  
  }
}
