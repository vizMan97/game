#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>



//g++ -std=c++23 src/main.cpp -Ithird_party/SDL3/include -Lthird_party/SDL_image/lib -Lthird_party/SDL3/lib -lSDL3 -lSDL3_image -o src/main.exe
//g++ -std=c++23 src/main.cpp -Ithird_party/SDL3/include -Lthird_party/SDL3/lib -lSDL3 -o src/main.exe

struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Screen_Test","Version: 0.0.1","3425");

    auto* state = new AppState();
    *appstate = state;

    if(!SDL_CreateWindowAndRenderer("Hello SDL",1920,1080,SDL_WINDOW_RESIZABLE, &state->window, &state->renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());

        return SDL_APP_FAILURE;
    }
    

    return SDL_APP_CONTINUE;

}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto* state = static_cast<AppState*>(appstate);
    SDL_SetRenderDrawColor(state->renderer,128,128,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state->renderer);
    SDL_RenderPresent(state->renderer);


    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{

    if(event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (appstate) {
    auto* state = static_cast<AppState*>(appstate);

    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);

    delete state; // <-- DEALLOCATING
}
}