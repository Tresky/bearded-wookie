#include <iostream>
    using std::cout;
    using std::endl;

#include "../../../inc/engine/states/main_menu_state.hpp"

MainMenuState::MainMenuState()
{
    
}

void MainMenuState::Update(sf::Time _elapsed_time)
{

}

void MainMenuState::Render(sf::RenderWindow& _window)
{
    sf::Font font;
    font.loadFromFile("res/fonts/sen_regular.otf");

    sf::Text text("Main Menu", font);
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);
    text.setPosition(_window.getSize().x / 2.f - text.getLocalBounds().width / 2.f,
                     _window.getSize().y / 2.f - text.getLocalBounds().height / 2.f);
    _window.draw(text);
}

void MainMenuState::OnEnter(string _params)
{
    cout << "Entering Main Menu" << endl;
}

void MainMenuState::OnExit()
{
    cout << "Exiting Main Menu" << endl;
}