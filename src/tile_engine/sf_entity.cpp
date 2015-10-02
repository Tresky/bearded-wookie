#include "../../inc/tile_engine/sf_entity.hpp"

namespace sftile
{

Entity::Entity()
    : position(0.f, 0.f)
{

}

Entity::Entity(const Entity& _copy)
    : position(_copy.position)
{

}

Entity::Entity(Entity&& _moveable)
    : position(std::move(_moveable.position))
{

}

Entity& Entity::operator=(const Entity& _copy)
{
    if (this != &_copy)
    {
        Entity temp(_copy);

        std::swap(position, temp.position);
    }
    return *this;
}

Entity::~Entity()
{
    
}

sf::Vector2f Entity::GetPosition()
{
    return position;
}

}