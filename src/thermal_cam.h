#ifndef BB8229EE_5D6A_4A05_8020_77355074F923
#define BB8229EE_5D6A_4A05_8020_77355074F923

#include <Adafruit_MLX90640.h>
#include <SPI.h>
#include <Wire.h>

#define BUFFER_HEIGHT 24
#define BUFFER_WIDTH 32

class ThermalCam {
 public:
  ThermalCam(TwoWire* i2c, float* frame_buffer);

  void ReadToBuffer();

 private:
  Adafruit_MLX90640 mlx;
  bool ready = false;
  TwoWire* i2c_bus_;
  float* frame_buffer_;
};

#endif /* BB8229EE_5D6A_4A05_8020_77355074F923 */
