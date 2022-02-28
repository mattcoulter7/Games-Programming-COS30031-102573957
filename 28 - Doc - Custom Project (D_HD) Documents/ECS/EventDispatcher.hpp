#pragma once

#include <functional>
#include <string>
#include <vector>
#include <map>

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
    static void AddEventListener(std::string identifier, J(T::* func)(Args...), T* obj) {
        /*
            USAGE: EventDispatcher::AddEventListener("onclick", OBJECT_POINTER, &OBJECT_TYPE::CALLBACK_FUNCTION);
        */
        handlers<J, Args...>[identifier].push_back([obj, func](Args... args)->J {
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