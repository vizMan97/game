#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#define SDL_MAIN_USE_CALLBACKS 1
struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Screen_Test","Version: 0.0.1","3425");

    auto* state = new AppState();

    return SDL_APP_CONTINUE;

}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}