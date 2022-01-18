#include "thermal_display.h"

#include "linear.h"

ThermalDisplay::ThermalDisplay(
    std::array<float, CAM_BUFFER_WIDTH * CAM_BUFFER_HEIGHT> *input_frame_buffer)
    : tft_(TFT_WIDTH, TFT_HEIGHT), input_frame_buffer_(input_frame_buffer) {
  Serial.println("Display setup begin.");
  tft_.init();
  tft_.setRotation(1);
  tft_.fillScreen(TFT_BLACK);
  tft_.drawString("Starting", tft_.width() / 2 - 16, tft_.height() / 2 - 16);

  // Keep pixels square
  display_pixel_width_ = display_pixel_height_ =
      tft_.width() / DISPLAY_BUFFER_WIDTH;
  Serial.print("Display initialized with pixel size: ");
  Serial.print(display_pixel_width_);
  Serial.print(",");
  Serial.println(display_pixel_height_);
};

void ThermalDisplay::Update() {
  LinearInterpolate<CAM_BUFFER_WIDTH, CAM_BUFFER_HEIGHT>(input_frame_buffer_,
                                                         &display_frame_buffer);

  for (uint8_t h = 0; h < DISPLAY_BUFFER_HEIGHT; h++) {
    for (uint8_t w = 0; w < DISPLAY_BUFFER_WIDTH; w++) {
      float t = display_frame_buffer[h * DISPLAY_BUFFER_WIDTH + w];

      t = min(t, maxtemp_);
      t = max(t, mintemp_);

      uint8_t colorIndex = map(t, mintemp_, maxtemp_, 0, 255);

      colorIndex = constrain(colorIndex, 0, 255);
      tft_.fillRect(display_pixel_width_ * w,
                    display_pixel_height_ * (DISPLAY_BUFFER_HEIGHT - 1 - h),
                    display_pixel_height_, display_pixel_width_,
                    camColors_[colorIndex]);
    }
  }
}