#include "../../inc/actors/sprite.hpp"

Sprite::Sprite()
    : texture()
{

}

Sprite::Sprite(const Sprite& _copy)
    : texture(_copy.texture)
{

}

Sprite::Sprite(Sprite&& _moveable)
{

}

Sprite& Sprite::operator=(const Sprite& _copy)
{
    if (this != &_copy)
    {
        Sprite temp(_copy);

    }
    return *this;
}
