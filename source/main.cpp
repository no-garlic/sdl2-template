#include <SDL.h>

#include <cmath>
#include <iostream>
#include <memory>

#if defined(__APPLE__) && defined(SDL_METAL_ENABLED)
#include <SDL_metal.h>
#endif

// Custom SDL resource deleters for smart pointers
struct SDLWindowDeleter {
  void operator()(SDL_Window* window) const {
    if (window) SDL_DestroyWindow(window);
  }
};

struct SDLRendererDeleter {
  void operator()(SDL_Renderer* renderer) const {
    if (renderer) SDL_DestroyRenderer(renderer);
  }
};

int main(int argc, char* argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Make sure SDL cleans up before exit
  std::atexit(SDL_Quit);

  // Window size
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;

  // Create window
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window(SDL_CreateWindow(
      "SDL2 Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH, WINDOW_HEIGHT,
      SDL_WINDOW_SHOWN
#if defined(__APPLE__) && defined(SDL_METAL_ENABLED)
          | SDL_WINDOW_METAL
#endif
      ));

  if (!window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create renderer
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;

#if defined(__APPLE__) && defined(SDL_METAL_ENABLED)
  // Use Metal renderer on Apple Silicon Macs
  SDL_MetalView metalView = SDL_Metal_CreateView(window.get());
  if (!metalView) {
    std::cerr << "Failed to create Metal view: " << SDL_GetError() << std::endl;
    return 1;
  }

  renderer.reset(SDL_CreateRenderer(
      window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  // Note: Don't destroy Metal view until after the main loop - moved below
#else
  // Use standard renderer for other platforms
  renderer.reset(SDL_CreateRenderer(
      window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
#endif

  if (!renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Print renderer info
  SDL_RendererInfo rendererInfo;
  if (SDL_GetRendererInfo(renderer.get(), &rendererInfo) == 0) {
    std::cout << "Using renderer: " << rendererInfo.name << std::endl;
  }

  // Main loop flag
  bool quit = false;

  // Event handler
  SDL_Event e;

  // Animation variables
  int animationTick = 0;

  // Main loop
  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      // User presses a key
      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
      }
    }

    // Clear screen with dark gray background
    SDL_SetRenderDrawColor(renderer.get(), 64, 64, 64, 255);
    SDL_RenderClear(renderer.get());

    // Draw a filled rectangle in the center (hot pink)
    SDL_Rect centerRect = {WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50, 100,
                           100};
    SDL_SetRenderDrawColor(renderer.get(), 255, 105, 180, 255);
    SDL_RenderFillRect(renderer.get(), &centerRect);

    // Draw a green rectangle that moves around
    int xOffset = static_cast<int>(50.0 * sin(animationTick * 0.05));
    int yOffset = static_cast<int>(50.0 * cos(animationTick * 0.05));
    SDL_Rect movingRect = {WINDOW_WIDTH / 2 - 25 + xOffset,
                           WINDOW_HEIGHT / 2 - 25 + yOffset, 50, 50};
    SDL_SetRenderDrawColor(renderer.get(), 0, 255, 0, 255);
    SDL_RenderFillRect(renderer.get(), &movingRect);

    // Draw a yellow circle (approximation using lines)
    const int centerX = WINDOW_WIDTH / 4;
    const int centerY = WINDOW_HEIGHT / 2;
    const int radius = 50;
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 0, 255);
    for (int w = 0; w < radius * 2; w++) {
      for (int h = 0; h < radius * 2; h++) {
        int dx = radius - w;
        int dy = radius - h;
        if ((dx * dx + dy * dy) <= (radius * radius)) {
          SDL_RenderDrawPoint(renderer.get(), centerX + dx, centerY + dy);
        }
      }
    }

    // Draw a blue hollow rectangle
    SDL_Rect blueRect = {WINDOW_WIDTH * 3 / 4 - 50, WINDOW_HEIGHT / 2 - 50, 100,
                         100};
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer.get(), &blueRect);

    // Draw horizontal and vertical lines crossing at the center of the window
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer.get(), 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH,
                       WINDOW_HEIGHT / 2);
    SDL_RenderDrawLine(renderer.get(), WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2,
                       WINDOW_HEIGHT);

    // Draw a red triangle (using lines)
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    const int triangleSize = 80;
    int triangleCenterX = WINDOW_WIDTH * 3 / 4;
    int triangleCenterY = WINDOW_HEIGHT / 4;
    SDL_Point trianglePoints[3] = {
        {triangleCenterX, triangleCenterY - triangleSize / 2},
        {triangleCenterX - triangleSize / 2,
         triangleCenterY + triangleSize / 2},
        {triangleCenterX + triangleSize / 2,
         triangleCenterY + triangleSize / 2}};

    SDL_RenderDrawLine(renderer.get(), trianglePoints[0].x, trianglePoints[0].y,
                       trianglePoints[1].x, trianglePoints[1].y);
    SDL_RenderDrawLine(renderer.get(), trianglePoints[1].x, trianglePoints[1].y,
                       trianglePoints[2].x, trianglePoints[2].y);
    SDL_RenderDrawLine(renderer.get(), trianglePoints[2].x, trianglePoints[2].y,
                       trianglePoints[0].x, trianglePoints[0].y);

    // Update screen
    SDL_RenderPresent(renderer.get());

    // Small delay to reduce CPU usage
    SDL_Delay(16);  // Approximately 60 FPS

    // Update animation tick
    animationTick++;
  }

#if defined(__APPLE__) && defined(SDL_METAL_ENABLED)
  // Clean up Metal view after the main loop
  SDL_Metal_DestroyView(metalView);
#endif

  return 0;
}