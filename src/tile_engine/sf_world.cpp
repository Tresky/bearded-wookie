#include <iostream>
    using std::cout;
    using std::cerr;
    using std::endl;
#include <cassert>

#include "../../inc/tile_engine/sf_world.hpp"

namespace sftile
{

World::World(sf::RenderWindow& _window)
    : tilemaps()
    , current_tilemap("")
    , camera(nullptr)
    , parser()
{

}

World::~World()
{

}

void World::RegisterCamera(shared_ptr<Camera> _camera)
{
    if (!_camera)
        cerr << "World: Camera to be registered is null." << endl;
    else
        camera = _camera;
}

void World::ChangeTilemap(const string _key)
{
    if (_key == "")
        cerr << "World: Invalid key specified." << endl;
    else if (tilemaps.find(_key) == tilemaps.end())
        cerr << "World: Tilemap with specified key doesn't exist." << endl;
    else
        current_tilemap = _key;
}

shared_ptr<Tilemap> World::AddTilemap(const string _path, const string _key)
{
    if (_path == "" || _key == "")
        cerr << "World: Incorrect path or key specified." << endl;
    else if (!camera)
        cerr << "World: Registered camera required before loading a tilemap." << endl;
    else if (tilemaps.find(_key) != tilemaps.end())
        cerr << "World: Tilemap with specified key already exists." << endl;
    else
    {
        Tilemap temp_map;
        if (!parser.ParseTmx(_path, temp_map))
        {
            cerr << "World: Failed to load tilemap: " << _path << endl;
            return nullptr;
        }
        temp_map.RegisterCamera(camera);

        //cout << "TEST: " << temp_map.layers.size() << endl;
        tilemaps[_key] = std::make_shared<Tilemap>(temp_map);
        //cout << "TEST2: " << tilemaps[_key]->tileset->GetTileDimensions().x << endl;

        return tilemaps[_key];
    }
    return nullptr;
}

shared_ptr<Tilemap> World::RemoveTilemap(const string _key)
{
    if (_key == "")
        cerr << "World: Invalid key specified." << endl;
    else if (tilemaps.find(_key) == tilemaps.end())
        cerr << "World: Tilemap with specified key doesn't exist." << endl;
    else
    {
        shared_ptr<Tilemap> temp = nullptr;

        temp = tilemaps[_key];
        tilemaps.erase(_key);

        return temp;
    }
    return nullptr;
}

void World::Update(sf::Time _elapsed_time)
{
    // Checking for map existence every iteration
    // would be too time consuming, so I will
    // trust that the map will exist. The ChangeTilemap()
    // function is the only way to change the current and
    // it handles checking.
    //cout << "World: update()" << endl;
    if (current_tilemap != "")
        tilemaps[current_tilemap]->Update(_elapsed_time);
}

// void World::HandleEvents(sf::Event _evt)
// {
//     //cout << "World: events()" << endl;
//     //if ()
// }

void World::Render(sf::RenderWindow& _window)
{
    // Same as Update(). I will trust that the map exists
    // for the sake of not wasting processing power.
    //cout << "World: render()" << endl;
    if (current_tilemap != "")
        tilemaps[current_tilemap]->Render(_window);
}

}