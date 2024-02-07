#pragma once

#include <vector>
#include <memory>
#include <map>
#include "Entity.hpp"

using E_Vec = std::vector <std::shared_ptr <Entity>>;
using E_Map = std::map <std::string, E_Vec>;

class EntityManager {
    E_Vec entities;
    E_Vec wait_room;
    E_Map entity_map;
    size_t total_entities = 0;

public:
    EntityManager();
    
    std::shared_ptr <Entity> addEntity(const std::string &tag);
    
    void update();

    E_Vec &getEntities();
    E_Vec &getEntities(const std::string &tag);
    void removeDeadEntities(E_Vec &vec);
};
