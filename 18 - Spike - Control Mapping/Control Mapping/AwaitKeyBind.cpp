#include "AwaitKeyBind.h"

#include "AwaitSelectControl.h"
#include "StateManager.h"
#include "ControlMapper.h"

AwaitKeyBind::AwaitKeyBind(Actions bindKey) {
	_bindKey = bindKey;
}
void AwaitKeyBind::Update(StateManager& configurer, SDL_Event& event) {
	Uint8 key = ControlMapper::GetInputCode(event);
	if (key != SDLK_ESCAPE) {
		ControlMapper::Instance().SetControl(_bindKey, key);
	}
	configurer.SetState(new AwaitSelectControl());
};
void AwaitKeyBind::Render() {
	std::cout << "Please select a key to bind..." << std::endl;
};