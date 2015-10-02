#ifndef SF_Entity_H
#define SF_Entity_H

#include <string>
    using std::string;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

namespace sftile
{

class Entity
{
public:
    Entity();

    Entity(const Entity& _copy);

    Entity& operator=(const Entity& _copy);

    Entity(Entity&& _moveable);

    ~Entity();

    sf::Vector2f GetPosition();

private:
    // Position of the object in relation to the map it is on
    sf::Vector2f position;
};

}

#endif