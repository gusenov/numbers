#ifndef Kellys_Max_Contrast_Set
#define Kellys_Max_Contrast_Set

int const kKellyColorsHex[] = {
  0xFFB300,  // Vivid Yellow
  0x803E75,  // Strong Purple
  0xFF6800,  // Vivid Orange
  0xA6BDD7,  // Very Light Blue
  0xC10020,  // Vivid Red
  0xCEA262,  // Grayish Yellow
  0x817066,  // Medium Gray

  // The following don't work well for people with defective color vision:
  0x007D34,  // Vivid Green
  0xF6768E,  // Strong Purplish Pink
  0x00538A,  // Strong Blue
  0xFF7A5C,  // Strong Yellowish Pink
  0x53377A,  // Strong Violet
  0xFF8E00,  // Vivid Orange Yellow
  0xB32851,  // Strong Purplish Red
  0xF4C800,  // Vivid Greenish Yellow
  0x7F180D,  // Strong Reddish Brown
  0x93AA00,  // Vivid Yellowish Green
  0x593315,  // Deep Yellowish Brown
  0xF13A13,  // Vivid Reddish Orange
  0x232C16,  // Dark Olive Green
};

double GetRed(int const color) {
  return ((color & 0xFF0000) >> 16) / 255.0F;
}

double GetGreen(int const color) {
  return ((color & 0x00FF00) >> 8) / 255.0F;
}

double GetBlue(int const color) {
  return (color & 0x0000FF) / 255.0F;
}

#endif
