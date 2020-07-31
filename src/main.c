#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "structs.h"
#include "init.h"
#include "render.h"
#include "buttons.h"

void initialize(State *state, SDL_Renderer *renderer)
{
    init_font(state);
    init_GUI(state, renderer);
    return;
}

int listen_for_events(State *state, SDL_Window *window, float dt)
{
    SDL_Event event;
    int done = 0;

    // Event loop
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            // Window events
            case(SDL_WINDOWEVENT_CLOSE):
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
            break;

            // Keyboard events
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = 1;
                    }
                    break;
                    
                    case SDLK_UP:
                    {
                        return done;
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        return done;
                    }
                }
            }
            break;

            // Mouse events
            case SDL_MOUSEBUTTONDOWN:
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        done = 0;                                  
                    }
                }
            }
            break;

            // Quit event
            case SDL_QUIT:
            {
                done = 1;
            }
            break;
        }
    }

    return done;
}

void render(SDL_Renderer *renderer, State *state)
{
    // Background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // GUI
    render_GUI(state, renderer);

    // Present it all
    SDL_RenderPresent(renderer);
}

void process(State *state, float dt)
{
    return;
}

int main(int argc, char* argv[])
{
    void initialize(State *state, SDL_Renderer *renderer);
    int listen_for_events(State *state, SDL_Window *window, float dt);
    void render(SDL_Renderer *renderer, State *state);
    void process(State *state, float dt);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Declare a state state that will be used a lot
    State state;

    
    
    // Init SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    window = SDL_CreateWindow("Title",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              960,
                              640,
                              0);
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    state.renderer = renderer;

    // Init this program
    initialize(&state, renderer);

    // Init SDL_ttf (for text fonts)
    TTF_Init();

    
    /*********
    EVENT LOOP
    *********/
    int done = 0;

    // Time stuff
    Uint32 t1 = SDL_GetTicks();
    float frame_duration = 16.666; // 60th of a second
    while(!done)
    {
        // Delta time
        Uint32 t2 = SDL_GetTicks();
        float dt = (t2 - t1) / 1000.0f;

        if (listen_for_events(&state, window, dt) == 1)
        {
            done = 1;
        }
        render(renderer, &state);
        process(&state, dt);

        // Delta time
        t1 = t2;
        SDL_Delay(floor(frame_duration - dt));
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
