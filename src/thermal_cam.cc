#include "thermal_cam.h"

ThermalCam::ThermalCam(TwoWire* i2c, float* frame_buffer)
    : i2c_bus_(i2c), frame_buffer_(frame_buffer) {
  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, i2c)) {
    ready = true;
    Serial.println("MLX90640 not found!");
    return;
  }

  Serial.println("Found Adafruit MLX90640");
  Serial.print("Serial number: ");
  Serial.print(mlx.serialNumber[0], HEX);
  Serial.print(mlx.serialNumber[1], HEX);
  Serial.println(mlx.serialNumber[2], HEX);

  mlx.setMode(MLX90640_CHESS);
  mlx.setResolution(MLX90640_ADC_18BIT);
  mlx.setRefreshRate(MLX90640_16_HZ);
  i2c->setClock(3400000);  // max 3.4 MHz
  Serial.println("Thermal Cam initialized");
}

void ThermalCam::ReadToBuffer() {
  int result;
  try {
    result = mlx.getFrame(this->frame_buffer_);
  } catch (const std::exception& e) {
    Serial.print("Thermal Cam error caught: ");
    Serial.println(e.what());
    return;
  }

  if (result != 0) {
    Serial.print("Unexpected value from Thermal Cam read: ");
    Serial.println(result);
  }
}