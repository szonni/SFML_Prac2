#include "Entity.hpp"

Entity::Entity(const size_t &in_id, const std::string &in_tag)
    : id(in_id), tag(in_tag), is_alive(true) {}

const std::string &Entity::returnTag() const
{
    return tag;
}

const size_t &Entity::returnId() const
{
    return id;
}

bool Entity::isDead() const
{
    return is_alive == false;
}

void Entity::destroy()
{
    is_alive = false;
}
