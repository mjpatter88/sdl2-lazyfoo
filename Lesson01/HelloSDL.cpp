#include <SDL.h>
#include <iostream>

#define HEIGHT 500
#define WIDTH 500
#define POS_X 200
#define POS_Y 200

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create the window
	window = SDL_CreateWindow("Hello SDL", POS_X, POS_Y, WIDTH, HEIGHT, 0);
	if (window == NULL) {
		std::cout << "Failed to create the window: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Set the renderer's size
	if (SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT) != 0) {
		std::cout << "Failed to set the renderer's logical size: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Set the color to Green
	if (SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255) != 0) {
		std::cout << "Unable to set the renderer's draw color: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Clear the window (makes it all green)
	if (SDL_RenderClear(renderer) != 0) {
		std::cout << "Unable to clear the window: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Actually render the changes
	SDL_RenderPresent(renderer);

	// Delay so we can see the window
	SDL_Delay(5000);

	SDL_Quit();
	return 0;
}
