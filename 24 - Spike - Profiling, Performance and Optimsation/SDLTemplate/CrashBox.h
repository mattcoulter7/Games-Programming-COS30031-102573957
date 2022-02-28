#include "SDL.h"

enum BoxState { CONTACT_NO, CONTACT_YES };

struct CrashBox {
	int x, y; // pos
	int dx, dy; // vel
	int w, h; // size
	BoxState state;
	SDL_Rect rect;
};