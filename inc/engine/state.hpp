#ifndef STATE_H
#define STATE_H

#include <string>
    using std::string;

#include <SFML/Graphics.hpp>

/*
 * @class State
 * @desc Abstract class that is inherited by
 *   various higher level state types. These states
 *   are used to denote and control the current
 *   state that the game's StateStack is in.
 *
 *   This class provides only a few very basic 
 *   functionalities for the StateStack to utilize.
 */
class State
{
public:
    // Default constructor
    State() {}

    /*
     * Updates the current game state.
     * Purely virtual function.
     * 
     * @param[in] _elapsed_time Current frames elapsed time
     *
     * @retval none
     */
    virtual void Update(sf::Time _elapsed_time) = 0;

    /*
     * Renders the current game state.
     * Purely virtual function.
     *
     * @param[in] _window Window to render to
     *
     * @retval none
     */
    virtual void Render(sf::RenderWindow& _window) = 0;

    /*
     * Executes whenever the state is first entered.
     * Purely virtual function.
     *
     * @param[in] _params String of parameters to pass into the state
     *
     * @retval none
     */
    virtual void OnEnter(string _params) = 0;

    /*
     * Executes whenever the state is exited.
     * Purely virtual function.
     *
     * @retval none
     */
    virtual void OnExit() = 0;

protected:
    // Disabled copy constructor
    State(const State& _copy) = delete;

    // Disabled copy assignment operator
    State& operator=(const State& _copy) = delete;

    // Disabled move constructor
    State(const State&& _moveable) = delete;
};

#endif