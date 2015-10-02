#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "mobile_sprite.hpp"

class Character: public MobileSprite
{
public:
    Character(const sf::Texture _texture);

    Character(const Character& _copy);

    Character(Character&& _moveable);

    Character& operator=(const Character& _copy);

    sf::Vector2f GetPosition();
    void SetPosition(const sf::Vector2f _position);

    void Move(const int _x, const int _y);

    void Update(sf::Time _elapsed_time);
    void Render(sf::RenderWindow& _window);

private:

};

#endif