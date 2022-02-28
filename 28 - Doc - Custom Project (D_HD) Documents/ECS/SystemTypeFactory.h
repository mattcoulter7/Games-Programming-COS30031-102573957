#pragma once

#include "SystemFactory.h"

#include <typeindex>

class SystemTypeFactory {
public:
    SystemTypeFactory();
    ~SystemTypeFactory();

    template<typename T>
    void RegisterFactory(std::string type) {
        SystemFactory<T>* cFactory = new SystemFactory<T>();
        _factoriesByName[type] = cFactory; // save under type alias
        _factoriesByType[typeid(T)] = cFactory; // save under component type index
    };
    template<typename T>
    T* Create() {
        return static_cast<T*>(_factoriesByType[typeid(T)]->Create());
    };

    System* Create(std::string type);
    System* CreateFromJson(json obj);
    static SystemTypeFactory* Instance();
private:
    static SystemTypeFactory _instance;
    std::map<std::type_index, SystemFactoryBase*> _factoriesByType;
    std::map<std::string, SystemFactoryBase*> _factoriesByName;
};