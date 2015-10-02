#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>

#include "../tile_engine/sf_entity.hpp"
#include "sprite.hpp"

class Actor: public sftile::Entity, Sprite
{
public:
    Actor();

    Actor(const Actor& _copy);

    Actor(Actor&& _moveable);

    Actor& operator=(const Actor& _copy);

private:
};

#endif