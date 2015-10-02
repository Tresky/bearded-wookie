#ifndef SF_TILESET_H
#define SF_TILESET_H

#include <string>
    using std::string;
#include <vector>
    using std::vector;

#include <SFML/Graphics.hpp>

#include "sf_tile.hpp"

namespace sftile
{
class Loader;

class Tileset
{
friend class Loader;
public:
    // Default constructor
    Tileset();

    // Copy constructor
    Tileset(const Tileset& _copy);

    // Copy assignment operator
    Tileset& operator=(const Tileset& _copy);

    // Move constuctor
    Tileset(Tileset&& _moveable);

    // Destructor
    ~Tileset();

    Tile GetTile(const unsigned int _id);

    sf::Vector2i GetTileDimensions();

    const int GetNumTiles();

    void RenderTile(sf::RenderWindow& _window, const unsigned int _id, const float _x, const float _y);

private:
    // Dimensions of the tiles in pixels
    sf::Vector2i tile_dimensions;


    // Vector of tiles
    vector<Tile> tiles;


    // Texture of the entire tileset in full
    sf::Texture tileset_image;


    // Properties of the tileset
    //unique_ptr<SfProperties> properties;
};

}

#endif