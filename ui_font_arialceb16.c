/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:/Users/pcu2/SquareLine/assets/arialceb.ttf -o C:/Users/pcu2/SquareLine/assets\ui_font_arialceb16.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_ARIALCEB16
#define UI_FONT_ARIALCEB16 1
#endif

#if UI_FONT_ARIALCEB16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf6, 0xd2, 0x41, 0xb0,

    /* U+0022 "\"" */
    0xdf, 0x7c, 0xf3,

    /* U+0023 "#" */
    0x1b, 0x9, 0x8c, 0xdf, 0xff, 0xf9, 0xb0, 0x99,
    0xff, 0xff, 0xb2, 0x1b, 0x9, 0x80,

    /* U+0024 "$" */
    0x10, 0xfb, 0xf6, 0xbd, 0x1e, 0x1e, 0x1f, 0x1e,
    0x2f, 0x5f, 0xf7, 0xc2, 0x4, 0x0,

    /* U+0025 "%" */
    0x70, 0xcf, 0x88, 0x99, 0x89, 0x90, 0x73, 0x0,
    0x2e, 0x6, 0xf0, 0x59, 0xd, 0x90, 0x99, 0x18,
    0xf3, 0xe,

    /* U+0026 "&" */
    0x3c, 0x1f, 0x86, 0x61, 0x98, 0x3e, 0xf, 0x6,
    0xd3, 0x3e, 0xc7, 0xb1, 0xef, 0xfd, 0xf2,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x36, 0x6c, 0xcc, 0xcc, 0xcc, 0xc4, 0x66, 0x30,

    /* U+0029 ")" */
    0x8c, 0x46, 0x66, 0x67, 0x66, 0x66, 0x4c, 0x80,

    /* U+002A "*" */
    0x30, 0xdf, 0xcc, 0x78, 0x0,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0xf7, 0x80,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x13, 0x33, 0x22, 0x66, 0x44, 0xcc,

    /* U+0030 "0" */
    0x38, 0xfb, 0x3e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0xdd, 0xf1, 0xc0,

    /* U+0031 "1" */
    0x18, 0xdf, 0xfd, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x3e, 0x7f, 0x63, 0x63, 0x3, 0x7, 0xe, 0x1c,
    0x38, 0x70, 0x7f, 0xff,

    /* U+0033 "3" */
    0x79, 0xfb, 0x38, 0x71, 0xc7, 0x83, 0x83, 0xc7,
    0x9f, 0xf3, 0xc0,

    /* U+0034 "4" */
    0x6, 0x7, 0x3, 0x83, 0xc3, 0x61, 0xb1, 0x98,
    0xcc, 0xff, 0xff, 0xc1, 0x80, 0xc0,

    /* U+0035 "5" */
    0x7e, 0xfd, 0x87, 0xf, 0xdf, 0xf1, 0x83, 0x7,
    0x8f, 0xfb, 0xe0,

    /* U+0036 "6" */
    0x3c, 0xff, 0x9e, 0xd, 0xdf, 0xf9, 0xe3, 0xc7,
    0xcd, 0xf9, 0xe0,

    /* U+0037 "7" */
    0xff, 0xfc, 0x30, 0x61, 0x83, 0xc, 0x18, 0x30,
    0xe1, 0x83, 0x0,

    /* U+0038 "8" */
    0x7d, 0xfb, 0x1e, 0x3f, 0xcf, 0xb1, 0xe3, 0xc7,
    0x8f, 0xf3, 0xc0,

    /* U+0039 "9" */
    0x79, 0xfb, 0x3e, 0x3c, 0x79, 0xff, 0xbb, 0x7,
    0x9f, 0xf3, 0xc0,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x3, 0x6d, 0x0,

    /* U+003C "<" */
    0x1, 0x7, 0x1f, 0x7c, 0xe0, 0xe0, 0x7c, 0x1f,
    0x7, 0x1,

    /* U+003D "=" */
    0xff, 0xff, 0x0, 0x0, 0xff, 0xff,

    /* U+003E ">" */
    0x0, 0xc0, 0xf0, 0x3e, 0xf, 0xf, 0x3e, 0xf0,
    0xc0, 0x0,

    /* U+003F "?" */
    0x3c, 0x7e, 0xe7, 0xc3, 0x3, 0x6, 0xc, 0x18,
    0x18, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0x7, 0xe0, 0x1f, 0xf8, 0x3c, 0x1c, 0x33, 0xb6,
    0x67, 0xf6, 0x4e, 0x62, 0x4c, 0x62, 0xdc, 0x66,
    0xd8, 0x66, 0x4c, 0xec, 0x6f, 0xf8, 0x67, 0x70,
    0x38, 0xe, 0x1f, 0xfc, 0x7, 0xf0,

    /* U+0041 "A" */
    0xe, 0x0, 0xe0, 0xf, 0x1, 0xb0, 0x1b, 0x83,
    0x98, 0x31, 0x83, 0xfc, 0x7f, 0xc6, 0xe, 0x60,
    0xee, 0x6,

    /* U+0042 "B" */
    0xff, 0x3f, 0xec, 0x1b, 0x6, 0xc1, 0xbf, 0xcf,
    0xfb, 0x7, 0xc1, 0xf0, 0x7f, 0xfb, 0xfc,

    /* U+0043 "C" */
    0x1e, 0x1f, 0xe6, 0x3b, 0x86, 0xc0, 0x30, 0xc,
    0x3, 0x4, 0xe1, 0xd8, 0xe7, 0xf8, 0x78,

    /* U+0044 "D" */
    0xfe, 0x3f, 0xcc, 0x3b, 0x6, 0xc1, 0xf0, 0x7c,
    0x1f, 0x7, 0xc1, 0xb0, 0xef, 0xf3, 0xf8,

    /* U+0045 "E" */
    0xff, 0xff, 0xf0, 0x18, 0xc, 0x7, 0xfb, 0xfd,
    0x80, 0xc0, 0x60, 0x3f, 0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0,
    0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0047 "G" */
    0x1f, 0x1f, 0xe7, 0x1f, 0x80, 0xc0, 0x31, 0xfc,
    0x7f, 0x3, 0xe0, 0xdc, 0x77, 0xfc, 0x7c,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0xe7, 0xe6, 0x7e, 0x3c,

    /* U+004B "K" */
    0xe1, 0xdc, 0x73, 0x9c, 0x77, 0xf, 0xc1, 0xfc,
    0x3f, 0x87, 0x38, 0xe3, 0x1c, 0x73, 0x87, 0x70,
    0xe0,

    /* U+004C "L" */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xff, 0xff,

    /* U+004D "M" */
    0xf0, 0xfe, 0x3f, 0xc7, 0xe8, 0xfd, 0x9f, 0xb6,
    0xf6, 0xde, 0xdb, 0xcf, 0x79, 0xcf, 0x39, 0xe7,
    0x30,

    /* U+004E "N" */
    0xe1, 0xf0, 0xfc, 0x7e, 0x3d, 0x9e, 0xef, 0x37,
    0x9f, 0xc7, 0xe3, 0xf0, 0xf8, 0x30,

    /* U+004F "O" */
    0x1f, 0xf, 0xf1, 0xc7, 0x70, 0x6c, 0xf, 0x81,
    0xf0, 0x3e, 0x7, 0xe0, 0xce, 0x39, 0xfe, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfe, 0x7f, 0xb0, 0xf8, 0x3c, 0x3f, 0xfb, 0xf9,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0x0,

    /* U+0051 "Q" */
    0x1f, 0xf, 0xf1, 0xc7, 0x70, 0x6c, 0xf, 0x81,
    0xf0, 0x3e, 0x7, 0xe6, 0xde, 0x79, 0xff, 0xf,
    0xf0, 0x6,

    /* U+0052 "R" */
    0xff, 0x3f, 0xec, 0x1b, 0x7, 0xc1, 0xbf, 0xef,
    0xe3, 0x1c, 0xc7, 0x30, 0xec, 0x1f, 0x7,

    /* U+0053 "S" */
    0x3e, 0x3f, 0xb8, 0xd8, 0x7f, 0x3, 0xf0, 0x7c,
    0x7, 0xc1, 0xf1, 0xdf, 0xc7, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xe1, 0xf1, 0xdf, 0xe7, 0xc0,

    /* U+0056 "V" */
    0xe0, 0xdc, 0x19, 0x87, 0x38, 0xc3, 0x18, 0x67,
    0xe, 0xc0, 0xd8, 0x1b, 0x3, 0xc0, 0x38, 0x7,
    0x0,

    /* U+0057 "W" */
    0xe3, 0x87, 0xc7, 0x1d, 0x8f, 0x3b, 0x36, 0x66,
    0x6c, 0xce, 0xd9, 0x8d, 0xbf, 0x1e, 0x3c, 0x3c,
    0x78, 0x78, 0xf0, 0xf1, 0xe0, 0xc1, 0x80,

    /* U+0058 "X" */
    0x61, 0xce, 0x30, 0xee, 0xd, 0x81, 0xf0, 0x1c,
    0x7, 0x80, 0xf8, 0x3b, 0x6, 0x71, 0xc7, 0x70,
    0x60,

    /* U+0059 "Y" */
    0xe0, 0xce, 0x39, 0xc6, 0x1d, 0xc1, 0xb0, 0x3c,
    0x3, 0x80, 0x60, 0xc, 0x1, 0x80, 0x30, 0x6,
    0x0,

    /* U+005A "Z" */
    0x7f, 0xbf, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0x70,
    0x70, 0x70, 0x70, 0x3f, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,

    /* U+005C "\\" */
    0xcc, 0x44, 0x66, 0x22, 0x33, 0x31,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f, 0xf0,

    /* U+005E "^" */
    0x18, 0x70, 0xe3, 0x66, 0xcc, 0xf1, 0x80,

    /* U+005F "_" */
    0xff, 0xff, 0xc0,

    /* U+0060 "`" */
    0x63,

    /* U+0061 "a" */
    0x7d, 0xff, 0x18, 0x77, 0xf8, 0xf3, 0xff, 0x76,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0xfe, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xfe, 0xc6, 0xc0, 0xc0, 0xc4, 0xe6, 0xfe,
    0x3c,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x7b, 0xff, 0xe7, 0xc7, 0xc3,
    0xc7, 0xe7, 0xff, 0x7b,

    /* U+0065 "e" */
    0x79, 0xfb, 0x1f, 0xff, 0xf8, 0x31, 0xff, 0x7c,

    /* U+0066 "f" */
    0x3d, 0xf7, 0x3e, 0xf9, 0xc7, 0x1c, 0x71, 0xc7,
    0x1c,

    /* U+0067 "g" */
    0x7b, 0xff, 0xe7, 0xc7, 0xc3, 0xc7, 0xe7, 0xff,
    0x7b, 0xc7, 0xfe, 0x7c,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xde, 0xfe, 0xe7, 0xc7, 0xc7,
    0xc7, 0xc7, 0xc7, 0xc7,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x37, 0xe0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xce, 0xcc, 0xd8, 0xf8, 0xf8,
    0xec, 0xcc, 0xc6, 0xc6,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006D "m" */
    0xdc, 0xef, 0xff, 0xe7, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xde, 0xfe, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7,
    0xc7,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0xfe,
    0xdc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x7b, 0xff, 0xe7, 0xc3, 0xc3, 0xc7, 0xe7, 0xff,
    0x7b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0xf9, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x3c, 0x7e, 0x63, 0x70, 0x3e, 0x7, 0xe3, 0x7f,
    0x3e,

    /* U+0074 "t" */
    0x23, 0x19, 0xff, 0xb1, 0x8c, 0x63, 0x1e, 0x70,

    /* U+0075 "u" */
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0xfb,
    0x73,

    /* U+0076 "v" */
    0xe3, 0xb1, 0x98, 0xce, 0xc3, 0x61, 0xb0, 0x70,
    0x38, 0x1c, 0x0,

    /* U+0077 "w" */
    0xc6, 0x36, 0x73, 0x67, 0x36, 0xf6, 0x6d, 0x63,
    0xde, 0x39, 0xe3, 0x9c, 0x18, 0xc0,

    /* U+0078 "x" */
    0x63, 0x3b, 0x8f, 0x83, 0x81, 0xc1, 0xe0, 0xd8,
    0xee, 0xe3, 0x0,

    /* U+0079 "y" */
    0xe3, 0x31, 0x98, 0xce, 0xc3, 0x61, 0xb0, 0x70,
    0x38, 0x1c, 0xc, 0x1e, 0xe, 0x0,

    /* U+007A "z" */
    0x7e, 0x7e, 0xe, 0x1c, 0x38, 0x30, 0x70, 0xff,
    0xff,

    /* U+007B "{" */
    0x1c, 0xf3, 0xc, 0x30, 0xce, 0x38, 0x30, 0xc3,
    0xc, 0x30, 0xf1, 0xc0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xe3, 0xc3, 0xc, 0x30, 0xc1, 0xc7, 0x30, 0xc3,
    0xc, 0x33, 0xce, 0x0,

    /* U+007E "~" */
    0xf1, 0xff, 0x8e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 71, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 85, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 121, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 142, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 37, .adv_w = 228, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 71, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 87, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 92, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 100, .adv_w = 71, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 102, .adv_w = 85, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 103, .adv_w = 71, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 142, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 85, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 85, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 229, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 239, .adv_w = 150, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 245, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 255, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 250, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 185, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 199, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 71, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 185, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 213, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 199, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 199, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 539, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 242, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 692, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 706, .adv_w = 150, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 713, .adv_w = 142, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 716, .adv_w = 85, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 717, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 142, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 85, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 799, .adv_w = 71, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 71, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 810, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 71, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 228, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 869, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 881, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 142, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 913, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 199, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 949, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 963, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 972, .adv_w = 100, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 984, .adv_w = 72, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 988, .adv_w = 100, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1000, .adv_w = 150, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
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
    -9, -5, -14, -9, -19, -19, -14, -23,
    -9, -5, -9, -28, -28, -14, -5, -19,
    -19, -14, -23, -9, -5, -33, -33, -19,
    -5, -5, -9, -28, -14, -28, -28, -28,
    -19, -5, -19, -19, -19, -5, -19, -14,
    -19, -19, -19, -19, -23, -14, -23, -14,
    -14, -19, -14, -14, -5, -19, -14, -9,
    -9, -14, -5, -14, -5, -5, -14, -9,
    -5, -2, -5, -5, -5, -5, -5, -28,
    -14, -28, -19, -19, -23, -14, -14, -9,
    -19, -14, -19, -14, -14, -14, -14, -19,
    -19, -9, -9, -19, -19
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
const lv_font_t ui_font_arialceb16 = {
#else
lv_font_t ui_font_arialceb16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_ARIALCEB16*/

