#include "Component.h"

enum class OpenState {
	Opened,
	Closed
};

class ComponentOpenable : public Component {
public:
	ComponentOpenable(json component) : Component(ComponentType::Openable) {

	};
	OpenState state = OpenState::Closed;
};