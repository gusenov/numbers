#include <iostream>
#include <complex>
#include <map>

#include <unistd.h>

#include <g2.h>
#include <g2_X11.h>

#include "kelly_colors_hex.h"
#include "utils.h"


int const kWindowWidth  = 777;
int const kWindowHeight = 777;

double const kXCoordinateOfNewOrigin = kWindowWidth  / 2.0;
double const kYCoordinateOfNewOrigin = kWindowHeight / 2.0;
double kXScalingFactor = 1;
double kYScalingFactor = 1;

int minBase = 1, maxBase;
int minExponent = 0, maxExponent = 3;

int const kRadiusFactor = 20;

std::map<int, int> inkMap;


int main(int argc, char const * argv[]) {

  // Open a simple X11 window (physical device device):
  int physicalDeviceId = g2_open_X11(kWindowWidth, kWindowHeight);

  // Ось X:
  g2_line(physicalDeviceId,
          0, kYCoordinateOfNewOrigin,  // x1, y1
          kWindowWidth, kYCoordinateOfNewOrigin);  // x2, y2

  // Ось Y:
  g2_line(physicalDeviceId,
          kXCoordinateOfNewOrigin, 0,  // x1, y1
          kXCoordinateOfNewOrigin, kWindowHeight);  // x2, y2

  // Set the user coordinate system:
  g2_set_coordinate_system(physicalDeviceId, kXCoordinateOfNewOrigin, kYCoordinateOfNewOrigin, kXScalingFactor, kYScalingFactor);

  std::cout << "|  ";
  for (int j = minExponent; j <= maxExponent; ++j) {
    double im = j;
    std::cout << "| " << im << "i ";
    if (j == maxExponent)
      std::cout << "|" << std::endl;
  }

  std::cout << "| - ";
  for (int j = minExponent; j <= maxExponent; ++j) {
    std::cout << "| - ";
    if (j == maxExponent)
      std::cout << "|" << std::endl;
  }

  for (int i = minBase, color = 0; i < SizeOfStaticArray(kKellyColorsHex); ++i) {

    // Create an ink:
    int ink;
    if ( inkMap.find(kKellyColorsHex[color]) == inkMap.end() ) {
      ink = g2_ink(physicalDeviceId, GetRed  (kKellyColorsHex[color]),
                                     GetGreen(kKellyColorsHex[color]),
                                     GetBlue (kKellyColorsHex[color]));
      inkMap.insert(std::make_pair(kKellyColorsHex[color], ink));
      ++color;
    } else {
      ink = inkMap[kKellyColorsHex[color]];
    }


    // Set pen color for all following operations:
    g2_pen(physicalDeviceId, ink);

    int radius = i * kRadiusFactor;
    g2_circle(physicalDeviceId, 0, 0, radius);

    double x = i;

    std::cout << "| " << x << " ";

    for (int j = minExponent; j <= maxExponent; ++j) {
      double re = 0;
      double im = j;
      std::complex<double> y(re, im);
      auto z = std::pow(x, y);

      // std::cout << x << " ^ " << im << "i = " << z << std::endl;

      std::cout << "| " << z << " ";
      if (j == maxExponent)
        std::cout << "|";

      g2_filled_circle(physicalDeviceId, z.real() * radius, z.imag() * radius, 4.0);

    }  // j

    std::cout << std::endl;
  }  // i


  g2_pen(physicalDeviceId, g2_ink(physicalDeviceId, 0, 0, 0));

  std::complex<double> prev_z;
  int prev_r;
  for (int j = minExponent; j <= maxExponent; ++j) {
    for (int i = minBase; i < SizeOfStaticArray(kKellyColorsHex); ++i) {
      double x = i;

      double re = 0, im = j;
      std::complex<double> y(re, im);
      auto z = std::pow(x, y);

      int radius = i * kRadiusFactor;
      if (i > 2)
        g2_line(physicalDeviceId, prev_z.real() * prev_r, prev_z.imag() * prev_r,
                                       z.real() * radius,      z.imag() * radius);

      prev_z = z;
      prev_r = radius;
    }
  }

  std::cout << "\nDone.\n[Enter]\n";
  std::cin.get();

  // Close and delete a device:
  g2_close(physicalDeviceId);

  return 0;
}
