#include <SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

// Surface rendering is slow and done through software.
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentImageSurface = NULL;

int main(int argc, char* argv[])
{
	if (init() != true) {
		printf("Failed to initialize.\n");
		SDL_Delay(2000);
		return -1;
	}
	if (loadMedia() != true) {
		printf("Failed to load media.\n");
		SDL_Delay(2000);
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
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(currentImageSurface, NULL, screenSurface, &stretchRect);
		SDL_UpdateWindowSurface(window);
	}
	close();
	return 0;
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created: %s\n", SDL_GetError());
			success = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	currentImageSurface = loadSurface("up.bmp");
	if (currentImageSurface == NULL) {
		printf("Failed to load up image. \n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(currentImageSurface);
	SDL_DestroyWindow(window);	//Also destroys the screen surface.
	window = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* newSurface = SDL_LoadBMP(path.c_str());
	if (newSurface == NULL) {
		printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		optimizedSurface = SDL_ConvertSurface(newSurface, screenSurface->format, NULL);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image. SDL error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(newSurface);
	}
	return optimizedSurface;
}

