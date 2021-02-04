#include "hal.h"

int SDL_PollEvent(SDL_Event *event) {
	return 0;
}

int SDL_LockSurface(SDL_Surface *surface) {
	return 0;
}

void SDL_UnlockSurface(SDL_Surface *surface) {
}

int SDL_ShowCursor(int toggle) {
	return 0;
}

int SDL_SaveBMP(SDL_Surface *surface, const char *file) {
	return 0;
}

int SDL_Init(uint32_t flags) {
	return 0;
}

char *SDL_GetError(void) {
	static char msg[] = "SDL_GetError is not implemented";
	return msg;
}

void SDL_WM_SetCaption(const char *title, const char *icon) {
	return;
}

void SDL_Quit(void) {
	return;
}
