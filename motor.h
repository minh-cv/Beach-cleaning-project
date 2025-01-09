#pragma once
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

// Define the Motor class
class Motor {
private:
  uint8_t rpwm_output;
  uint8_t lpwm_output;

public:
  Motor() = default;

  //Initialize and set the pin to OUTPUT mode
  Motor(uint8_t rpwm_output, uint8_t lpwm_output)
    : rpwm_output(rpwm_output),
      lpwm_output(lpwm_output) {
    pinMode(rpwm_output, OUTPUT);
    pinMode(lpwm_output, OUTPUT);
  }

  void setLeftPin(uint8_t pin) {
    lpwm_output = pin;
    pinMode(pin, OUTPUT);
  }

  void setRightPin(uint8_t pin) {
    rpwm_output = pin;
    pinMode(pin, OUTPUT);
  }

  void setPin(uint8_t left, uint8_t right) {
    setLeftPin(left);
    setRightPin(right);
  }

  uint8_t getLeftPin() const {return lpwm_output;}
  uint8_t getRightPin() const {return rpwm_output;}

  //Turn left, right or stop the motor depends on the speed. speed is in range [-1, 1]
  void turn(double speed) const {
    if (speed >= 0) {
      analogWrite(lpwm_output, 0);
      analogWrite(rpwm_output, 1023*speed);
    }
    else {
      analogWrite(rpwm_output, 0);
      analogWrite(lpwm_output, -1023*speed);
    }
  }

  void stop() const {
    turn(0);
  }
};

#endif