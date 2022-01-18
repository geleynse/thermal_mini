
#include <unity.h>

#include "linear.h"

void test_linear_interpolate(void) {
  std::array<float, 2 * 2> input = {128, 64, 32, 16};
  std::array<float, 3 * 3> output;
  LinearInterpolate<2, 2>(&input, &output);
  std::array<float, 3 * 3> expected = {128, 96, 64,  //
                                       80,  60, 40,  //
                                       32,  24, 16};
  for (int i = 0; i < 9; i++) {
    TEST_ASSERT_EQUAL(expected[i], output[i]);
  }
}

int main(int argc, char **argv) {
  // NOTE!!! Wait for >2 secs if board doesn't support software reset via
  // Serial.DTR/RTS
  // Not needed here since we are only doing local native tests.
  // delay(2000);

  UNITY_BEGIN();

  RUN_TEST(test_linear_interpolate);

  UNITY_END();

  return 0;
}