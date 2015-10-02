#include <iostream>
    using std::cout;
    using std::endl;

#include "../../inc/tile_engine/sf_tile_layer.hpp"

#include "../../inc/tile_engine/sf_tileset.hpp"

namespace sftile
{

TileLayer::TileLayer()
    : Layer()
    , tile_gids()
    , tileset(nullptr)
{
    //cout << "TileLayer: default()" << endl;
}

TileLayer::TileLayer(const TileLayer& _copy)
    : Layer(_copy)
    , tile_gids(_copy.tile_gids)
    , tileset(_copy.tileset)
{
    //cout << "TileLayer: copy()" << endl;
}

TileLayer& TileLayer::operator=(const TileLayer& _copy)
{
    //cout << "TileLayer: operator()" << endl;
    if (this != &_copy)
    {
        Layer::operator=(_copy);

        TileLayer temp(_copy);

        std::swap(tile_gids, temp.tile_gids);
        std::swap(tileset, temp.tileset);
    }
    return *this;
}

TileLayer::TileLayer(TileLayer&& _copy)
    : Layer(std::move(_copy))
    , tile_gids(std::move(_copy.tile_gids))
    , tileset(std::move(_copy.tileset))
{
    //cout << "TileLayer: move()" << endl;
}

int TileLayer::GetTileGID(const int _x, const int _y)
{
    /// The TMX tileset stores tiles startring from 1.
    /// Our vector stores them starting from 0.
    int gid = tile_gids.at(_y).at(_x);

    return gid;
}

string TileLayer::GetName()
{
    return name;
}

string TileLayer::GetType()
{
    return "tile";
}

sf::Vector2i TileLayer::GetDimensions()
{
    return layer_dimensions;
}

void TileLayer::Render(sf::RenderWindow& _window, sf::Vector2i _offset, sf::IntRect _bounds, sf::Vector2i _tile_dimensions)
{
    //cout << "\t\tTileLayer: render()" << endl;
    // These for loops ensure that we don't render anything
    // outside of the camera's view. That would be a waste of
    // the processor's power.
    for (int y = 0, tile_y = _bounds.top; y < _bounds.height; ++y, ++tile_y)
    {
        //cout << y << ":\t";
        for (int x = 0, tile_x = _bounds.left; x < _bounds.width; ++x, ++tile_x)
        {
            //cout << x << " ";
            // Guard against trying to render outside of
            // the map. There lie dragons.
            if (tile_x < 0 || tile_y < 0)
                continue;
            if (tile_x >= layer_dimensions.x || tile_y >= layer_dimensions.y)
                continue;

            // Get the GID of the tile
            int gid = GetTileGID(tile_x, tile_y);

            // GID 0 is a blank tile, so don't render
            if (gid == 0)
                continue;

            // Adjust the tile coordinates by the size of the tiles
            // and by substracting how much the camera is offset from the
            // tile grid.
            const float pos_x = static_cast<float>(x * _tile_dimensions.x - _offset.x);
            const float pos_y = static_cast<float>(y * _tile_dimensions.y - _offset.y);
            tileset->RenderTile(_window, gid, pos_x, pos_y);
        }
        //cout << endl;
    }
}

}

