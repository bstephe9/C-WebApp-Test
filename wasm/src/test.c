#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "sdl_file.h"

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

int running = 1;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

void mainloop(void);

int main(int argc, char* argv[])
{
    initialize();
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 0, 1);
    #else
    while (1) { mainloop(); }
    #endif
}

void mainloop(void)   /* this will run often, possibly at the monitor's refresh rate */
{
    if (!running) {
        deinitialize();
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();  /* this should "kill" the app. */
        #else
        exit(0);
        #endif
    }

    Uint32 frame_start = SDL_GetTicks();

    running = handle_input();
    draw();

    // Limit frame rate
    uint32_t frame_time = SDL_GetTicks() - frame_start;  // Time it took to render this frame
    if (frame_time < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frame_time);  // Delay the remaining time of the frame
    }
}
