#ifndef SF_TILEMAP_H
#define SF_TILEMAP_H

#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "sf_camera.hpp"
#include "sf_tileset.hpp"
#include "sf_layer.hpp"
#include "sf_entity.hpp"

namespace sftile
{
class Loader;
class World;

// Orientation of the tile map
enum TilemapOrientation
{
    SFTILE_ORIENT_UNSUPPORTED = -1,
    SFTILE_ORIENT_ORTHOGONAL = 0//,
    // SFTILE_ORIENT_ISOMETRIC,
    // SFTILE_ORIENT_STAGGERED
};

// Format encoding of the data
enum TilemapEncoding
{
    SFTILE_ENCODING_UNSUPPORTED = -1,
    SFTILE_ENCODING_XML = 0//,
    // SFTILE_ENCODING_BASE64,
    // SFTILE_ENCODING_CSV
};

// Compression format of the data
enum TilemapCompression
{
    SFTILE_COMPRESSION_UNSUPPORTED = -1,
    SFTILE_COMPRESSION_NONE = 0//,
    // SFTILE_COMPRESSION_GZIP,
    // SFTILE_COMPRESSION_ZLIB
};

class Tilemap
{
friend class Loader;
friend class World;
public:
    // Default constructor
    Tilemap();

    // Copy constructor
    Tilemap(const Tilemap& _copy);

    // Copy assignment operator
    Tilemap& operator=(const Tilemap& _copy);

    // Destructor
    ~Tilemap();

    void RegisterCamera(shared_ptr<Camera> _camera);

    void HandleEvents(sf::Event _evt);

    void Update(sf::Time _elapsed_time);

    void Render(sf::RenderWindow& _window);

private:
    // Disabled move constuctor
    Tilemap(const Tilemap&& _moveable) = delete;

    // Camera being used in the tile map
    shared_ptr<Camera> camera;

    // Tileset to hold all the tilesets in the tile map
    shared_ptr<Tileset> tileset;

    // Vector holding all layers: tile, object, image
    vector< shared_ptr<Layer> > layers;

    // Vector of all of the entities in the map
    vector<Entity> entities;

    // Dimensions of the tile map in tiles
    sf::Vector2i map_dimensions;

    // Dimensions of the tiles in pixels
    sf::Vector2i tile_dimensions;

    // Orientation of the tilemap
    TilemapOrientation orientation;

    // Encoding of the data for the tilemap
    TilemapEncoding encoding;

    // Compression algorithm used on the data
    TilemapCompression compression;

    // Version of TMX
    float version;
};

}

#endif