#pragma once
#ifndef CONTROLLER_PPM_H
#define CONTROLLER_PPM_H

#include <map>
#include <string>
#include <optional>

namespace Controller {
  const byte NUM_CHANNELS = 8; // Number of channels in the PPM signal
  volatile unsigned int channelValues[NUM_CHANNELS];

  void readPPM() {
    static volatile unsigned long lastTime = 0;
    static volatile byte currentChannel = 0;
    
    unsigned long currentTime = micros();
    unsigned long pulseWidth = currentTime - lastTime;
    lastTime = currentTime;

    if (pulseWidth > 3000) { // Sync pulse (indicates start of a new frame)
      currentChannel = 0;
    } else if (currentChannel < NUM_CHANNELS) {
      channelValues[currentChannel++] = pulseWidth;
    }
  }

  void initialize(byte interrupt_pin) {
    pinMode(interrupt_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interrupt_pin), readPPM, RISING);
  }

  double getChannelValue(int channel) {
    return (float(channelValues[channel - 1]) - 1500)/500;
  }

  void print() {
    for (int channel = 1; channel <= NUM_CHANNELS; channel++) {
      Serial.printf("Channel %d: %f | ", channel, getChannelValue(channel));
    }
    Serial.printf("\n");
  }
}

#endif