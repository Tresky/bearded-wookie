#ifndef SF_LAYER_H
#define SF_LAYER_H

#include <string>
    using std::string;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

namespace sftile
{

class Layer
{
friend class Loader;
public:
    // Default constructor
    Layer();

    // Copy constructor
    Layer(const Layer& _copy);

    // Copy assignment operator
    Layer& operator=(const Layer& _copy);

    // Move constuctor
    Layer(Layer&& _moveable);

    virtual string GetName();

    virtual string GetType();

    virtual float GetOpacity();

    virtual bool IsVisible();

    virtual sf::Vector2i GetDimensions();

    virtual void Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_dimensions);

protected:
    // Name of layer
    string name;

    // Opacity to display the layer with
    float opacity;

    // If true, layer will be rendered
    bool visible;

    // Tile dimensions in pixels
    sf::Vector2i layer_dimensions;
};

}

#endif