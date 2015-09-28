#include <SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();
bool loadMedia();
void close();

int main(int argc, char* argv[])
{
	if (!init()) {
		printf("Problem with initialization.\n");
		return -1;
	}
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		// CLear the screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Red rectangle
		SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);

		// Green quad outline
		SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &outlineRect);

		//Blue horizontal line
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

		//Yellow dotted horizontal line
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		for (int i = 0; i < SCREEN_HEIGHT; i+=4) {
			SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
		}

		SDL_RenderPresent(renderer);
	}

	return 0;
}

bool init() {
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
		}
	}
	return success;
}

bool loadMedia() {
	return true;
}

void close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}