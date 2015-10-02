#include <iostream>
    using std::cerr;
    using std::endl;
#include <string>
    using std::string;
#include <memory>
    using std::unique_ptr;
    using std::shared_ptr;

#include "../../inc/tile_engine/sf_loader.hpp"

#include "../../inc/tile_engine/sf_tilemap.hpp"
#include "../../inc/tile_engine/sf_tileset.hpp"
#include "../../inc/tile_engine/sf_tile_layer.hpp"
#include "../../inc/tile_engine/sf_object_layer.hpp"
#include "../../inc/tile_engine/sf_tile.hpp"

namespace sftile
{

// Helper function to check the validity of a pointer
bool CheckPointer(const void* _ptr, string _error)
{
  if (!_ptr)
  {
    cerr << _error << endl;
    return false;
  }
  return true;
}

bool Loader::ParseTmx(const string _path, Tilemap& _tilemap)
{
    // Load TMX file
    XMLDocument doc;
    doc.LoadFile(_path.c_str());

    // Check for errors in parsing
    if (doc.Error())
    {
        cerr << "XML parsing error: " << doc.ErrorID() << endl;
        return false;
    }

    // Get root map element
    const XMLElement* map_element = doc.FirstChildElement("map");
    if (!CheckPointer(map_element, "No map element"))
        return false;

    // Load basic map data
    map_element->QueryFloatAttribute("version", &_tilemap.version);
    map_element->QueryIntAttribute("width", &_tilemap.map_dimensions.x);
    map_element->QueryIntAttribute("height", &_tilemap.map_dimensions.y);
    map_element->QueryIntAttribute("tilewidth", &_tilemap.tile_dimensions.x);
    map_element->QueryIntAttribute("tileheight", &_tilemap.tile_dimensions.y);

    // Load the orientation of the map.
    // Only orthogonal is supported.
    string orient_str = map_element->Attribute("orientation");
    if (orient_str == "orthogonal")
        _tilemap.orientation = SFTILE_ORIENT_ORTHOGONAL;
    else
    {
        cerr << "Unsupported map orientation" << endl;
        return false;
    }

    // Parse the tilesets in the map
    const XMLElement* tileset_element = map_element->FirstChildElement("tileset");
    while (tileset_element)
    {   
        Tileset temp_tileset;
        if (!ParseTileset(tileset_element, temp_tileset))
        {
            cout << "Failed to parse tileset" << endl;
            return false;
        }
        else
            _tilemap.tileset = std::make_shared<Tileset>(temp_tileset);
        tileset_element = tileset_element->NextSiblingElement("tileset");
    }

    // Don't let your pointer dangle... That's gross.
    tileset_element = nullptr;

    // Parse all layers: tile, object, image
    const XMLElement* layer_element = map_element->FirstChildElement();
    while (layer_element)
    {
        string name = layer_element->Name();
        if (name == "layer")
        {
            TileLayer temp_tile_layer;
            temp_tile_layer.tileset = _tilemap.tileset;
            if (!ParseTileLayer(layer_element, temp_tile_layer))
            {
                cout << "Failed to parse tile layer" << endl;
                return false;
            }
            else
                _tilemap.layers.push_back(std::make_shared<TileLayer>(temp_tile_layer));
        }
        else if (name == "objectgroup")
        {
            ObjectLayer temp_object_layer;
            if (!ParseObjectLayer(layer_element, temp_object_layer))
            {
                cout << "Failed to parse object layer" << endl;
                return false;
            }
            else
                _tilemap.layers.push_back(std::make_shared<ObjectLayer>(temp_object_layer));
        }
        layer_element = layer_element->NextSiblingElement();
    }
    layer_element = nullptr;
    
    return true;
}
































bool Loader::ParseTileset(const XMLElement* _element, Tileset& _tileset)
{
    // First GID of the currently parsing tileset
    int first_gid = 0; _element->QueryIntAttribute("firstgid", &first_gid);
    _element->QueryIntAttribute("tilewidth", &_tileset.tile_dimensions.x);
    _element->QueryIntAttribute("tileheight", &_tileset.tile_dimensions.y);
    // Space around the tileset image
    int margin = 0; _element->QueryIntAttribute("margin", &margin);
    // Space in between each tile in the tileset
    int spacing = 0; _element->QueryIntAttribute("spacing", &spacing);

    // Load the image of the tileset and store
    // it in the SfTileset.
    const XMLElement* image_element = _element->FirstChildElement("image");
    if (!CheckPointer(image_element, "Couldn't locate image element in map file"))
        return false;

    // Load the tileset image
    string source = image_element->Attribute("source");
    if (!_tileset.tileset_image.loadFromFile(source))
    {
        cout << "Failed to load tileset image" << endl;
        return false;
    }

    int width = 0; image_element->QueryIntAttribute("width", &width);
    int height = 0; image_element->QueryIntAttribute("height", &height);
    image_element = nullptr;

    // Load all of the tiles into the tileset
    int gid = first_gid;
    for (int y = margin; y < height; y += spacing + _tileset.tile_dimensions.y)
        for (int x = margin; x < width; x += spacing + _tileset.tile_dimensions.x)
        {
            // We only save the rectangle around the tile
            // to help shorten loading times.
            // We can then load the texture every frame when we want
            // to display the tile.
            sf::IntRect rect(x, y, _tileset.tile_dimensions.x, _tileset.tile_dimensions.y);

            Tile temp_tile;
            temp_tile.gid = gid;
            temp_tile.rect = rect;
            _tileset.tiles.push_back(temp_tile);
        }

    return true;
}

////////////////////////////////////////////////////////////
bool Loader::ParseTileLayer(const XMLElement* _element, TileLayer& _tile_layer)
{
    // Load the arbitrary name of the layer
    string name = _element->Attribute("name");
  
    cout << "Loading layer: " << name << endl;

    // Load the dimensions of the layer
    sf::Vector2i layer_dimensions(0, 0);
    _element->QueryIntAttribute("width", &layer_dimensions.x);
    _element->QueryIntAttribute("height", &layer_dimensions.y);

    _tile_layer.name = name;
    _tile_layer.layer_dimensions = layer_dimensions;

    // Load the data node
    const XMLElement* data = _element->FirstChildElement("data");

    // Find out the encoding of the data
    string encoding_attr = (data->Attribute("encoding") != NULL) ? data->Attribute("encoding") : "xml";

    // Go-go-gadget, Parsers!
    if (encoding_attr == "xml" && !ParseXmlTileLayer(data, _tile_layer))
        return false;
    else if (encoding_attr == "base64" && !ParseBase64TileLayer(data, _tile_layer))
        return false;
    else if (encoding_attr == "csv" && !ParseCsvTileLayer(data, _tile_layer))
        return false;
    else
        return true;
}


////////////////////////////////////////////////////////////
bool Loader::ParseXmlTileLayer(const XMLElement* _element, TileLayer& _tile_layer)
{
    const XMLElement* tile = _element->FirstChildElement("tile");

    for (int y = 0; y < _tile_layer.layer_dimensions.y; ++y)
    {
        vector<int> temp;
        for (int x = 0; x < _tile_layer.layer_dimensions.x; ++x)
        {
            int gid = tile->IntAttribute("gid");

            temp.push_back(gid);

            tile = tile->NextSiblingElement("tile");
        }
        _tile_layer.tile_gids.push_back(temp);
    }
    // Voila! It's a boy!
    return true;
}


////////////////////////////////////////////////////////////
bool Loader::ParseBase64TileLayer(const XMLElement* _element, TileLayer& _tile_layer)
{
    cout << "Cannot parse Base64 data" << endl;
    return false;
}


////////////////////////////////////////////////////////////
bool Loader::ParseCsvTileLayer(const XMLElement* _element, TileLayer& _tile_layer)
{
    cout << "Cannot parse CSV data" << endl;
    return false;
}











bool Loader::ParseObjectLayer(const XMLElement* _element, ObjectLayer& _object_layer)
{
    _object_layer.name = _element->Attribute("name");
    _object_layer.layer_dimensions = sf::Vector2i(_element->IntAttribute("width"), _element->IntAttribute("height"));

    const XMLElement* object = _element->FirstChildElement("object");

    while (object)
    {
        Object temp;

        temp.name = object->Attribute("name") ? object->Attribute("name") : "";
        temp.type = object->Attribute("type") ? object->Attribute("type") : "";
        object->QueryIntAttribute("gid", &temp.gid);
        object->QueryBoolAttribute("visible", &temp.visible);

        temp.position = sf::Vector2i(object->IntAttribute("x"), object->IntAttribute("y"));
        temp.dimensions = sf::Vector2i(object->IntAttribute("width"), object->IntAttribute("height"));

        _object_layer.objects.push_back(temp);

        object = object->NextSiblingElement("object");
    }
    return true;
}

}