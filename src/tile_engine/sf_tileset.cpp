#include <iostream>
    using std::cout;
    using std::endl;

#include "../../inc/tile_engine/sf_tileset.hpp"

namespace sftile
{

Tileset::Tileset()
    : tile_dimensions(32, 32)
    , tiles()
    , tileset_image()
{
    //cout << "\tTileset: default()" << endl;
}

Tileset::Tileset(const Tileset& _copy)
    : tile_dimensions(_copy.tile_dimensions)
    , tiles(_copy.tiles)
    , tileset_image(_copy.tileset_image)
{
    //cout << "\tTileset: copy()" << endl;
    tileset_image.loadFromImage(_copy.tileset_image.copyToImage());
}

Tileset& Tileset::operator=(const Tileset& _copy)
{
    //cout << "\tTileset: operator()" << endl;
    if (this != &_copy)
    {
        Tileset temp(_copy);

        std::swap(tile_dimensions, temp.tile_dimensions);
        std::swap(tiles, temp.tiles);
        
        tileset_image.loadFromImage(temp.tileset_image.copyToImage());
    }

    return *this;
}

Tileset::Tileset(Tileset&& _moveable)
{
    //cout << "\tTileset: move()" << endl;
}

Tileset::~Tileset()
{}

Tile Tileset::GetTile(const unsigned int _id)
{
    return tiles.at(_id - 1);
}

sf::Vector2i Tileset::GetTileDimensions()
{
    return tile_dimensions;
}

const int Tileset::GetNumTiles()
{
    return tiles.size();
}

void Tileset::RenderTile(sf::RenderWindow& _window, const unsigned int _id, const float _x, const float _y)
{
    Tile tile = GetTile(_id);
    sf::Sprite sprite(tileset_image, tile.rect);
    sprite.setPosition(_x, _y);

    _window.draw(sprite);
}

}