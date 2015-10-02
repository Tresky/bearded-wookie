#include <iostream>
    using std::cout;
    using std::cerr;
    using std::endl;

#include "../../inc/engine/sprite_animation.hpp"

SpriteAnimation::SpriteAnimation(sf::Texture _texture)
    : texture(_texture)
    , animating(true)
    , color(sf::Color::White)
    , position(0, 0)
    , last_position(0, 0)
    , animations()
    , current_animation("")
    , rotate_by_position(false)
    , rotation(0.f)
    , center(0, 0)
    , width(0)
    , height(0)
{
    //animations["test"] = std::make_shared();
}

SpriteAnimation::SpriteAnimation(const SpriteAnimation& _copy)
    : texture(_copy.texture)
    , animating(_copy.animating)
    , color(_copy.color)
    , position(_copy.position)
    , last_position(_copy.last_position)
    , animations(_copy.animations)
    , current_animation(_copy.current_animation)
    , rotate_by_position(_copy.rotate_by_position)
    , rotation(_copy.rotation)
    , center(_copy.center)
    , width(_copy.width)
    , height(_copy.height) 
{

}

SpriteAnimation::SpriteAnimation(SpriteAnimation&& _moveable)
    : texture(std::move(_moveable.texture))
    , animating(std::move(_moveable.animating))
    , color(std::move(_moveable.color))
    , position(std::move(_moveable.position))
    , last_position(std::move(_moveable.last_position))
    , animations(std::move(_moveable.animations))
    , current_animation(std::move(_moveable.current_animation))
    , rotate_by_position(std::move(_moveable.rotate_by_position))
    , rotation(std::move(_moveable.rotation))
    , center(std::move(_moveable.center))
    , width(std::move(_moveable.width))
    , height(std::move(_moveable.height)) 
{

}

SpriteAnimation& SpriteAnimation::operator=(const SpriteAnimation& _copy)
{
    if (this != &_copy)
    {
        SpriteAnimation temp(_copy);

        std::swap(texture, temp.texture);
        std::swap(animating, temp.animating);
        std::swap(color, temp.color);
        std::swap(position, temp.position);
        std::swap(last_position, temp.last_position);
        std::swap(animations, temp.animations);
        std::swap(current_animation, temp.current_animation);
        std::swap(rotate_by_position, temp.rotate_by_position);
        std::swap(rotation, temp.rotation);
        std::swap(center, temp.center);
        std::swap(width, temp.width);
        std::swap(height, temp.height);
    }
    return *this;
}

sf::Vector2f SpriteAnimation::GetPosition()
{
    return position;
}

void SpriteAnimation::SetPosition(sf::Vector2f _position)
{
    last_position = position;
    position = _position;
    UpdateRotation();
}

int SpriteAnimation::GetXPosition()
{
    return static_cast<int>(position.x);
}

void SpriteAnimation::SetXPosition(const int _x)
{
    last_position.x = position.x;
    position.x = _x;
    UpdateRotation();
}

int SpriteAnimation::GetYPosition()
{
    return static_cast<int>(position.y);
}

void SpriteAnimation::SetYPosition(const int _y)
{
    last_position.y = position.y;
    position.y = _y;
    UpdateRotation();
}

int SpriteAnimation::GetWidth()
{
    return width;
}

int SpriteAnimation::GetHeight()
{
    return height;
}

bool SpriteAnimation::GetAutoRotate()
{
    return rotate_by_position;
}

void SpriteAnimation::SetAutoRotate(bool _rotate_by_position)
{
    rotate_by_position = _rotate_by_position;
}

float SpriteAnimation::GetRotation()
{
    return rotation;
}

void SpriteAnimation::SetRotation(const float _rotation)
{
    rotation = _rotation;
}

sf::IntRect SpriteAnimation::GetBoundingBox()
{
    return sf::IntRect(position.x, position.y, width, height);
}

sf::Texture& SpriteAnimation::GetTexture()
{
    return texture;
}

sf::Color SpriteAnimation::GetColor()
{
    return color;
}

void SpriteAnimation::SetColor(sf::Color _color)
{
    color = _color;
}

bool SpriteAnimation::GetIsAnimating()
{
    return animating;
}

void SpriteAnimation::SetIsAnimating(bool _animating)
{
    animating = _animating;
}

shared_ptr<FrameAnimation> SpriteAnimation::GetCurrentFrameAnimation()
{
    if (current_animation.empty())
        cerr << "SpriteAnimation: No current animation specified." << endl;
    else if (animations.find(current_animation) == animations.end())
        cerr << "SpriteAnimation: Animation not found for specified key." << endl;
    else
        return animations[current_animation];
    return nullptr;
}

string SpriteAnimation::GetCurrentAnimation()
{
    return current_animation;
}

void SpriteAnimation::SetCurrentAnimation(string _current_animation)
{
    if (_current_animation.empty())
        cerr << "SpriteAnimation: Invalid key specified." << endl;
    else if (animations.find(_current_animation) == animations.end())
        cerr << "SpriteAnimation: Animation not found for specified key." << endl;
    else
    {
        current_animation = _current_animation;
        animations[current_animation]->SetCurrentFrame(0);
        animations[current_animation]->SetPlayCount(0);
    }
}

void SpriteAnimation::UpdateRotation()
{
    if (rotate_by_position)
        rotation = static_cast<float>(std::atan2(position.y - last_position.y, position.x - last_position.x));
}

void SpriteAnimation::AddAnimation(const string _key, const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length)
{
    if (_key.empty())
        cerr << "SpriteAnimation: Invalid key or animation name specified." << endl;
    else if (animations.find(_key) != animations.end())
        cerr << "SpriteAnimation: Animation with specified key already exists." << endl;
    else
    {   
        shared_ptr<FrameAnimation> temp(new FrameAnimation(_x, _y, _width, _height, _frame_count, _frame_length));
        animations[_key] = temp;

        width = _width;
        height = _height;
        center = sf::Vector2f(width / 2.f, height / 2.f);

        if (animations.size() == 1)
            current_animation = _key;
    }
    
}

void SpriteAnimation::AddAnimation(const string _key, const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length, const string _next_animation)
{
    if (_key.empty() || _next_animation.empty())
        cerr << "SpriteAnimation: Invalid key or animation name specified." << endl;
    else if (animations.find(_key) != animations.end())
        cerr << "SpriteAnimation: Animation with specified key already exists." << endl;
    else
    {
        animations[_key] = shared_ptr<FrameAnimation>(new FrameAnimation(_x, _y, _width, _height, _frame_count, _frame_length, _next_animation));
        width = _width;
        height = _height;
        center = sf::Vector2f(width / 2.f, height / 2.f);

        if (animations.size() == 1)
            current_animation = _key;
    }
}

shared_ptr<FrameAnimation> SpriteAnimation::GetAnimationByName(const string _key)
{
    if (_key.empty())
        cerr << "SpriteAnimation: Invalid key specified." << endl;
    else if (animations.find(_key) == animations.end())
        cerr << "SpriteAnimation: Animation with specified key doesn't exist." << endl;
    else
        return animations[_key];
    return nullptr;
}

void SpriteAnimation::Move(const int _x, const int _y)
{
    last_position = position;
    position = sf::Vector2f(position.x + _x, position.y + _y);
    UpdateRotation();
}

void SpriteAnimation::Update(sf::Time _elapsed_time)
{
    if (animating)
    {
        GetCurrentFrameAnimation()->Update(_elapsed_time);

        // Check to see if there is a follow-up animation.
        if (!GetCurrentFrameAnimation()->GetNextAnimation().empty())
        {
            // If this animation has completed a full cycle, load next
            if (GetCurrentFrameAnimation()->GetPlayCount() > 0)
                current_animation = GetCurrentFrameAnimation()->GetNextAnimation();
        }
    }
}

void SpriteAnimation::Render(sf::RenderWindow& _window, const int _x_offset, const int _y_offset)
{
    if (animating)
    {
        sf::Sprite sprite(texture, GetCurrentFrameAnimation()->GetRect());
        sprite.setPosition(position + center + sf::Vector2f(_x_offset, _y_offset));
        sprite.setColor(color);
        sprite.setRotation(rotation);
        _window.draw(sprite);
    }
}