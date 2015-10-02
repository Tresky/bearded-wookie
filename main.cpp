#include <iostream>
    using std::cout;
    using std::endl;
#include <string>

#include <SFML/Graphics.hpp>

#include "inc/engine/state_stack.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "Crawler Demo");
    window.setFramerateLimit(60);

    // Create state stack and load all potential states
    StateStack game_mode;
    game_mode.AddState("main-menu", shared_ptr<State>(new MainMenuState()));
    game_mode.AddState("local-map", shared_ptr<State>(new LocalMapState(window)));
    /*game_mode.AddState("world-map", shared_ptr<State>*new WorldMapState()));
    game_mode.AddState("battle", shared_ptr<State>(new BattleState()));
    game_mode.AddState("ingame-menu", shared_ptr<State>(new InGameMenuState()));*/

    // Push the default state
    game_mode.Push("main-menu");


    sf::Font font;
    font.loadFromFile("res/fonts/sen_regular.otf");
    sf::Text framerate("0", font);
    framerate.setCharacterSize(30);
    framerate.setColor(sf::Color::White);
    framerate.setPosition(15, 15);

    sf::Clock clk;
    while (window.isOpen())
    {
        sf::Event evt;
        while (window.pollEvent(evt))
        {
            game_mode.HandleEvents(evt);

            if (evt.type == sf::Event::Closed)
                window.close();

            if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::M)
                game_mode.Push("local-map");

            if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::P)
                game_mode.Pop();
        }

        sf::Time frame_time = clk.restart();
        float elapsed_time = frame_time.asMilliseconds();
        game_mode.Update(frame_time);

        window.clear();

        game_mode.Render(window);

        framerate.setString("FPS: " + std::to_string((int)(1.f / frame_time.asSeconds())));
        window.draw(framerate);

        window.display();
    }

    return 0;
}