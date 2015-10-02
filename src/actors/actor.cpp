#include "../../inc/actors/actor.hpp"

Actor::Actor()
    : sftile::Entity()
    , Sprite()
{

}

Actor::Actor(const Actor& _copy)
    : sftile::Entity(_copy)
    , Sprite(_copy)
{

}

Actor::Actor(Actor&& _moveable)
    : sftile::Entity(std::move(_moveable))
    , Sprite(_moveable)
{

}

Actor& Actor::operator=(const Actor& _copy)
{
    if (this != &_copy)
    {
        sftile::Entity::operator=(_copy);
        Sprite::operator=(_copy);

        Actor temp(_copy);
    }
    return *this;
}