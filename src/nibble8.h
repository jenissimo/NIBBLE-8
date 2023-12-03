#ifndef NIBBLE8_H
#define NIBBLE8_H

#include <stdint.h>

// PocketBuddy?

// Debug flags
#define NIBBLE_DISPLAY_FPS        0

#define NIBBLE_TITLE              "Nibble-8"

#define NIBBLE_WIDTH              160
#define NIBBLE_HEIGHT             120
#define NIBBLE_FONT_WIDTH         4
#define NIBBLE_FONT_HEIGHT        5
#define NIBBLE_BPP                2 // 2 bits per pixel
#define NIBBLE_FULLWIDTH_BITS     8
#define NIBBLE_PALETTE_SIZE       4
#define NIBBLE_DEFAULT_COLOR      3
#define NIBBLE_DEFAULT_BG_COLOR   0
#define NIBBLE_FULLWIDTH          (1 << NIBBLE_FULLWIDTH_BITS)
#define NIBBLE_FULLHEIGHT         (NIBBLE_FULLWIDTH*9/16)
#define NIBBLE_FPS                30

#define NIBBLE_WINDOW_SCALE       4

#define NIBBLE_TILE_SIZE          8 // tiles 8x8 pixels
#define NIBBLE_PIXELS_IN_BYTE     (uint8_t)(1 << NIBBLE_BPP)

// Memory layout
#define NIBBLE_SPRITE_SHEET_WIDTH 160
#define NIBBLE_SPRITE_SHEET_HEIGHT 160
#define NIBBLE_SPRITE_SHEET_SIZE NIBBLE_SPRITE_SHEET_WIDTH * NIBBLE_SPRITE_SHEET_HEIGHT / NIBBLE_PIXELS_IN_BYTE
#define NIBBLE_SPRITE_FLAG_SIZE  NIBBLE_SPRITE_SHEET_SIZE * NIBBLE_PIXELS_IN_BYTE / (NIBBLE_TILE_SIZE * NIBBLE_TILE_SIZE)

#define NIBBLE_MAP_WIDTH          128
#define NIBBLE_MAP_HEIGHT         64
#define NIBBLE_MAP_SIZE          NIBBLE_TILE_SIZE * NIBBLE_MAP_WIDTH * NIBBLE_MAP_HEIGHT

// 64 music frames (0-63), each frame uses 4 bytes represents 4 channels
#define NIBBLE_MUSIC_SIZE           256 

/* There are 64 sound effects. Each sound effect is 68 bytes, with two bytes for each of 32 notes, followed by
   4 special bytes: one encoding the editor mode and filter switch positions, one for the speed, and two for the
   loop parameters (start, end). (64 * 68 = 4,352 bytes.)
*/
#define NIBBLE_SFX_COUNT            64
#define NIBBLE_SFX_MAX_NOTES        32
#define NIBBLE_SFX_SIZE             4352 // 64 music frames (0-63), each frame uses 4 bytes represents 4 channels

#define NIBBLE_DRAW_STATE_SIZE      64
#define NIBBLE_HARDWARE_STATE_SIZE  64
#define NIBBLE_SCREEN_DATA_SIZE     NIBBLE_WIDTH * NIBBLE_HEIGHT / NIBBLE_PIXELS_IN_BYTE

#define NIBBLE_MEMORY_SIZE          NIBBLE_SPRITE_SHEET_SIZE + NIBBLE_SPRITE_FLAG_SIZE + NIBBLE_MAP_SIZE + NIBBLE_MUSIC_SIZE + NIBBLE_SFX_SIZE + NIBBLE_DRAW_STATE_SIZE + NIBBLE_HARDWARE_STATE_SIZE + NIBBLE_SCREEN_DATA_SIZE

#define NIBBLE_MARGIN_TOP           ((NIBBLE_FULLHEIGHT - NIBBLE_HEIGHT) / 2)
#define NIBBLE_MARGIN_BOTTOM        NIBBLE_MARGIN_TOP
#define NIBBLE_MARGIN_LEFT          ((NIBBLE_FULLWIDTH - NIBBLE_WIDTH) / 2)
#define NIBBLE_MARGIN_RIGHT         NIBBLE_MARGIN_LEFT

#define NIBBLE_KEY_PRESS_DELAY   60 // 15 frames delay before key repeat
#define NIBBLE_KEY_BUFFER        4
#define NIBBLE_SAMPLERATE        44100
#define NIBBLE_SAMPLETYPE        s16
#define NIBBLE_SAMPLESIZE        sizeof(NIBBLE_SAMPLETYPE)
#define NIBBLE_SAMPLE_CHANNELS   2
#define NIBBLE_FRAMERATE         30

#define FONT_SIZE_COMPRESSED 128 * 128 / 8

//static const uint8_t palette[] = {0x0d, 0x04, 0x05, 0x5e, 0x12, 0x10, 0xd3, 0x56, 0x00, 0xfe, 0xd0, 0x18};
//static const uint8_t palette[] = {0x08, 0x18, 0x20, 0x34, 0x68, 0x56, 0x88, 0xc0, 0x70, 0xe0, 0xf8, 0xd0};
//static const uint8_t palette[] = {0x40, 0x50, 0x10, 0x70, 0x80, 0x28, 0xa0, 0xa8, 0x40, 0xd0, 0xd0, 0x58};
//static const uint8_t palette[] = {0x21, 0x1e, 0x20, 0x55, 0x55, 0x68, 0xa0, 0xa0, 0x8b, 0xe9, 0xef, 0xec};

#endif