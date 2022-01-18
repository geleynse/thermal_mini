#include <Arduino.h>

#include <memory>

#include "thermal_cam.h"
#include "thermal_display.h"

std::unique_ptr<ThermalCam> cam;
std::unique_ptr<ThermalDisplay> display;

TwoWire i2c(0);

// Buffer for full frame of temperatures.
std::array<float, CAM_BUFFER_WIDTH * CAM_BUFFER_HEIGHT> frame_buffer;

void IRAM_ATTR button1() { Serial.println("Button 1 Pressed!"); }

void IRAM_ATTR button2() { Serial.println("Button 2 Pressed!"); }

void setup() {
  while (!Serial) delay(10);
  Serial.begin(115200);

  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  attachInterrupt(BUTTON_1_PIN, button1, FALLING);
  attachInterrupt(BUTTON_2_PIN, button2, FALLING);

  cam = std::make_unique<ThermalCam>(&i2c, &frame_buffer);
  display = std::make_unique<ThermalDisplay>(&frame_buffer);
  Serial.print("h: ");
  Serial.print(display->display_pixel_height_);
  Serial.print(" w: ");
  Serial.println(display->display_pixel_width_);
}

void loop() {
  cam->ReadToBuffer();
  display->Update();
}