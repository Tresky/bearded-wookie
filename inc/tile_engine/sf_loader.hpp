#ifndef SF_LOADER_HPP
#define SF_LOADER_HPP

#include "../../extlibs/tinyxml2/tinyxml2.hpp"
    using namespace tinyxml2;

namespace tinyxml2
{
    class XMLElement;
}

namespace sftile
{
class Tilemap;
class Tileset;
class TileLayer;
class ObjectLayer;

class Loader
{
public:
    bool ParseTmx(const string _path, Tilemap& _tilemap);

private:
    bool ParseTileset(const XMLElement* _element, Tileset& _tileset);

    bool ParseTileLayer(const XMLElement* _element, TileLayer& _tile_layer);

    bool ParseXmlTileLayer(const XMLElement* _element, TileLayer& _tile_layer);

    bool ParseBase64TileLayer(const XMLElement* _element, TileLayer& _tile_layer);

    bool ParseCsvTileLayer(const XMLElement* _element, TileLayer& _tile_layer);

    bool ParseObjectLayer(const XMLElement* _element, ObjectLayer& _object_layer);
};

}

#endif