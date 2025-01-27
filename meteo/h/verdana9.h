const uint8_t verdana9pt7bBitmaps[] PROGMEM = {
  0xFF, 0xF0, 0xFC, 0x02, 0x06, 0x06, 0x04, 0x0C, 0x0C, 0x08, 0x18, 0x10,
  0x10, 0x30, 0x20, 0x60, 0x60, 0x40, 0xC0, 0x80, 0x1E, 0x3F, 0x98, 0xE8,
  0x3C, 0x1E, 0x0F, 0x07, 0x83, 0xC1, 0xA0, 0xD8, 0xEF, 0xE3, 0xE0, 0x18,
  0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF,
  0x3E, 0x3F, 0x90, 0xE0, 0x30, 0x18, 0x18, 0x08, 0x18, 0x18, 0x18, 0x18,
  0x1F, 0xFF, 0xF8, 0x3E, 0x3F, 0x90, 0x60, 0x30, 0x30, 0xF0, 0x7C, 0x03,
  0x01, 0x80, 0xF0, 0xFF, 0xE3, 0xE0, 0x03, 0x01, 0xC0, 0xB0, 0x4C, 0x23,
  0x10, 0xC8, 0x33, 0xFF, 0xFF, 0xC0, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0xFF,
  0xFF, 0xC0, 0xC0, 0xC0, 0xFC, 0xFE, 0x03, 0x03, 0x03, 0x87, 0xFE, 0x7C,
  0x0F, 0x1F, 0x9C, 0x0C, 0x04, 0x06, 0xFB, 0xFF, 0x83, 0xC0, 0xE0, 0x58,
  0x6F, 0xE1, 0xE0, 0xFF, 0xFF, 0xC0, 0x20, 0x30, 0x30, 0x10, 0x18, 0x08,
  0x0C, 0x04, 0x06, 0x06, 0x03, 0x00, 0x3E, 0x3F, 0x98, 0x78, 0x36, 0x19,
  0xD8, 0xFC, 0x83, 0xC0, 0xE0, 0xF8, 0x6F, 0xF3, 0xE0, 0x3E, 0x3F, 0xB8,
  0xF8, 0x3C, 0x1E, 0x0D, 0xFE, 0x7F, 0x01, 0x80, 0xC1, 0xCF, 0xC7, 0xC0,
  0xFC, 0x03, 0xF0 };

const GFXglyph verdana9pt7bGlyphs[] PROGMEM = {
  {     0,   6,   2,   8,    1,   -6 },   // 0x2D '-'
  {     2,   2,   3,   7,    2,   -2 },   // 0x2E '.'
  {     3,   8,  17,   8,    0,  -13 },   // 0x2F '/'
  {    20,   9,  13,  11,    1,  -12 },   // 0x30 '0'
  {    35,   8,  13,  11,    2,  -12 },   // 0x31 '1'
  {    48,   9,  13,  11,    1,  -12 },   // 0x32 '2'
  {    63,   9,  13,  11,    1,  -12 },   // 0x33 '3'
  {    78,  10,  13,  11,    1,  -12 },   // 0x34 '4'
  {    95,   8,  13,  11,    2,  -12 },   // 0x35 '5'
  {   108,   9,  13,  11,    1,  -12 },   // 0x36 '6'
  {   123,   9,  13,  11,    1,  -12 },   // 0x37 '7'
  {   138,   9,  13,  11,    1,  -12 },   // 0x38 '8'
  {   153,   9,  13,  11,    1,  -12 },   // 0x39 '9'
  {   168,   2,  10,   8,    3,   -9 } }; // 0x3A ':'

const GFXfont verdana9pt7b PROGMEM = {
  (uint8_t  *)verdana9pt7bBitmaps,
  (GFXglyph *)verdana9pt7bGlyphs,
  0x2D, 0x3A, 22 };

// Approx. 276 bytes
