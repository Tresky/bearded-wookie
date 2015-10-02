#include <iostream>
    using std::cout;
    using std::endl;

#include "../../../inc/engine/states/local_map_state.hpp"

LocalMapState::LocalMapState(sf::RenderWindow& _window)
    : world(_window)
    , camera(new sftile::Camera(_window.getSize().x, _window.getSize().y))
{
    world.RegisterCamera(camera);
    world.AddTilemap("demo_map.tmx", "demo_map");
    world.ChangeTilemap("demo_map");

    texture.loadFromFile("./res/actors/actor0.png");

    sprite = std::unique_ptr<MobileSprite>(new MobileSprite(texture));
    sprite->GetSpriteAnimation().AddAnimation("walk-south", 0, 0, 32, 32, 3, 0.2f);
    sprite->GetSpriteAnimation().AddAnimation("walk-west", 0, 32, 32, 32, 3, 0.2f);
    sprite->GetSpriteAnimation().AddAnimation("walk-east", 0, 64, 32, 32, 3, 0.2f);
    sprite->GetSpriteAnimation().AddAnimation("walk-north", 0, 96, 32, 32, 3, 0.2f);

    sprite->GetSpriteAnimation().AddAnimation("idle-south", 0, 0, 32, 32, 2, 0.5f);
    sprite->GetSpriteAnimation().AddAnimation("idle-west", 0, 32, 32, 32, 2, 0.5f);
    sprite->GetSpriteAnimation().AddAnimation("idle-east", 0, 64, 32, 32, 2, 0.5f);
    sprite->GetSpriteAnimation().AddAnimation("idle-north", 0, 96, 32, 32, 2, 0.5f);

    sprite->GetSpriteAnimation().SetCurrentAnimation("idle-south");

    sprite->SetPosition(sf::Vector2f(200, 200));
    sprite->SetSpeed(3);
}

void LocalMapState::Update(sf::Time _elapsed_time)
{
    bool west = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool east = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool north = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool south = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    string anim = sprite->GetSpriteAnimation().GetCurrentAnimation();
    if (west)
    {
        if (anim != "walk-west")
            sprite->GetSpriteAnimation().SetCurrentAnimation("walk-west");
        sprite->GetSpriteAnimation().Move(-2, 0);
    }
    else if (east)
    {
        if (anim != "walk-east")
            sprite->GetSpriteAnimation().SetCurrentAnimation("walk-east");
        sprite->GetSpriteAnimation().Move(2, 0);
    }
    else if (north)
    {
        if (anim != "walk-north")
            sprite->GetSpriteAnimation().SetCurrentAnimation("walk-north");
        sprite->GetSpriteAnimation().Move(0, -2);
    }
    else if (south)
    {
        if (anim != "walk-south")
            sprite->GetSpriteAnimation().SetCurrentAnimation("walk-south");
        sprite->GetSpriteAnimation().Move(0, 2);
    }
    else if (!west && !east && !north && !south)
    {
        if (anim == "walk-west")
            sprite->GetSpriteAnimation().SetCurrentAnimation("idle-west");
        else if (anim == "walk-east")
            sprite->GetSpriteAnimation().SetCurrentAnimation("idle-east");
        else if (anim == "walk-north")
            sprite->GetSpriteAnimation().SetCurrentAnimation("idle-north");
        else if (anim == "walk-south")
            sprite->GetSpriteAnimation().SetCurrentAnimation("idle-south");
    }

    sprite->Update(_elapsed_time);
    world.Update(_elapsed_time);
}

void LocalMapState::Render(sf::RenderWindow& _window)
{
    world.Render(_window);
    sprite->Render(_window);
}

void LocalMapState::OnEnter(string _params)
{
    cout << "Entering Local Map" << endl;
}

void LocalMapState::OnExit()
{
    cout << "Exiting Local Map" << endl;
}