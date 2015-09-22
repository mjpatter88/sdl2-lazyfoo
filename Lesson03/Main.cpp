#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	SDL_Window *window;
	SDL_Surface *surface;

	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Events!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Unable to create the window: %s\n", SDL_GetError());
		return -1;
	}
	
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL) {
		printf("Unable to get the window's surface: %s\n", SDL_GetError());
		return -1;
	}

	if (SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0)) != 0) {
		printf("Unable to fill the rectangle: %s\n", SDL_GetError());
		return -1;
	}
	if (SDL_UpdateWindowSurface(window) != 0) {
		printf("Unable to redraw the window: %s\n", SDL_GetError());
		return -1;
	}

	// Main Loop
	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}