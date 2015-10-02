#ifndef SF_CAMERA_H
#define SF_CAMERA_H

#include <iostream>
    using std::cout;
    using std::endl;

#include <SFML/Graphics.hpp>

#include "sf_entity.hpp"

namespace sftile
{

// Represents the tracking mode that the smart camera
// is currently in.
enum TrackingMode
{
    SF_TRACK_OFF = 0, // Supported
    SF_TRACK_KEYS_PRESS, // Supported
    SF_TRACK_MOUSE_CLICK, // Supported
    SF_TRACK_MOUSE_CLICKDRAG, // Supported
    SF_TRACK_ENTITY
};

class Camera
{
public:
    // Default constructor
    Camera(const float _width, const float _height);

    // Copy constructor
    Camera(const Camera& _copy);

    // Copy assignment operator
    Camera& operator=(const Camera& _copy);

    // Move constuctor
    Camera(Camera&& _moveable);

    // Destructor
    ~Camera();

    void SetPosition(const float _x, const float _y);

    void SetCenterPosition(const float _x, const float _y);

    void MoveTo(const float _x, const float _y);

    void MoveCenterTo(const float _x, const float _y);

    const sf::Vector2f GetPosition();

    const sf::Vector2f GetCenterPosition();

    void SetTrackMode(const TrackingMode _mode);

    void SetTrackedKeys(const sf::Keyboard::Key _up, const sf::Keyboard::Key _down, const sf::Keyboard::Key _left, const sf::Keyboard::Key _right);

    void SetTrackedMouseButton(const sf::Mouse::Button _button);

    void SetTrackedEntity(shared_ptr<Entity> _camera);

    const sf::Vector2i GetTileOffset(const int _tile_width, const int _tile_height);

    const sf::IntRect GetBounds(const int _tile_width, const int _tile_height);

    void Update(sf::Time _elapsed_time);

private:
    // Default constructor
    Camera() = delete;

    void CalculatePosition();

    //   Current position of the top-left corner of the camera
    sf::Vector2f position;

    // Current target the camera is moving towards
    sf::Vector2f target;

    // Size of the camera in pixels
    // This is usually the size of the window
    sf::Vector2f size;

    // Bounds of the portion of the map being displayed
    sf::IntRect bounds;

    // True is the position of the camera needs to be updated
    bool need_update;

    // Current tracking mode of the camera
    TrackingMode tracking_mode;

    // Keyboard keys being tracked for directions
    sf::Keyboard::Key tracked_up, tracked_down, tracked_left, tracked_right;

    // Mouse button being tracked for use
    sf::Mouse::Button tracked_button;

    // Entity object to be tracked
    shared_ptr<Entity> tracked_entity;

    // Initial position of the camera for click-drag purposes
    sf::Vector2f click_drag_intial_position;
};

}

#endif




//     class Camera
// {
// public:
//     explicit Camera(const float _width, const float _height);

//     explicit Camera(const Camera& _copy);

//     Camera& operator=(const Camera& _copy);

//     virtual void SetPosition(const float _x, const float _y) = 0;

//     virtual void SetCenterPosition(const float _x, const float _y) = 0;

//     virtual void MoveTo(const float _x, const float _y) = 0;

//     virtual void MoveCenterTo(const float _x, const float _y) = 0;

//     virtual const sf::Vector2f GetPosition() = 0;

//     virtual const sf::Vector2f GetCenterPosition() = 0;

//     virtual void Update(float _elapsed_time) = 0;

//     virtual void HandleEvents(sf::Event& _evt) = 0;

//     const sf::Vector2i GetTileOffset(const int _tile_width, const int _tile_height);

//     const sf::IntRect GetBounds(const int _tile_width, const int _tile_height);

// protected:
//     // Current position of the top-left corner of the camera
//     sf::Vector2f position;

//     // Current target that the camera is heading towards
//     sf::Vector2f target;

//     // Size of the camera in pixels (usually the size of the window)
//     sf::Vector2f size;

//     // Bounds around the portion of the map that is currently in the camera
//     sf::IntRect bounds;

//     // True if the position of the camera needs to be updated
//     bool need_update;

// private:
//     explicit Camera() = delete;
// };

// }

// #endif
