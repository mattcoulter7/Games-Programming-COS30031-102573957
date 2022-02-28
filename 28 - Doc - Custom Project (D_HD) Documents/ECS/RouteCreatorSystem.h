#pragma once

#include "System.h"

#include "Route.h"

class Collider2D;
class RouteCreatorSystem : public System {
public:
	enum class Intent {
		Remove,
		Add
	};
	RouteCreatorSystem();
	RouteCreatorSystem(json obj);
	~RouteCreatorSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
private:
	void AddEventListeners() override;
	void HandleStartNewRoute(Uint8 input, Collider2D* col);
	void HandleModifyCurrentRoute(Uint8 input, bool state,Collider2D* col);
	void HandleDestroyRoute(Uint8 input, Collider2D* col);
	void HandleStopModification(Uint8 input);
	
	void SaveRoute();
	void CancelRoute();
	
	void MouseEnter(Collider2D* col);
	void MouseExit(Collider2D* col);
	void MouseMove(Vector2 pos, Vector2 vel);

	std::vector<Vector2> GetShapedRoute(std::vector<Vector2>);

	size_t trainPrefabId = -1;
	size_t routePrefabId = -1;

	Intent intent = Intent::Add;
	Route* currentRoute; // reference to the current route being built
};