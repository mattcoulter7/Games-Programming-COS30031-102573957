#pragma once

#include "BaseComponent.h"

// renders the entity
struct Train : public BaseComponent {
    enum class State {
        Moving,
        AtStation
    };
    Train() : BaseComponent() {}
    Train(const Train& obj) : BaseComponent(obj) {
        routeid = obj.routeid;
        targetIndex = obj.targetIndex;
        direction = obj.direction;
        maxSpeed = obj.maxSpeed;
        personTransferSpeed = obj.personTransferSpeed;
        nextTransfer = obj.nextTransfer;
        maxCapacity = obj.maxCapacity;
        currCapacity = obj.currCapacity;
    };
    Train(json obj) : BaseComponent(obj) {
        routeid = obj["routeid"].is_null() ? routeid : obj["routeid"];
        targetIndex = obj["targetIndex"].is_null() ? targetIndex : obj["targetIndex"];
        direction = obj["direction"].is_null() ? direction : obj["direction"];
        maxSpeed = obj["maxSpeed"].is_null() ? maxSpeed : obj["maxSpeed"];
        personTransferSpeed = obj["personTransferSpeed"].is_null() ? personTransferSpeed : obj["personTransferSpeed"];
        nextTransfer = obj["nextTransfer"].is_null() ? nextTransfer : obj["nextTransfer"];
        maxCapacity = obj["maxCapacity"].is_null() ? maxCapacity : obj["maxCapacity"];
        currCapacity = obj["currCapacity"].is_null() ? currCapacity : obj["currCapacity"];
    } // json constructor
    ~Train() {}
    BaseComponent* Clone() {
        return new Train(*this);
    };
    size_t routeid = -1; // component id of route it is following
    int targetIndex = 1; // index of the point within the route. starts at one because train is spawned at 0
    int direction = 1; // index of the point within the route
    float maxSpeed = 0.1; // max speed in which it moves across the route
    float personTransferSpeed = 500; // pickup and drop people 1 every 500 ms
    float nextTransfer = 0; // time in which a new pickup is allowed to happen
    int maxCapacity = 6; // maximum amount of people to be carried at once
    int currCapacity = 0; // current capacity of people
    State state = State::Moving;
};