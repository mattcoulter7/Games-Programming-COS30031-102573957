#pragma once

#include "PersonTrainStationType.h"
#include "BaseComponent.h"

/*
    Declares an entity as a train station
*/

struct TrainStation : public BaseComponent {
    TrainStation() : BaseComponent() {}
    TrainStation(const TrainStation& obj) : BaseComponent(obj) {
        type = obj.type;
    };
    TrainStation(json obj) : BaseComponent(obj) {
        type = obj["type"].is_null() ? type : obj["type"];
    } // json constructor
    ~TrainStation() {}
    BaseComponent* Clone() {
        return new TrainStation(*this);
    };
    PersonTrainStationType type = PersonTrainStationType::Circle;
};