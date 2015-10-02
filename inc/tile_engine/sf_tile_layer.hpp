#ifndef SF_TILE_LAYER_HPP
#define SF_TILE_LAYER_HPP

#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "sf_layer.hpp"

namespace sftile
{
class Tileset;
class Loader;

class TileLayer: public Layer
{
friend class Loader;
public:
    TileLayer();

    TileLayer(const TileLayer& _copy);

    TileLayer& operator=(const TileLayer& _copy);

    TileLayer(TileLayer&& _copy);

    int GetTileGID(const int _x, const int _y);

    string GetName();

    string GetType();

    sf::Vector2i GetDimensions();

    void Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_layer);

private:
    // Vector of the tile GIDs in the layer
    vector< vector<int> > tile_gids;

    // Tileset pointer
    shared_ptr<Tileset> tileset;
};

}

#endif