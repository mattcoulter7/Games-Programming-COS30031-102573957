#include "Component.h"

#include "json.hpp"
using json = nlohmann::json;

class ComponentFactory {
	public:
		Component* CreateComponent(json component);
		static ComponentFactory* Instance();
	private:
		static ComponentFactory m_componentFactory;
};