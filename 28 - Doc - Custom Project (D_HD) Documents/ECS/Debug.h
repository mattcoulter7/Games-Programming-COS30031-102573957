#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Vector2.h"

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
	void RenderPolygon(SDL_Renderer* renderer, std::vector<Vector2> pts) {
		// original connecting points is to last point
		Vector2 connectingPt;
		Vector2 pt;
		// loop through each point and draw to previous point
		for (size_t i = 0; i < pts.size(); i++) {
			pt = pts[i];
			if (i == pts.size() - 1) {
				connectingPt = pts[0];
			}
			else {
				connectingPt = pts[i + 1];
			}
			RenderLine(renderer, pt.x, pt.y, connectingPt.x, connectingPt.y);
		}

	}
	void RenderOpenPolygon(SDL_Renderer* renderer, std::vector<Vector2> pts) {
		// original connecting points is to last point
		Vector2 connectingPt;
		Vector2 pt;
		// loop through each point and draw to previous point
		for (size_t i = 0; i < pts.size() - 1; i++) {
			pt = pts[i];
			connectingPt = pts[i+1];
			RenderLine(renderer, pt.x, pt.y, connectingPt.x, connectingPt.y);
		}

	}
	void RenderText(SDL_Renderer* renderer, float x,float y,std::string text) {
		//this opens a font style and sets a size
		TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color color = { 255, 0, 0,255 };

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), color);

		// now you can convert it into a texture
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = x;  //controls the rect's x coordinate 
		Message_rect.y = y; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 100; // controls the height of the rect

		// (0,0) is on the top left of the window/screen,
		// think a rect as the text's box,
		// that way it would be very simple to understand

		// Now since it's a texture, you have to put RenderCopy
		// in your game loop area, the area where the whole code executes

		// you put the renderer's name first, the Message,
		// the crop size (you can ignore this if you don't want
		// to dabble with cropping), and the rect which is the size
		// and coordinate of your texture
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
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