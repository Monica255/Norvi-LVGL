/*******************************************************************************
 * Size: 13 px
 * Bpp: 1
 * Opts: --bpp 1 --size 13 --font C:/Users/pcu2/SquareLine/assets/arialceb.ttf -o C:/Users/pcu2/SquareLine/assets\ui_font_arial13.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_ARIAL13
#define UI_FONT_ARIAL13 1
#endif

#if UI_FONT_ARIAL13

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf7, 0xc0,

    /* U+0022 "\"" */
    0xde, 0xe4,

    /* U+0023 "#" */
    0x36, 0x4b, 0xf9, 0x66, 0xdf, 0xd2, 0x24, 0x58,

    /* U+0024 "$" */
    0x10, 0xf9, 0x52, 0x87, 0x7, 0x85, 0xeb, 0x7c,
    0x70, 0x40,

    /* U+0025 "%" */
    0xe3, 0x2c, 0x8b, 0x63, 0x90, 0x9, 0x82, 0xb1,
    0x24, 0xcb, 0x23, 0x80,

    /* U+0026 "&" */
    0x38, 0x6c, 0x6c, 0x78, 0x78, 0xda, 0x8e, 0xce,
    0x7b,

    /* U+0027 "'" */
    0xf8,

    /* U+0028 "(" */
    0x6b, 0x69, 0x24, 0xd9, 0x30,

    /* U+0029 ")" */
    0x46, 0x62, 0x33, 0x33, 0x26, 0x64,

    /* U+002A "*" */
    0x27, 0xc8, 0xa0, 0x0,

    /* U+002B "+" */
    0x30, 0xcf, 0xcc, 0x30, 0xc0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x32, 0x26, 0x44, 0x4c, 0x80,

    /* U+0030 "0" */
    0x73, 0x6c, 0xa3, 0x8e, 0x38, 0xb6, 0x70,

    /* U+0031 "1" */
    0x37, 0xfb, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0x38, 0xc9, 0x18, 0x61, 0xc7, 0x1c, 0x30, 0xfe,

    /* U+0033 "3" */
    0x38, 0xd8, 0x30, 0xc0, 0xc0, 0xf1, 0xb6, 0x38,

    /* U+0034 "4" */
    0xc, 0x38, 0x71, 0xe6, 0xc9, 0xbf, 0x86, 0xc,

    /* U+0035 "5" */
    0x7b, 0xc, 0x3e, 0xcc, 0x30, 0xf2, 0x70,

    /* U+0036 "6" */
    0x7b, 0x2c, 0x2e, 0xcb, 0x3c, 0xf2, 0x78,

    /* U+0037 "7" */
    0xfc, 0x61, 0xc, 0x21, 0x86, 0x18, 0x60,

    /* U+0038 "8" */
    0x7b, 0x2c, 0xbc, 0xda, 0x38, 0xf6, 0x70,

    /* U+0039 "9" */
    0x38, 0x9b, 0x12, 0x77, 0xe0, 0xd1, 0x36, 0x38,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0x3d, 0x80,

    /* U+003C "<" */
    0xc, 0xff, 0x30, 0xf8, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0xc3, 0xc3, 0x7b, 0x88, 0x0,

    /* U+003F "?" */
    0x7b, 0x30, 0x43, 0x18, 0xc0, 0xc, 0x30,

    /* U+0040 "@" */
    0xf, 0xc1, 0x83, 0x9, 0xfc, 0x93, 0x25, 0x99,
    0x68, 0xcb, 0x46, 0x5b, 0x34, 0x4f, 0xc3, 0x0,
    0x8c, 0x1c, 0x1f, 0x80,

    /* U+0041 "A" */
    0x1c, 0xe, 0x7, 0x86, 0xc3, 0x63, 0x99, 0xfc,
    0xc3, 0xc1, 0x80,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xfc, 0xc6, 0xc3, 0xc3,
    0xfe,

    /* U+0043 "C" */
    0x3c, 0x66, 0xc2, 0xc0, 0xc0, 0xc0, 0xc3, 0xc6,
    0x3c,

    /* U+0044 "D" */
    0xfc, 0xc6, 0xc2, 0xc3, 0xc3, 0xc3, 0xc2, 0xc6,
    0xfc,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xf, 0xf8, 0x30, 0x60, 0xfe,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xff, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3e, 0x63, 0xc2, 0xc0, 0xcf, 0xc3, 0xc3, 0x63,
    0x3e,

    /* U+0048 "H" */
    0xc3, 0x87, 0xe, 0x1f, 0xf8, 0x70, 0xe1, 0xc2,

    /* U+0049 "I" */
    0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x34, 0xf3, 0x78,

    /* U+004B "K" */
    0xc7, 0xce, 0xdc, 0xf8, 0xf8, 0xec, 0xce, 0xc6,
    0xc3,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xfe,

    /* U+004D "M" */
    0xe3, 0xf1, 0xf9, 0xfe, 0xff, 0x5e, 0xaf, 0x77,
    0xbb, 0xd9, 0x80,

    /* U+004E "N" */
    0xc3, 0xc7, 0x8f, 0x9d, 0xbb, 0x73, 0xe7, 0xc6,

    /* U+004F "O" */
    0x3c, 0x31, 0xb0, 0xd8, 0x3c, 0x1e, 0xf, 0xd,
    0xc6, 0x3c, 0x0,

    /* U+0050 "P" */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd8, 0x30, 0x60, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x71, 0xb0, 0xd8, 0x2c, 0x1e, 0xf, 0x2d,
    0xde, 0x3f, 0x80, 0x80,

    /* U+0052 "R" */
    0xfe, 0xc6, 0xc3, 0xc6, 0xfc, 0xcc, 0xce, 0xc6,
    0xc3,

    /* U+0053 "S" */
    0x3e, 0x67, 0x60, 0x7c, 0x3f, 0xf, 0x43, 0x63,
    0x3e,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c,

    /* U+0056 "V" */
    0xc3, 0x31, 0x98, 0xcc, 0xc3, 0x61, 0xb0, 0xf0,
    0x38, 0x1c, 0x0,

    /* U+0057 "W" */
    0xc6, 0x3c, 0x73, 0x6f, 0x36, 0xf2, 0x6d, 0x66,
    0x9e, 0x39, 0xe3, 0x8c, 0x30, 0xc0,

    /* U+0058 "X" */
    0x63, 0x33, 0xd, 0x83, 0x81, 0xc1, 0xe0, 0xd8,
    0xce, 0xe3, 0x0,

    /* U+0059 "Y" */
    0xe3, 0x31, 0x8d, 0x87, 0x81, 0xc0, 0xc0, 0x60,
    0x30, 0x18, 0x0,

    /* U+005A "Z" */
    0x7f, 0x6, 0xc, 0x1c, 0x18, 0x30, 0x60, 0xe0,
    0xff,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x70,

    /* U+005C "\\" */
    0x8c, 0x44, 0x46, 0x22, 0x30,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0xf0,

    /* U+005E "^" */
    0x31, 0xc7, 0xb6, 0xcc,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x44,

    /* U+0061 "a" */
    0x7c, 0x88, 0x33, 0xec, 0x49, 0x9d, 0x80,

    /* U+0062 "b" */
    0xc3, 0xf, 0xb3, 0xc7, 0x1c, 0x73, 0xf8,

    /* U+0063 "c" */
    0x7b, 0x38, 0x20, 0x83, 0x37, 0x80,

    /* U+0064 "d" */
    0xc, 0x37, 0xf3, 0x8e, 0x38, 0xf3, 0x7c,

    /* U+0065 "e" */
    0x38, 0xdb, 0x1f, 0xfc, 0xc, 0x8f, 0x0,

    /* U+0066 "f" */
    0x7b, 0x3c, 0xc6, 0x31, 0x8c, 0x60,

    /* U+0067 "g" */
    0x7f, 0x38, 0xe3, 0x8f, 0x37, 0xc3, 0xcd, 0xe0,

    /* U+0068 "h" */
    0xc3, 0xf, 0xb3, 0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0069 "i" */
    0xcf, 0xff, 0xc0,

    /* U+006A "j" */
    0x30, 0x33, 0x33, 0x33, 0x33, 0x36,

    /* U+006B "k" */
    0xc3, 0xd, 0xbe, 0xf3, 0xcd, 0xb6, 0xcc,

    /* U+006C "l" */
    0xff, 0xff, 0xc0,

    /* U+006D "m" */
    0xbb, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcc,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xfb, 0x3c, 0x71, 0xc7, 0x3f, 0xb0, 0xc3, 0x0,

    /* U+0071 "q" */
    0x7f, 0x38, 0xe3, 0x8f, 0x37, 0xc3, 0xc, 0x30,

    /* U+0072 "r" */
    0xfc, 0xcc, 0xcc, 0xc0,

    /* U+0073 "s" */
    0x7c, 0x89, 0xc3, 0xe0, 0xf8, 0x9f, 0x0,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x66, 0x70,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0xc0,

    /* U+0076 "v" */
    0xc6, 0x8d, 0xb3, 0x63, 0x87, 0x6, 0x0,

    /* U+0077 "w" */
    0xcc, 0xd3, 0x34, 0xe9, 0xfe, 0x7b, 0x8c, 0xc3,
    0x30,

    /* U+0078 "x" */
    0x6e, 0xd8, 0xe1, 0xc3, 0x8d, 0xb9, 0x80,

    /* U+0079 "y" */
    0xc6, 0x8d, 0xb3, 0x62, 0x87, 0xe, 0x8, 0x30,
    0xc0,

    /* U+007A "z" */
    0xfc, 0x71, 0x8c, 0x71, 0x8f, 0xc0,

    /* U+007B "{" */
    0x39, 0x8, 0x46, 0x61, 0x84, 0x21, 0x8, 0x70,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xe1, 0x8, 0x43, 0xc, 0xc4, 0x21, 0x19, 0xc0,

    /* U+007E "~" */
    0x73, 0x1c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 69, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 99, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 185, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 49, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 46, .adv_w = 69, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 51, .adv_w = 69, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 57, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 61, .adv_w = 121, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 66, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 67, .adv_w = 69, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 68, .adv_w = 58, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 58, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 116, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 69, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 69, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 151, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 157, .adv_w = 121, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 160, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 166, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 193, .adv_w = 150, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 162, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 150, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 58, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 173, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 150, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 162, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 162, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 340, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 139, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 150, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 139, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 196, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 139, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 139, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 69, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 436, .adv_w = 58, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 69, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 446, .adv_w = 121, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 450, .adv_w = 116, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 451, .adv_w = 69, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 452, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 69, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 500, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 58, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 58, .box_w = 4, .box_h = 12, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 516, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 58, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 185, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 127, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 127, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 555, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 563, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 69, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 127, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 162, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 104, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 81, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 631, .adv_w = 58, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 634, .adv_w = 81, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 642, .adv_w = 121, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 34,
    1, 58,
    18, 18,
    34, 1,
    34, 53,
    34, 55,
    34, 56,
    34, 58,
    34, 87,
    34, 88,
    34, 90,
    39, 13,
    39, 15,
    39, 34,
    45, 1,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 90,
    49, 1,
    49, 13,
    49, 15,
    49, 34,
    51, 55,
    51, 56,
    51, 58,
    53, 13,
    53, 14,
    53, 15,
    53, 27,
    53, 28,
    53, 34,
    53, 48,
    53, 66,
    53, 68,
    53, 70,
    53, 74,
    53, 80,
    53, 83,
    53, 84,
    53, 86,
    53, 88,
    53, 90,
    55, 13,
    55, 14,
    55, 15,
    55, 27,
    55, 28,
    55, 34,
    55, 66,
    55, 70,
    55, 74,
    55, 80,
    55, 83,
    55, 86,
    55, 90,
    56, 13,
    56, 14,
    56, 15,
    56, 27,
    56, 28,
    56, 34,
    56, 66,
    56, 70,
    56, 74,
    56, 80,
    56, 83,
    56, 86,
    56, 90,
    58, 1,
    58, 13,
    58, 14,
    58, 15,
    58, 27,
    58, 28,
    58, 34,
    58, 66,
    58, 70,
    58, 74,
    58, 80,
    58, 81,
    58, 82,
    58, 86,
    58, 87,
    83, 13,
    83, 15,
    87, 13,
    87, 15,
    88, 13,
    88, 15,
    90, 13,
    90, 15
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -8, -4, -11, -8, -15, -15, -11, -19,
    -8, -4, -8, -23, -23, -11, -4, -15,
    -15, -11, -19, -8, -4, -27, -27, -15,
    -4, -4, -8, -23, -11, -23, -23, -23,
    -15, -4, -15, -15, -15, -4, -15, -11,
    -15, -15, -15, -15, -19, -11, -19, -11,
    -11, -15, -11, -11, -4, -15, -11, -8,
    -8, -11, -4, -11, -4, -4, -11, -8,
    -4, -2, -4, -4, -4, -4, -4, -23,
    -11, -23, -15, -15, -19, -11, -11, -8,
    -15, -11, -15, -11, -11, -11, -11, -15,
    -15, -8, -8, -15, -15
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 93,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_arial13 = {
#else
lv_font_t ui_font_arial13 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_ARIAL13*/

