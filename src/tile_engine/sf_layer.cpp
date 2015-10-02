#include <iostream>
    using std::cout;
    using std::endl;

#include "../../inc/tile_engine/sf_layer.hpp"

namespace sftile
{

Layer::Layer()
    : name("")
    , opacity(1.f)
    , visible(true)
    , layer_dimensions(0, 0)
{}

Layer::Layer(const Layer& _copy)
    : name(_copy.name)
    , opacity(_copy.opacity)
    , visible(_copy.visible)
    , layer_dimensions(_copy.layer_dimensions)
{}

Layer& Layer::operator=(const Layer& _copy)
{
    if (this != &_copy)
    {
        Layer temp(_copy);

        std::swap(name, temp.name);
        std::swap(opacity, temp.opacity);
        std::swap(visible, temp.visible);
        std::swap(layer_dimensions, temp.layer_dimensions);
    }

    return *this;
}

Layer::Layer(Layer&& _moveable)
    : name(std::move(_moveable.name))
    , opacity(std::move(_moveable.opacity))
    , visible(std::move(_moveable.visible))
    , layer_dimensions(std::move(_moveable.layer_dimensions))
{}

string Layer::GetName()
{
    return name;
}

string Layer::GetType()
{
    return "";
}

float Layer::GetOpacity()
{
    return opacity;
}

bool Layer::IsVisible()
{
    return visible;
}

sf::Vector2i Layer::GetDimensions()
{
    return layer_dimensions;
}

void Layer::Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_dimensions)
{
    
}

}