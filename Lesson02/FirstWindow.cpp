#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

// Surface rendering is slow and done through software.
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *imageSurface = NULL;

int main(int argc, char* argv[])
{
	if (init() != true) {
		printf("Failed to initialize.\n");
	}
	else {
		if (loadMedia() != true) {
			printf("Failed to load media.\n");
		}
		else {
			SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
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
	imageSurface = SDL_LoadBMP("guest.bmp");
	if (imageSurface == NULL) {
		printf("Unable to load image %s. Error: %s\n", "guest.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;

	SDL_DestroyWindow(window);	//Also destroys the screen surface.
	window = NULL;

	SDL_Quit();
}
