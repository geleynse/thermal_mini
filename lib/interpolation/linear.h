#ifndef E8A4F9CC_D4C6_48C9_8758_443BE766D47A
#define E8A4F9CC_D4C6_48C9_8758_443BE766D47A

#include <array>

#include "stdint.h"

template <uint8_t in_width, uint8_t in_height>
void LinearInterpolate(
    std::array<float, in_width * in_height> *input,
    std::array<float, (in_width * 2 - 1) * (in_height * 2 - 1)> *output) {
  constexpr uint8_t out_width = in_width * 2 - 1;
  constexpr uint8_t out_height = in_height * 2 - 1;
  // Interpolate within even rows.
  for (uint8_t h = 0; h < out_height; h += 2) {
    for (uint8_t w = 0; w < out_width; w++) {
      float value = 0;
      int input_index = (h / 2) * in_width + (w / 2);
      if (w % 2 == 0) {
        // Even column, copy from input.
        value = (*input)[input_index];
      } else {
        // Odd column, interpolate between 2 input columns.
        auto first = (*input)[input_index];
        auto second = (*input)[input_index + 1];
        value = (first + second) / 2;
      }

      int output_index = h * out_width + w;
      (*output)[output_index] = value;
    }
  }

  // Interpolate odd rows.
  for (uint8_t h = 1; h < out_height; h += 2) {
    for (uint8_t w = 0; w < out_width; w++) {
      auto value_above = (*output)[(h - 1) * out_width + w];
      auto value_below = (*output)[(h + 1) * out_width + w];
      float value = (value_above + value_below) / 2;

      int output_index = h * out_width + w;
      (*output)[output_index] = value;
    }
  }
}

#endif /* E8A4F9CC_D4C6_48C9_8758_443BE766D47A */
