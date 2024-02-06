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
    for (auto e : wait_room) {
        entities.push_back(e);
        entity_map[e->tag].push_back(e);
    }
    wait_room.clear();
}

E_Vec &EntityManager::getEntities()
{
    return entities;
}
