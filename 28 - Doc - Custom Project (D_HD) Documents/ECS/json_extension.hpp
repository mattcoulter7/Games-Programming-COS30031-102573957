#pragma once

#include "json.hpp"
using json = nlohmann::json;

class json_extension {
public:
    // append values of another json object on top of the original json object
    static void combine(json& obj1, json obj2) {
        for (const auto& pair : obj2.items())
        {
            if (pair.value().is_object()) {
                combine(obj1[pair.key()], obj2[pair.key()]);
            }
            else {
                obj1[pair.key()] = obj2[pair.key()];
            }
        }
    }
};