#include "../../inc/tile_engine/sf_object_layer.hpp"

namespace sftile
{

ObjectLayer::ObjectLayer()
    : Layer()
    , color(sf::Color::Red)
    , objects()
{

}

ObjectLayer::ObjectLayer(const ObjectLayer& _copy)
    : Layer(_copy)
    , color(_copy.color)
    , objects(_copy.objects)
{

}

ObjectLayer::ObjectLayer(ObjectLayer&& _moveable)
    : Layer(std::move(_moveable))
    , color(std::move(_moveable.color))
    , objects(std::move(_moveable.objects))
{

}

ObjectLayer& ObjectLayer::operator=(const ObjectLayer& _copy)
{
    if (this != &_copy)
    {
        Layer::operator=(_copy);

        ObjectLayer temp(_copy);

        std::swap(color, temp.color);
        std::swap(objects, temp.objects);
    }
    return *this;
}

string ObjectLayer::GetName()
{
    return name;
}

string ObjectLayer::GetType()
{
    return "object";
}

sf::Vector2i ObjectLayer::GetDimensions()
{
    return layer_dimensions;
}

void ObjectLayer::Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_dimensions)
{
    for (auto &object: objects)
    {
        sf::RectangleShape rect(sf::Vector2f(object.GetDimensions()));
        rect.setFillColor(sf::Color::White);
        sf::Vector2i pos = object.GetPosition();

        sf::Vector2i bounds_top_left(_bounds.left * _tile_dimensions.x, _bounds.top * _tile_dimensions.y);
        sf::Vector2i bounds_bott_right(_bounds.left * _tile_dimensions.x + _bounds.width * _tile_dimensions.x, _bounds.top * _tile_dimensions.y + _bounds.height * _tile_dimensions.y);

        if (pos.x > bounds_top_left.x && pos.x < bounds_bott_right.x)
            if (pos.y > bounds_top_left.y && pos.y < bounds_bott_right.y)
            {
                sf::Vector2f new_pos(pos.x - _bounds.left * _tile_dimensions.x - _offset.x, pos.y - _bounds.top * _tile_dimensions.y - _offset.y);
                rect.setPosition(new_pos);
                _window.draw(rect);
            }
    }
}

}