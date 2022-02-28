#include <typeinfo>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <map>
#include <vector>
#include <typeindex>

#include <cstdio>
#include <functional>
#include <type_traits>
#include <any>

struct Vector2 {
    float x = 0;
    float y = 0;
};

struct BaseComponent {
    BaseComponent() {}
    int val = 0;
};

class ComponentFactoryBase { // base class so template classes can be stored
public:
    virtual BaseComponent* Create() = 0;
};
template<typename T>
class ComponentFactory : public ComponentFactoryBase {
public:
    BaseComponent* Create() override {
        return new T();
    }
};

struct Component1 : public BaseComponent {
    Component1() : BaseComponent() {}
    void mousedown(Vector2 pos,Vector2 vel) {

    };
    int val1 = 0;
};
struct Component2 : public BaseComponent {
    Component2() : BaseComponent() {}
    void mousedown(Vector2 pos) {

    };
    static void test(Vector2 pos,Vector2 vel) {

    };
    int val2 = 0;
};
ComponentFactory<Component1> c1Factory;
std::map<std::type_index, BaseComponent*> components;
template<typename T>
T* GetComponent() {
    return dynamic_cast<T*>(components[typeid(T)]);
}
template<typename T>
T* AddComponent() {
    T* comp = static_cast<T*>(c1Factory.Create());
    components[typeid(T)] = comp;
    return comp;
}
template<typename T>
void RemoveComponent(T* comp) {
    T* found = static_cast<T*>(components[typeid(*comp)]);
    bool test = found == comp;
}

class EventDispatcher {
public:
    // Add a new event listener to call a global function
    template<typename J, typename ...Args>
    static void AddEventListener(std::string identifier, J(*func)(Args...)) {
        /*
            USAGE: EventDispatcher::AddEventListener("onclick", &CALLBACK_FUNCTION);
        */
        handlers<J, Args...>[identifier].push_back([func](Args... args)->J {
            return (func)(args...);
        });
    }
    // Add a new event listener to call a function in a given object
    template<class T, typename J, typename ...Args>
    static void AddEventListener(std::string identifier, J(T::*func)(Args...), T* obj) {
        /*
            USAGE: EventDispatcher::AddEventListener("onclick", OBJECT_POINTER, &OBJECT_TYPE::CALLBACK_FUNCTION);
        */
        handlers<J,Args...>[identifier].push_back([obj,func](Args... args)->J {
            return ((obj)->*(func))(args...);
        });
    }
    // call all the event listener functions by a given key, and specifying return type (J)
    template<typename J, typename ...Args>
    static std::vector<J> Dispatch(std::string identifier, Args ...args) {
        /*
            USAGE: std::vector<RETURN_TYPE> data = EventDispatcher::Dispatch<RETURN_TYPE>("identifier", val1, val2, ...);
        */
        std::vector<J> result;
        for (auto& func : handlers<J, Args...>[identifier]) {
            result.push_back(func(args...));
        }
        return result;
    }
    // call all the event listener functions by a given key
    template<typename ...Args>
    static void Dispatch(std::string identifier, Args ...args) {
        /*
            USAGE: EventDispatcher::Dispatch("identifier", val1, val2, ...);
        */
        for (auto& func : handlers<void, Args...>[identifier]) {
            func(args...);
        }
    }
    // holds all of the handlers by key
    template<typename J, typename ...Args>
    static std::map<std::string, std::vector<std::function<J(Args...)>>> handlers;
};
template<typename J, typename ...Args>
std::map<std::string, std::vector<std::function<J(Args...)>>> EventDispatcher::handlers;


int mousedown(Vector2 pos, Vector2 vel) {
    return 1;
};
int main() {
    if (false) {
        Component1* comp1 = new Component1();
        Component2* comp2 = new Component2();
        EventDispatcher::AddEventListener("onclick", &Component1::mousedown, comp1);
        EventDispatcher::AddEventListener("onclick", &mousedown);
        EventDispatcher::AddEventListener("onclick", &Component2::test);
        EventDispatcher::Dispatch("onclick", Vector2{ 0,0 }, Vector2{ 1,1 });
        std::vector<int> data = EventDispatcher::Dispatch<int>("onclick", Vector2{ 0,0 }, Vector2{ 1,1 });
    }

    RemoveComponent(AddComponent<Component1>());


    return 0;
}