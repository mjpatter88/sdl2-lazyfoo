#include <SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press surface constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

// Surface rendering is slow and done through software.
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentImageSurface = NULL;
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

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
	
	currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type = SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;
				case SDLK_RIGHT:
					currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					currentImageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}
		SDL_BlitSurface(currentImageSurface, NULL, screenSurface, NULL);
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
	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image. \n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load up image. \n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load down image. \n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load left image. \n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load right image. \n");
		success = false;
	}
	return success;
}

void close()
{
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_FreeSurface(keyPressSurfaces[i]);
		keyPressSurfaces[i] = NULL;
	}

	SDL_DestroyWindow(window);	//Also destroys the screen surface.
	window = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* newSurface = SDL_LoadBMP(path.c_str());
	if (newSurface == NULL) {
		printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return newSurface;
}

