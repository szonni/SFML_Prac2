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
    wait_room.clear();

    //remove dead entities from E_Vec
    removeDeadEntities(entities);
    //remove dead entities from ALL E_Vec in E_Map
    for (auto &[tag, E_Vec] : entity_map) {
        removeDeadEntities(E_Vec);
    }
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
    for (auto &e : vec) {
        if (e->isDead()) {
            vec.erase(std::remove(vec.begin(), vec.end(), e), vec.end());
        }
    }
}
