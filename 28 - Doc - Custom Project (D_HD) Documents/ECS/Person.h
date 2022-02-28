#pragma once

#include "PersonTrainStationType.h"
#include "BaseComponent.h"

/*
    Declares an entity as a train station
*/

struct Person : public BaseComponent {
    enum class State {
        WaitingAtStation,
        OnTrain
    };
    Person() : BaseComponent() {}
    Person(const Person& obj) : BaseComponent(obj) {
        trainStationId = obj.trainStationId;
        trainId = obj.trainId;
        state = obj.state;
        type = obj.type;
    };
    Person(json obj) : BaseComponent(obj) {
        trainStationId = obj["trainStationId"].is_null() ? trainStationId : obj["trainStationId"];
        trainId = obj["trainId"].is_null() ? trainId : obj["trainId"];
        state = obj["state"].is_null() ? state : obj["state"];
        type = obj["type"].is_null() ? type : obj["type"];
    } // json constructor
    ~Person() {}
    BaseComponent* Clone() {
        return new Person(*this);
    };
    size_t trainStationId = - 1;
    size_t trainId = -1;
    State state = State::WaitingAtStation;
    PersonTrainStationType type = PersonTrainStationType::Circle;
};