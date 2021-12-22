#include <Arduino.h>

#include <memory>

#include "thermal_cam.h"
#include "thermal_display.h"

std::unique_ptr<ThermalCam> cam;
std::unique_ptr<ThermalDisplay> display;

TwoWire i2c(0);

// Buffer for full frame of temperatures.
float frame_buffer[BUFFER_WIDTH * BUFFER_HEIGHT];

void setup() {
  while (!Serial) delay(10);
  Serial.begin(115200);

  cam = std::make_unique<ThermalCam>(&i2c, frame_buffer);
  display = std::make_unique<ThermalDisplay>(frame_buffer);
}

void loop() {
  cam->ReadToBuffer();
  display->Update();
}