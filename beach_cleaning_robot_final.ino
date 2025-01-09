#include <controller_ppm.h>
#include <system.h>

const int SPEED_CHANNEL = 3;
const int FORWARD_CHANNEL = 2;
const int SIDEWAY_CHANNEL = 4;
const int CONVEYOR_CHANNEL = 6;
const int COLLECTOR_CHANNEL = 5;

const int CHANNEL_PIN = 26;

void setup() {
  Serial.begin(9600);
  Controller::initialize(CHANNEL_PIN);

  motor1.setPin(21, 13);  //left
  motor2.setPin(22, 23);  //right
  motor3.setPin(16, 17);  //left
  motor4.setPin(14, 15);  //right
  motor_conveyor.setPin(32, 33);
  motor_collector.setPin(18, 19);
}

void loop() {
  //get values from the channels
  double forward = Controller::getChannelValue(FORWARD_CHANNEL);
  double speed = Controller::getChannelValue(SPEED_CHANNEL)/2 + 0.5;
  double sideway = Controller::getChannelValue(SIDEWAY_CHANNEL);
  double conveyor_mode = Controller::getChannelValue(CONVEYOR_CHANNEL);
  double collector_mode = Controller::getChannelValue(COLLECTOR_CHANNEL);
  
  move(forward, sideway, speed);
  move_conveyor(conveyor_mode);
  move_collector(collector_mode);
  
  delay(100);
}