#include "EntityMananger.hpp"

EntityManager::EntityManager() {}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto e = std::shared_ptr <Entity> (new Entity(total_entities++, tag));
    wait_room.push_back(e);
    return e;
}

void EntityManager::update()
{
    for (auto &e : wait_room) {
        entities.push_back(e);
        entity_map[e->tag].push_back(e);
    }

    //remove dead entities from E_Vec
    removeDeadEntities(entities);
    //remove dead entities from ALL E_Vec in E_Map
    for (auto &[tag, E_Vec] : entity_map) {
        removeDeadEntities(E_Vec);
    }
    wait_room.clear();
}

E_Vec &EntityManager::getEntities()
{
    return entities;
}

E_Vec &EntityManager::getEntities(const std::string &tag)
{
    return entity_map[tag];
}

void EntityManager::removeDeadEntities(E_Vec &vec)
{
    // Create a lambda function to check if an entity is dead
    auto isDeadEntity = [](const std::shared_ptr<Entity> &entity) {
        return entity->isDead();
    };

    // Use std::remove_if to move dead entities to the end of the vector
    auto deadEntityIterator = std::remove_if(vec.begin(), vec.end(), isDeadEntity);

    // Use vector's erase member function to remove dead entities from the vector
    vec.erase(deadEntityIterator, vec.end());
}