#pragma once

#include <memory>
#include <iostream>
#include "Components.hpp"

class Entity {
    friend class EntityManager;

    const size_t id = 0;
    const std::string tag = "Null_Tag";
    bool is_alive = true;
    
    Entity(const size_t &id, const std::string &tag);

public:
    std::shared_ptr <c_Transform> transform;
    std::shared_ptr <c_Shape> shape;
    std::shared_ptr <c_Score> score;
    std::shared_ptr <c_Name> name;
    std::shared_ptr <c_LifeSpan> life_span;
    std::shared_ptr <c_Collision> collision;
    std::shared_ptr <c_Input> input;

    
    const std::string &returnTag() const;
    const size_t &returnId() const;
    void destroy();
};