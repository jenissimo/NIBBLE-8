#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "nibble8.h"
#include "adapters/sdl_adapter.h"
#include "hardware/os.h"
#include "hardware/ram.h"
#include "hardware/video.h"
#include "hardware/utils.h"
#include "api/lua.h"
#include <SDL2/SDL.h>

int run = 1;

int main(int argc, char *argv[])
{
    uint32_t now_time;
    uint32_t frame_time;
    uint32_t last_time;
    uint32_t targetFrameTimeMs = 1000 / NIBBLE_FPS;

    srand(time(NULL)); // Initialization, should only be called once.

    initRAM();
    initVideo();
    initLua();
    nibble_sdl_init();
    init_clock();

    next_time = SDL_GetTicks() + NIBBLE_FPS;

    // parse params
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--fullscreen") == 0)
        {
            goFullScreen();
        }
        // if cart is specified, load it
        if (strcmp(argv[i], "--cart") == 0)
        {
            if (i + 1 < argc)
            {
                lua_getglobal(currentVM, "loadAndPlayCart");
                lua_pushstring(currentVM, argv[i + 1]);
                lua_pcall(currentVM, 1, 0, 0);
            }
        }
    }

    while (run)
    {
        now_time = SDL_GetTicks();
        frame_time = now_time - last_time;
        last_time = now_time;

        if (nibble_sdl_update() == 0)
        {
            run = 0;
        }
        else
        {
            // sleep for remainder of time
            if (frame_time < targetFrameTimeMs)
            {
                uint32_t msToSleep = targetFrameTimeMs - frame_time;

                SDL_Delay(msToSleep);

                last_time += msToSleep;
            }
            next_time += NIBBLE_FPS;
        }
        tick_clock();
    }

    destroyLua();
    destroyVideo();
    destroyRAM();
    return nibble_sdl_quit();
}
