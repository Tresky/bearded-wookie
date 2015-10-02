#ifndef SPRITE_ANIMATION_HPP
#define SPRITE_ANIMATION_HPP

#include <map>
    using std::map;
#include <string>
    using std::string;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "frame_animation.hpp"

class SpriteAnimation
{
public:
    explicit SpriteAnimation(sf::Texture _texture);

    SpriteAnimation(const SpriteAnimation& _copy);

    SpriteAnimation(SpriteAnimation&& _moveable);

    SpriteAnimation& operator=(const SpriteAnimation& _copy);

    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f _position);

    int GetXPosition();
    void SetXPosition(const int _x);

    int GetYPosition();
    void SetYPosition(const int _y);

    int GetWidth();
    int GetHeight();

    bool GetAutoRotate();
    void SetAutoRotate(bool _rotate_by_position);

    float GetRotation();
    void SetRotation(const float _rotation);

    sf::IntRect GetBoundingBox();

    sf::Texture& GetTexture();

    sf::Color GetColor();
    void SetColor(sf::Color _color);

    bool GetIsAnimating();
    void SetIsAnimating(bool _animating);

    shared_ptr<FrameAnimation> GetCurrentFrameAnimation();

    string GetCurrentAnimation();
    void SetCurrentAnimation(string _current_animation);

    void UpdateRotation();

    void AddAnimation(const string _key, const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length);
    void AddAnimation(const string _key, const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length, const string _next_animation);

    shared_ptr<FrameAnimation> GetAnimationByName(const string _key);

    void Move(const int _x, const int _y);

    void Update(sf::Time _elapsed_time);
    void Render(sf::RenderWindow& _window, const int _x_offset, const int _y_offset);

private:
    // Texture for the sprite
    sf::Texture texture;

    // True if animations are being played
    bool animating;

    // If set to any other color than white,
    // will colorize the sprite with that color.
    sf::Color color;

    // Position of the sprite on the screen
    sf::Vector2f position;
    sf::Vector2f last_position;

    // Map of all of the animations associated
    // with this sprite
    map<string, shared_ptr<FrameAnimation>> animations;

    // String containing the key of the current animations
    string current_animation;

    // If true, the sprite will rotate to align
    // itself with the angle difference between it's new
    // position and it's previous position.
    bool rotate_by_position;

    // How much to rotate the sprite when drawing
    float rotation;

    // Calculated center of sprite
    sf::Vector2f center;

    // Width and height of the sprite
    int width;
    int height;
};

#endif