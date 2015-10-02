#ifndef SF_TILE_H
#define SF_TILE_H

#include <SFML/Graphics.hpp>

/// Engine namespace
namespace sftile
{

struct Tile
{
    // Global ID of the tile
    int gid;

    // Rectangle of the tile
    sf::IntRect rect;
};

}

#endif