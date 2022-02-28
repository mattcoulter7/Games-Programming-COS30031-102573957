#pragma once

#include "BaseComponent.h"

// renders the entity
struct Route : public BaseComponent {
    Route() : BaseComponent() {}
    Route(const Route& obj) : BaseComponent(obj) {
        inUse = obj.inUse;
        nodes = obj.nodes;
        shapedRoute = obj.shapedRoute;
    };
    Route(json obj) : BaseComponent(obj) {
        inUse = obj["inUse"].is_null() ? inUse : obj["inUse"];

        if (!obj["nodes"].is_null()) {
            for (json v : obj["nodes"]) {
                float x = v["x"].is_null() ? 0 : v["x"];
                float y = v["y"].is_null() ? 0 : v["y"];
                nodes.push_back(Vector2{ x,y });
            }
        }

        if (!obj["shapedRoute"].is_null()) {
            for (json v : obj["shapedRoute"]) {
                float x = v["x"].is_null() ? 0 : v["x"];
                float y = v["y"].is_null() ? 0 : v["y"];
                shapedRoute.push_back(Vector2{ x,y });
            }
        }
    } // json constructor
    ~Route() {}
    BaseComponent* Clone() {
        return new Route(*this);
    };
    bool inUse = false;
    std::vector<Vector2> nodes; // the nodes of each trainsation
    std::vector<Vector2> shapedRoute; // the points in between each train station
};