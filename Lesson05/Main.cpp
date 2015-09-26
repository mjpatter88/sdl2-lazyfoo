#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

// Surface rendering is slow and done through software.
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

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
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
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
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Renderer could not be created: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (IMG_Init(imgFlags) & imgFlags != imgFlags) {
					printf("SDL_image could not be initialized: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	texture = loadTexture("press.bmp");
	if (texture == NULL) {
		printf("Failed to load press image. \n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s. Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

