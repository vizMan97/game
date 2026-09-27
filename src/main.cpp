#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

// This struct holds your engine state (window and renderer pointers)
struct AppState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

// 1. Initialization (Runs once at startup)
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << "\n";
        return SDL_APP_FAILURE;
    }

    auto* state = new AppState();
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("Visual Novel Engine", 1280, 720, 0, &state->window, &state->renderer)) {
        std::cerr << "Failed to create window/renderer: " << SDL_GetError() << "\n";
        return SDL_APP_FAILURE;
    }

    std::cout << "SDL3 Window opened successfully!\n";
    return SDL_APP_CONTINUE;
}

// 2. Event Handling (Runs when clicking, pressing keys, or closing the app)
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // Cleanly exit the app
    }
    return SDL_APP_CONTINUE;
}

// 3. Rendering Loop (Runs every single frame)
SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* state = static_cast<AppState*>(appstate);

    // Clear the screen with a nice pink visual novel background
    SDL_SetRenderDrawColor(state->renderer, 240, 128, 128, 255); 
    SDL_RenderClear(state->renderer);
    
    // Present the drawing to the screen
    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

// 4. Memory Cleanup (Runs when shutting down)
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (appstate) {
        auto* state = static_cast<AppState*>(appstate);
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        delete state;
    }
    SDL_Quit();
    std::cout << "Engine shut down cleanly.\n";
}