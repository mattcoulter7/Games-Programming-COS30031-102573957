#pragma once

#include "ComponentFactory.h"

#include <typeindex>

class ComponentTypeFactory {
public:
    ComponentTypeFactory();
    ~ComponentTypeFactory();

    template<typename T>
    void RegisterFactory(std::string type) {
        ComponentFactory<T>* cFactory = new ComponentFactory<T>();
        _factoriesByName[type] = cFactory; // save under type alias
        _factoriesByType[typeid(T)] = cFactory; // save under component type index
    };
    template<typename T>
    T* Create() {
        return static_cast<T*>(_factoriesByType[typeid(T)]->Create());
    };

    BaseComponent* Create(std::string type);
    BaseComponent* CreateFromJson(json obj);
    std::vector<BaseComponent*> CreateFromJsonArray(json obj);
    std::vector<BaseComponent*> CreateFromPrefab(size_t prefabid);
    static ComponentTypeFactory* Instance();
private:
    static ComponentTypeFactory _instance;
    std::map<std::type_index, ComponentFactoryBase*> _factoriesByType;
    std::map<std::string, ComponentFactoryBase*> _factoriesByName;
};