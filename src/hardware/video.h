#ifndef nibble_video_h
#define nibble_video_h

#include "../nibble8.h"
#include "palette_manager.h"
#include <stdint.h>
#include <stdbool.h>

uint32_t *frame;
uint8_t *font;
PaletteManager *manager;
static const uint8_t fullByteColors[4] = {0b00000000, 0b01010101, 0b10101010, 0b11111111};

// TODO: Make dirty flag

/*
struct pixel {
    int r;
    int g;
    int b;
} pixel;
struct pixel frame[NIBBLE_WIDTH*NIBBLE_HEIGHT];
*/

void initVideo(void);
void destroyVideo(void);
void loadFont(void);
void loadPalettes();
void print_char(int charIndex);
void nibble_api_cls(uint8_t col);
void nibble_api_pal(uint8_t c0, uint8_t c1, uint8_t p);
void nibble_api_pal_reset();
void nibble_api_palt(uint8_t col, bool t);
void nibble_api_palt_reset();
void nibble_api_circ(int16_t x, int16_t y, int16_t r, uint8_t col);
void nibble_api_circfill(int16_t x, int16_t y, int16_t r, uint8_t col);
void nibble_api_pset(int16_t x, int16_t y, uint8_t col);
uint8_t nibble_api_pget(int16_t x, int16_t y);
void nibble_api_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t col);
void nibble_api_rectfill(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t col);
void nibble_api_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t col);
void nibble_api_hline(int16_t x1, int16_t x2, int16_t y, uint8_t color);
int nibble_api_print(char *text, int16_t x, int16_t y, uint8_t fg_color, uint8_t bg_color);
void nibble_api_sspr(int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh, bool flip_x, bool flip_y);
void nibble_api_sset(int16_t x, int16_t y, uint8_t col);
uint8_t nibble_api_sget(int16_t x, int16_t y);
void draw_char(int charIndex, int16_t x, int16_t y, uint8_t fgCol, uint8_t bgCol);
void nibble_api_spr(int16_t sprIndex, int16_t x, int16_t y, uint8_t flipX, uint8_t flipY);
void nibble_api_mset(uint16_t x, uint16_t y, uint8_t sprite_number);
uint8_t nibble_api_mget(uint16_t x, uint16_t y);
void nibble_api_draw_fps(int fps);

uint16_t nibble_get_vram_byte_index(int16_t x, int16_t y, uint16_t width);
uint16_t nibble_get_vram_bitpair_index(int16_t x, int16_t y, uint16_t width);
void setPixelFromSprite(int16_t x, int16_t y, uint8_t col);
bool isColorTransparent(uint8_t color);
void updateFrame(void);
void printVRam(void);

#endif