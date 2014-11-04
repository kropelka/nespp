#define VERSION_NO 0.1

#include "SDL.h"

#include <iostream>
#include <cstdlib>

#define ERRLOG(x) std::cout << x

class EmulationWindow {
private:
	int screenWidth, screenHeight;
	SDL_Window* window;
	SDL_Surface* screenSurface;
public:
	EmulationWindow(int w = 256, int h = 240);
	~EmulationWindow();
	void startEventLoop();

};

EmulationWindow::EmulationWindow(int w, int h) {
	window = NULL;
	screenSurface = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERRLOG("Blad inicjalizacji SDL.");
		std::exit(1);
	};
	window = SDL_CreateWindow("NES++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		w, h, SDL_WINDOW_SHOWN);
	if(window==NULL) {
		ERRLOG("Blad tworzenia okna.");
		std::exit(1);
	};
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

}

EmulationWindow::~EmulationWindow() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void EmulationWindow::startEventLoop() {
	
}

int main(int argc, char* argv[]) {
	std::cout << "NES++ 0.1" << std::endl;
	std::string s;
	std::cin >>s;
	EmulationWindow wind(640, 480);
	return 0;
}