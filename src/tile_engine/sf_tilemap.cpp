#include <iostream>
    using std::cout;
    using std::endl;

#include "../../inc/tile_engine/sf_tilemap.hpp"

namespace sftile
{

Tilemap::Tilemap()
    : camera(nullptr)
    , tileset()
    , layers()
    , map_dimensions(-1, -1)
    , tile_dimensions(-1, -1)
    , orientation(SFTILE_ORIENT_UNSUPPORTED)
    , encoding(SFTILE_ENCODING_UNSUPPORTED)
    , compression(SFTILE_COMPRESSION_UNSUPPORTED)
    , version(1.0)
{
    //cout << "\tTilemap: default()" << endl;
}

Tilemap::Tilemap(const Tilemap& _copy)
    : camera(_copy.camera)
    , tileset(_copy.tileset)
    , map_dimensions(_copy.map_dimensions)
    , tile_dimensions(_copy.tile_dimensions)
    , orientation(_copy.orientation)
    , encoding(_copy.encoding)
    , compression(_copy.compression)
    , version(_copy.version)
{
    //cout << "\tTilemap: copy()" << endl;
    for (unsigned int i = 0; i < _copy.layers.size(); ++i)
        layers.push_back(_copy.layers[i]);
}

Tilemap& Tilemap::operator=(const Tilemap& _copy)
{
    //cout << "\tTilemap: operator()" << endl;
    if (this != &_copy)
    {
        Tilemap temp(_copy);

        std::swap(tileset, temp.tileset);
        std::swap(map_dimensions, temp.map_dimensions);
        std::swap(tile_dimensions, temp.tile_dimensions);
        std::swap(orientation, temp.orientation);
        std::swap(encoding, temp.encoding);
        std::swap(compression, temp.compression);
        std::swap(version, temp.version);

        camera = temp.camera;

        while(temp.layers.size() > 0)
        {
            const auto it = temp.layers.begin();
            layers.push_back( *it );
            temp.layers.erase(it);
        }
    }

    return *this;
}

Tilemap::~Tilemap()
{

}

void Tilemap::RegisterCamera(shared_ptr<Camera> _camera)
{
    camera = _camera;
}

void Tilemap::HandleEvents(sf::Event _evt)
{
    //camera->HandleEvents(_evt);
}

void Tilemap::Update(sf::Time _elapsed_time)
{
    //cout << "\tTilemap: update()" << endl;
    camera->Update(_elapsed_time);
}

void Tilemap::Render(sf::RenderWindow& _window)
{
    //cout << "\tTilemap: render()" << endl;
    sf::Vector2i offset = camera->GetTileOffset(tile_dimensions.x, tile_dimensions.y);
    sf::IntRect bounds = camera->GetBounds(tile_dimensions.x, tile_dimensions.y);

    //cout << "\t\t\t\tOffset: " << offset.x << "  " << offset.y << endl;
    //cout << "\t\t\t\tBounds: " << bounds.left << "  " << bounds.top << "  " << bounds.width << "  " << bounds.height << endl;




    //cout << "\tFor" << endl;
    for (unsigned int i = 0; i < layers.size(); ++i)
    {
        //cout << "\t\tLayer Size: " << layers.size() << endl;
        //cout << "\t\tIndex: " << i << endl;
        if (layers[i]->GetName() == "Characters")
        {
            
            continue;
        }
        layers[i]->Render(_window, offset, bounds, tile_dimensions);
    }
}

}