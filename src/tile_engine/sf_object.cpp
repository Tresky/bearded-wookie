#include "../../inc/tile_engine/sf_object.hpp"

namespace sftile
{

Object::Object()
    : name("")
    , type("")
    , position(0, 0)
    , dimensions(0, 0)
    , rotation(0.f)
    , gid(-1)
    , visible(false)
{

}

Object::Object(const Object& _copy)
    : name(_copy.name)
    , type(_copy.type)
    , position(_copy.position)
    , dimensions(_copy.dimensions)
    , rotation(_copy.rotation)
    , gid(_copy.gid)
    , visible(_copy.visible)
{

}

Object::Object(Object&& _moveable)
    : name(std::move(_moveable.name))
    , type(std::move(_moveable.type))
    , position(std::move(_moveable.position))
    , dimensions(std::move(_moveable.dimensions))
    , rotation(std::move(_moveable.rotation))
    , gid(std::move(_moveable.gid))
    , visible(std::move(_moveable.visible))
{

}

Object& Object::operator=(const Object& _copy)
{
    if (this != &_copy)
    {
        Object temp(_copy);

        std::swap(name, temp.name);
        std::swap(type, temp.type);
        std::swap(position, temp.position);
        std::swap(dimensions, temp.dimensions);
        std::swap(rotation, temp.rotation);
        std::swap(gid, temp.gid);
        std::swap(visible, temp.visible);
    }
    return *this;
}

string Object::GetName()
{
    return name;
}

void Object::SetName(const string _name)
{
    name = _name;
}

string Object::GetType()
{
    return type;
}

void Object::SetType(const string _type)
{
    type = _type;
}

sf::Vector2i Object::GetPosition()
{
    return position;
}

void Object::SetPosition(const sf::Vector2i _position)
{
    position = _position;
}

sf::Vector2i Object::GetDimensions()
{
    return dimensions;
}

void Object::SetDimensions(const sf::Vector2i _dimensions)
{
    dimensions = _dimensions;
}

float Object::GetRotation()
{
    return rotation;
}

void Object::SetRotation(const float _rotation)
{
    rotation = _rotation;
}

int Object::GetGid()
{
    return gid;
}

void Object::SetGid(const int _gid)
{
    gid = _gid;
}

bool Object::IsVisible()
{
    return visible;
}

void Object::SetVisible(const bool _visible)
{
    visible = _visible;
}

sf::IntRect Object::GetBoundingBox()
{
    return { position.x, position.y, dimensions.x, dimensions.y };
}

}