#include "System.h"

class PersonSpawnerSystem : public System {
public:
	PersonSpawnerSystem();
	PersonSpawnerSystem(json obj);
	~PersonSpawnerSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
private:
	void AddEventListeners() override;
};