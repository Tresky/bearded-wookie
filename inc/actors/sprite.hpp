#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

class Sprite
{
public:
    Sprite();

    Sprite(const Sprite& _copy);

    Sprite(Sprite&& _moveable);

    Sprite& operator=(const Sprite& _copy);

    void Render(sf::RenderWindow& _window);

private:
    sf::Texture texture;
};

#endif