#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../state.hpp"

/*
 * @class MainMenuState
 * @desc Child class that inherits methods and 
 *   properties from State. This represents the
 *   state for main menu of the game. This state
 *   will be handled by the StateStack.
 */
class MainMenuState: public State
{
public:
    // Default constructor
    MainMenuState();

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
    MainMenuState(const MainMenuState& _copy) = delete;

    // Disabled copy assignment operator
    MainMenuState& operator=(const MainMenuState& _copy) = delete;

    // Disabled move constructor
    MainMenuState(const MainMenuState&& _moveable) = delete;
};

#endif