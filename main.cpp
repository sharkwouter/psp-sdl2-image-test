// compile with: clang++ main.cpp -o image_exmple -lSDL2 -lSDL2_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

static bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return false;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "could not initialize sdl2_image: %s\n", IMG_GetError());
    return false;
  }
  window = SDL_CreateWindow(
			    "hello_sdl2",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return false;
  }
  screenSurface = SDL_GetWindowSurface(window);
  if (screenSurface == NULL) {
    fprintf(stderr, "could not get window: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

static SDL_Surface* loadImage(std::string path) {
  SDL_Surface* img = IMG_Load(path.c_str());
  if (img == NULL) {
    fprintf(stderr, "could not load image: %s\n", IMG_GetError());
    return NULL;
  }
  SDL_Surface* optimizedImg = SDL_ConvertSurface(img, screenSurface->format, 0);
  if (optimizedImg == NULL) fprintf(stderr, "could not optimize image: %s\n", SDL_GetError());
  SDL_FreeSurface(img);
  return optimizedImg;
}

static void close() {
  SDL_FreeSurface(screenSurface); screenSurface = NULL;
  SDL_DestroyWindow(window); window = NULL;
  SDL_Quit();
}

int main(int argc, char* args[]) {
  if (!init()) return 1;
  SDL_Surface* img = loadImage("hello.png");
  if (img == NULL) return 1;
  SDL_BlitSurface(img, NULL, screenSurface, NULL);
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);
  SDL_FreeSurface(img); img = NULL;
  close();
  return 0;
}
