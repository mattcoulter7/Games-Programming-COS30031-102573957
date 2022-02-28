#pragma once

#include "System.h"

/*
	Handles various mouse events interacting with colliders
*/

class Collider2D;
class CursorSystem : public System {
public:
	CursorSystem();
	CursorSystem(json obj);
	~CursorSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	bool MouseIn(size_t colId);
	bool MouseEnter(size_t colId);
	bool MouseExit(size_t colId);
	size_t cursorEntityId = -1;
	size_t cursorCompId = -1;
private:
	void AddEventListeners() override;
	void DispatchMouseMoveEvent(Vector2 pos,Vector2 vel);
	void DispatchMouseEnterEvent(Collider2D* col1, Collider2D* col2);
	void DispatchMouseExitEvent(Collider2D* col1, Collider2D* col2);
	void DispatchMouseInEvent(Collider2D* col1, Collider2D* col2);
	void DispatchMouseOutEvent(Collider2D* col1, Collider2D* col2);
	void DispatchInputDownEvents(Uint8 input);
	void DispatchInputUpEvents(Uint8 input);
	void DispatchInputEvents(Uint8 input, bool down);
};