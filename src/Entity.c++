#include "Entity.hpp"

Entity::Entity(const size_t &id, const std::string &tag)
    : id(id), tag(tag), is_alive(true) {}

const std::string &Entity::returnTag() const
{
    return tag;
}

const size_t &Entity::returnId() const
{
    return id;
}

void Entity::destroy()
{
    is_alive = false;
}
