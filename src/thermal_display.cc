#include "thermal_display.h"

ThermalDisplay::ThermalDisplay(float *frame_buffer)
    : tft_(TFT_WIDTH, TFT_HEIGHT), frame_buffer_(frame_buffer) {
  Serial.println("Display setup begin.");
  tft_.init();
  tft_.setRotation(1);
  tft_.fillScreen(TFT_BLACK);
  tft_.drawString("Starting", tft_.width() / 2 - 16, tft_.height() / 2 - 16);

  // Keep pixels square
  this->display_pixel_width_ = this->display_pixel_height_ = tft_.width() / 32;
  Serial.println("Display initialized.");
};

void ThermalDisplay::Update() {
  for (uint8_t h = 0; h < 24; h++) {
    for (uint8_t w = 0; w < 32; w++) {
      float t = this->frame_buffer_[h * 32 + w];

      t = min(t, this->maxtemp_);
      t = max(t, this->mintemp_);

      uint8_t colorIndex = map(t, this->mintemp_, this->maxtemp_, 0, 255);

      colorIndex = constrain(colorIndex, 0, 255);
      tft_.fillRect(this->display_pixel_width_ * w,
                    this->display_pixel_height_ * (23 - h),
                    this->display_pixel_height_, this->display_pixel_width_,
                    camColors_[colorIndex]);
    }
  }
}