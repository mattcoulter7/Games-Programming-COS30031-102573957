#include "SDL.h"
#include "ECS.h"

class Debug {
public:
	void RenderRect(SDL_Renderer* renderer, float x, float y, float w, float h) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_FRect r;
		r.x = x;
		r.y = y;
		r.w = w;
		r.h = h;
		SDL_RenderDrawRectF(renderer, &r);
	}
	void RenderSolidRect(SDL_Renderer* renderer, float x, float y, float w, float h) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_FRect r;
		r.x = x;
		r.y = y;
		r.w = w;
		r.h = h;
		SDL_RenderFillRectF(renderer, &r);
	}
	void RenderCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			RenderPoint(renderer, centreX + x, centreY - y);
			RenderPoint(renderer, centreX + x, centreY + y);
			RenderPoint(renderer, centreX - x, centreY - y);
			RenderPoint(renderer, centreX - x, centreY + y);
			RenderPoint(renderer, centreX + y, centreY - x);
			RenderPoint(renderer, centreX + y, centreY + x);
			RenderPoint(renderer, centreX - y, centreY - x);
			RenderPoint(renderer, centreX - y, centreY + x);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}
	void RenderPoint(SDL_Renderer* renderer, float x, float y) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPointF(renderer, x, y);
	}
	void RenderLine(SDL_Renderer* renderer,float x1, float y1, float x2, float y2) { // useful debug tools
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLineF(renderer,x1,y1,x2,y2);
	}
	static Debug* Instance() {
		if (m_instance == nullptr) {
			m_instance = new Debug();
		}
		return m_instance;
	}
private:
	static Debug* m_instance;
};