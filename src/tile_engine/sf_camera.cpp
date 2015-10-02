#include <iostream>
    using std::cout;
    using std::endl;

#include "../../inc/tile_engine/sf_camera.hpp"

namespace sftile
{

Camera::Camera(const float _width, const float _height)
    : position(0.f, 0.f)
    , target(0.f, 0.f)
    , size(_width, _height)
    , bounds(0, 0, static_cast<int>(_width), static_cast<int>(_height))
    , need_update(false)
    , tracking_mode(SF_TRACK_KEYS_PRESS)
    , tracked_up(sf::Keyboard::Key::S)
    , tracked_down(sf::Keyboard::Key::W)
    , tracked_left(sf::Keyboard::Key::D)
    , tracked_right(sf::Keyboard::Key::A)
    , tracked_button(sf::Mouse::Button::Left)
    , tracked_entity()
{}

Camera::Camera(const Camera& _copy)
    : position(_copy.position)
    , target(_copy.target)
    , size(_copy.size)
    , bounds(_copy.bounds)
    , need_update(_copy.need_update)
    , tracking_mode(_copy.tracking_mode)
    , tracked_up(_copy.tracked_up)
    , tracked_down(_copy.tracked_down)
    , tracked_left(_copy.tracked_left)
    , tracked_right(_copy.tracked_right)
    , tracked_button(_copy.tracked_button)
    , tracked_entity(_copy.tracked_entity)
{}

Camera& Camera::operator=(const Camera& _copy)
{
    if (this != &_copy)
    {
        Camera temp(_copy);

        std::swap(position, temp.position);
        std::swap(target, temp.target);
        std::swap(size, temp.size);
        std::swap(bounds, temp.bounds);
        std::swap(need_update, temp.need_update);
        std::swap(tracking_mode, temp.tracking_mode);
        std::swap(tracked_up, temp.tracked_up);
        std::swap(tracked_down, temp.tracked_down);
        std::swap(tracked_left, temp.tracked_left);
        std::swap(tracked_right, temp.tracked_right);
        std::swap(tracked_button, temp.tracked_button);
        std::swap(tracked_entity, temp.tracked_entity);
    }

    return *this;
}

Camera::Camera(Camera&& _moveable)
    : position(std::move(_moveable.position))
    , target(std::move(_moveable.target))
    , size(std::move(_moveable.size))
    , bounds(std::move(_moveable.bounds))
    , need_update(std::move(_moveable.need_update))
    , tracking_mode(std::move(_moveable.tracking_mode))
    , tracked_up(std::move(_moveable.tracked_up))
    , tracked_down(std::move(_moveable.tracked_down))
    , tracked_left(std::move(_moveable.tracked_left))
    , tracked_right(std::move(_moveable.tracked_right))
    , tracked_button(std::move(_moveable.tracked_button))
    , tracked_entity(std::move(_moveable.tracked_entity))
{}

Camera::~Camera()
{

}

void Camera::SetPosition(const float _x, const float _y)
{
    position = sf::Vector2f(_x, _y);
    target = sf::Vector2f(_x, _y);

    need_update = true;
}

void Camera::SetCenterPosition(const float _x, const float _y)
{
    float x = _x - size.x / 2.f;
    float y = _y - size.y / 2.f;

    position = sf::Vector2f(x, y);
    target = sf::Vector2f(x, y);

    need_update = true;
}

void Camera::MoveTo(const float _x, const float _y)
{
    target = sf::Vector2f(_x, _y);

    need_update = true;
}

void Camera::MoveCenterTo(const float _x, const float _y)
{
    float x = _x - size.x / 2.f;
    float y = _y - size.y / 2.f;

    target = sf::Vector2f(x, y);

    need_update = true;
}

const sf::Vector2f Camera::GetPosition()
{
    return position;
}

const sf::Vector2f Camera::GetCenterPosition()
{
    sf::Vector2f center(position.x + size.x / 2.f, position.y + size.y / 2.f);
    return center;
}

void Camera::SetTrackMode(const TrackingMode _mode)
{
    tracking_mode = _mode;
}

void Camera::SetTrackedKeys(const sf::Keyboard::Key _up, const sf::Keyboard::Key _down, const sf::Keyboard::Key _left, const sf::Keyboard::Key _right)
{
    tracked_up = _up;
    tracked_down = _down;
    tracked_left = _left;
    tracked_right = _right;
}

void Camera::SetTrackedMouseButton(const sf::Mouse::Button _button)
{
    tracked_button = _button;
}

void Camera::SetTrackedEntity(shared_ptr<Entity> _entity)
{
    tracked_entity = _entity;
}

const sf::Vector2i Camera::GetTileOffset(const int _tile_width, const int _tile_height)
{
    sf::Vector2i temp;
    temp.x = static_cast<int>(position.x) % _tile_width;
    temp.y = static_cast<int>(position.y) % _tile_height;
    return temp;
}

const sf::IntRect Camera::GetBounds(const int _tile_width, const int _tile_height)
{
    int tile_x = 0, tile_y = 0;
    int tiles_across = 0, tiles_down = 0;

    sf::IntRect rect(0, 0, 0, 0);

    if (_tile_width != 0 && _tile_height != 0)
    {
        tile_x = static_cast<int>(position.x / _tile_width);
        tile_y = static_cast<int>(position.y / _tile_height);

        /// If the whole size of the camera is not divisible by the tile
        /// size, we need to add one more tile to the bounds.
        /// We also have to add one to the numbers to make the tile count
        /// begin at 1 as opposed to 0.
        tiles_across = static_cast<int>(size.x / _tile_width) + 2;
        tiles_down = static_cast<int>(size.y / _tile_height) + 2;

        /// If we are not perfectly positioned over the tiles, we need to
        /// add one more tile to the frame to make sure no black is shown.
        if (static_cast<int>(position.x) % _tile_width != 0)
          ++tiles_across;
        if (static_cast<int>(position.y) % _tile_height != 0)
          ++tiles_down;
    }

    rect = sf::IntRect(tile_x, tile_y, tiles_across, tiles_down);
    return rect;
}

void Camera::Update(sf::Time _elapsed_time)
{
    //cout << "\t\tCamera: update()" << endl;

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    //     SetPosition(GetPosition().x, GetPosition().y - 2);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    //     SetPosition(GetPosition().x - 2, GetPosition().y);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    //     SetPosition(GetPosition().x, GetPosition().y + 2);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    //     SetPosition(GetPosition().x + 2, GetPosition().y);

    if (need_update)
        CalculatePosition();
}

void Camera::CalculatePosition()
{
    const float x_dist = static_cast<float>(target.x - position.x);
    const float y_dist = static_cast<float>(target.y - position.y);

    //printf("TX: %f\tPX: %f\tTY: %f\tPY: %f\n", target.x, position.x, target.y, position.y);

    const float distance = sqrt(pow(x_dist, 2) + pow(y_dist, 2));
    //cout << "Distance: " << distance << endl;
    // A spin-off of Xeno's Paradox prohibits us from reaching the
    // target, so we can counter that by giving up when we are within 1 pixel.
    if (distance <= 1.f)
    {
        position = target;
        need_update = false;
    }
    else
    {
        float velocity = distance / 60.f;

        // If our velocity falls below 1.0, we will never enter
        // Sovngarde!
        if (velocity < 1.f)
            velocity = 1.f;
        //cout << "YDIST: " << y_dist << "\tVEL: " << velocity << "\tDIST: " << distance << endl;
        const float velocity_x = x_dist * (velocity / distance);
        const float velocity_y = y_dist * (velocity / distance);

        position.x += velocity_x;
        position.y += velocity_y;
    }
}

}