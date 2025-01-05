#include <SDL.h>
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
const int SPEED = 15;  // Movement speed

int handle_input() {
    /* Rect screen coordinates */
    int rect_x=0, rect_y=0;
    int rect_xvel=0, rect_yvel=0;

    bool running = true;

    SDL_Event event;
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_QUIT:
                running = false;
                break;
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        rect_xvel = -SPEED;
                        break;
                    case SDLK_RIGHT:
                        rect_xvel =  SPEED;
                        break;
                    case SDLK_UP:
                        rect_yvel = -SPEED;
                        break;
                    case SDLK_DOWN:
                        rect_yvel =  SPEED;
                        break;
                    default:
                        break;
                }
                break;
            /* We must also use the SDL_KEYUP events to zero the x */
            /* and y velocity variables. But we must also be       */
            /* careful not to zero the velocities when we shouldn't*/
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        /* We check to make sure the rect is moving */
                        /* to the left. If it is then we zero the    */
                        /* velocity. If the rect is moving to the   */
                        /* right then the right key is still press   */
                        /* so we don't tocuh the velocity            */
                        if( rect_xvel < 0 )
                            rect_xvel = 0;
                        break;
                    case SDLK_RIGHT:
                        if( rect_xvel > 0 )
                            rect_xvel = 0;
                        break;
                    case SDLK_UP:
                        if( rect_yvel < 0 )
                            rect_yvel = 0;
                        break;
                    case SDLK_DOWN:
                        if( rect_yvel > 0 )
                            rect_yvel = 0;
                        break;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        }
    }
    
    
    /* Update the rect position */
    rect.x += rect_xvel;
    rect.y += rect_yvel;
    return running;
}

void draw() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow("Movable Rectangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
}

void deinitialize() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}