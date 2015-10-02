#ifndef SF_WORLD_H
#define SF_WORLD_H

#include <string>
    using std::string;
#include <map>
    using std::map;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "sf_tilemap.hpp"
#include "sf_loader.hpp"

namespace sftile
{

class World
{
public:
    // Default constructor
    explicit World(sf::RenderWindow& _window);

    // Destructor
    ~World();

    void RegisterCamera(shared_ptr<Camera> _camera);

    void ChangeTilemap(const string _key);

    shared_ptr<Tilemap> AddTilemap(const string _path, const string _key);

    shared_ptr<Tilemap> RemoveTilemap(const string _key);

    void Update(sf::Time _elapsed_time);

    void Render(sf::RenderWindow& _window);

private:
    // Disabled copy constructor
    World(const World& _copy) = delete;

    // Disabled copy assignment operator
    World& operator=(const World& _copy) = delete;

    // Disabled move constuctor
    World(const World&& _moveable) = delete;

    // Map of key associated tilemaps
    map<string, shared_ptr<Tilemap>> tilemaps;

    // Current tilemap being used in game
    string current_tilemap;

    // Camera to display the world with
    shared_ptr<Camera> camera;

    // Object to parse TMX data into a tilemap
    Loader parser;
};

}

#endif