#include "Component.h"


class ComponentFactory {
	public:
		Component* CreateComponent(json component);
		static ComponentFactory* Instance();
	private:
		static ComponentFactory m_componentFactory;
};