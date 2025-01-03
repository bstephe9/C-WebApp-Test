#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdl_file.h"

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect rect = { .x = 100, .y = 100, .w = 50, .h = 50 };
const int SPEED = 10;  // Movement speed
bool running = true;

void handle_input() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_UP]) {
        rect.y -= SPEED;
        if (rect.y < 0) rect.y = 0;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        rect.y += SPEED;
        if (rect.y > SCREEN_HEIGHT - rect.h) rect.y = SCREEN_HEIGHT - rect.h;
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        rect.x -= SPEED;
        if (rect.x < 0) rect.x = 0;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        rect.x += SPEED;
        if (rect.x > SCREEN_WIDTH - rect.w) rect.x = SCREEN_WIDTH - rect.w;
    }
}

void main_loop(void* arg) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            emscripten_cancel_main_loop();
            break;
        }
    }

    // Handle continuous movement
    handle_input();

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    if (!running) {
        // Cleanup resources
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
}

int sdl_func() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    win = SDL_CreateWindow("Movable Rectangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    emscripten_set_main_loop_arg(main_loop, NULL, 0, 1);

    return EXIT_SUCCESS;
}
