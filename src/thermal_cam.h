#ifndef BB8229EE_5D6A_4A05_8020_77355074F923
#define BB8229EE_5D6A_4A05_8020_77355074F923

#include <Adafruit_MLX90640.h>
#include <SPI.h>
#include <Wire.h>

#include <array>

#ifndef CAM_BUFFER_HEIGHT
#define CAM_BUFFER_HEIGHT 24
#endif
#ifndef CAM_BUFFER_WIDTH
#define CAM_BUFFER_WIDTH 32
#endif

// CAM_BUFFER_HEIGHT * 2 - 1
#define DISPLAY_BUFFER_HEIGHT 47
// CAM_BUFFER_WIDTH * 2 - 1
#define DISPLAY_BUFFER_WIDTH 63

class ThermalCam {
 public:
  ThermalCam(
      TwoWire* i2c,
      std::array<float, CAM_BUFFER_WIDTH * CAM_BUFFER_HEIGHT>* frame_buffer);

  void ReadToBuffer();

 private:
  Adafruit_MLX90640 mlx;
  bool ready = false;
  TwoWire* i2c_bus_;
  std::array<float, CAM_BUFFER_WIDTH * CAM_BUFFER_HEIGHT>* frame_buffer_;
};

#endif /* BB8229EE_5D6A_4A05_8020_77355074F923 */
