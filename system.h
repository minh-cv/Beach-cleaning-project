#pragma once
#ifndef MOVING_SYSTEM_H
#define MOVING_SYSTEM_H

#include <motor.h>
#include <cmath>

//Motors for moving system
Motor motor1, //top left
      motor2, //top right
      motor3, //bottom left
      motor4; //bottom right

//Move the motors in the moving system
void move(double forward, double sideway, double speed) {
  auto move_left = [](double speed) {
    if (abs(speed) < 0.3) {speed = 0;}
    motor1.turn(speed);
    motor3.turn(speed);
  };
  auto move_right = [](double speed) {
    if (abs(speed) < 0.3) {speed = 0;}
    motor2.turn(speed);
    motor4.turn(speed);
  };
  
  if (abs(forward) < 1.0/3 && abs(sideway) < 1.0/3) {
    move_left(0);
    move_right(0);
    return;
  }

  double angle = atan2(forward, sideway);
  bool is_negative = angle < 0;
  angle = abs(angle);
  double left_speed, right_speed;

  if (0 <= angle && angle < PI/2) {
    left_speed = 1;
    right_speed = std::lerp(-1, 1, angle/(PI/2));
  }
  else {
    right_speed = 1;
    left_speed = std::lerp(1, -1, angle/(PI/2) - 1);
  }

  if (is_negative) {
    std::swap(left_speed, right_speed);
    left_speed *= -1; right_speed *= -1;
  }

  left_speed *= speed;
  right_speed *= speed;

  move_left(left_speed);
  move_right(right_speed);
}

Motor motor_conveyor,
      motor_collector;

void move_conveyor(double mode) {
  if (mode < -0.5) {motor_conveyor.stop();}
  else if (mode > 0.5) {motor_conveyor.turn(-1);}
  else {motor_conveyor.turn(1);}
}

void move_collector(double mode) {
  static double current_speed = 0;
  const double SPEED_CHANGE = 0.02;

  int direction = mode < -0.5 ? -1 : 1;
  current_speed = std::clamp(current_speed + direction*SPEED_CHANGE, 0.0, 1.0);
  if (current_speed < 1.0/3) motor_collector.stop();
  else motor_collector.turn(current_speed);
}

#endif