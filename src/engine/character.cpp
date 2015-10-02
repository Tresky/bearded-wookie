#include "../../inc/engine/character.hpp"

Character::Character(const sf::Texture _texture)
    : MobileSprite(_texture)
{

}

Character::Character(const Character& _copy)
    : MobileSprite(_copy)
{

}

Character::Character(Character&& _moveable)
    : MobileSprite(std::move(_moveable))
{

}

Character& Character::operator=(const Character& _copy)
{
    if (this != &_copy)
    {
        MobileSprite::operator=(_copy);

        Character temp(_copy);
    }
    return *this;
}

sf::Vector2f Character::GetPosition()
{
    return MobileSprite::GetPosition();
}

void Character::SetPosition(sf::Vector2f _position)
{
    MobileSprite::SetPosition(_position);
}

void Character::Move(const int _x, const int _y)
{

}

void Update(sf::Time _elapsed_time)
{

}

void Render(sf::RenderWindow& _window)
{
    
}
