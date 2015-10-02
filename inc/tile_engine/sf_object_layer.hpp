#ifndef SF_OBJECT_LAYER_HPP
#define SF_OBJECT_LAYER_HPP

#include <vector>
    using std::vector;

#include "sf_layer.hpp"
#include "sf_object.hpp"

namespace sftile
{
class Loader;

class ObjectLayer: public Layer
{
friend class Loader;
public:
    // Default constructor
    ObjectLayer();

    // Copy constructor
    ObjectLayer(const ObjectLayer& _copy);

    // Copy assignment operator
    ObjectLayer& operator=(const ObjectLayer& _copy);

    // Move constuctor
    ObjectLayer(ObjectLayer&& _moveable);

    string GetName();

    string GetType();

    sf::Vector2i GetDimensions();

    void Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_dimensions);

private:
    // Color to use to display these objects
    sf::Color color;

    // Vector of objects in the layer
    vector<Object> objects;
};

}

#endif