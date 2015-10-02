#ifndef LOCAL_MAP_STATE_H
#define LOCAL_MAP_STATE_H

#include "../state.hpp"

#include "../../tile_engine/sf_world.hpp"
#include "../mobile_sprite.hpp"

/*
 * @class LocalMapState
 * @desc Child class that inherits methods and 
 *   properties from State. This represents the
 *   state for local map of the game. This state
 *   will be handled by the StateStack.
 */
class LocalMapState : public State
{
public:
    /*
     * Default constructor
     *
     * @param[in] _window SFML Window that the game runs in
     */
    LocalMapState(sf::RenderWindow& _window);

    /*
     * Updates the current game state.
     * 
     * @param[in] _elapsed_time Current frames elapsed time
     *
     * @retval none
     */
    void Update(sf::Time _elapsed_time);

    /*
     * Renders the current game state.
     *
     * @param[in] _window Window to render to
     *
     * @retval none
     */
    void Render(sf::RenderWindow& _window);

    /*
     * Executes whenever the state is first entered.
     *
     * @param[in] _params String of parameters to pass into the state
     *
     * @retval none
     */
    void OnEnter(string _params);

    /*
     * Executes whenever the state is exited.
     *
     * @retval none
     */
    void OnExit();

private:
    // Disabled copy constructor
    LocalMapState(const LocalMapState& _copy) = delete;

    // Disabled copy assignment operator
    LocalMapState& operator=(const LocalMapState& _copy) = delete;

    // Disabled move constructor
    LocalMapState(const LocalMapState&& _moveable) = delete;

    // Tile engine world
    sftile::World world;

    // Camera for the world
    shared_ptr<sftile::Camera> camera;

    // Test sprite
    std::unique_ptr<MobileSprite> sprite;
    sf::Texture texture;
};

#endif