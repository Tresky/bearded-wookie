#include <iostream>
    using std::cerr;
    using std::endl;

#include "../../inc/engine/mobile_sprite.hpp"

MobileSprite::MobileSprite(sf::Texture _texture)
    : sprite_animation(_texture)
    , path()
    , target(0, 0)
    , speed(1.f)
    , collision_buffer_x(0)
    , collision_buffer_y(0)
    , active(true)
    , moving_toward_target(false)
    , pathing(true)
    , collidable(true)
    , visible(true)
    , deactivate_end_path(false)
    , hide_end_path(false)
    , end_path_animation("")
{

}

MobileSprite::MobileSprite(const MobileSprite& _copy)
    : sprite_animation(_copy.sprite_animation)
    , path(_copy.path)
    , target(_copy.target)
    , speed(_copy.speed)
    , collision_buffer_x(_copy.collision_buffer_x)
    , collision_buffer_y(_copy.collision_buffer_y)
    , active(_copy.active)
    , moving_toward_target(_copy.moving_toward_target)
    , pathing(_copy.pathing)
    , collidable(_copy.collidable)
    , visible(_copy.visible)
    , deactivate_end_path(_copy.deactivate_end_path)
    , hide_end_path(_copy.hide_end_path)
    , end_path_animation(_copy.end_path_animation)
{

}

MobileSprite::MobileSprite(MobileSprite&& _moveable)
    : sprite_animation(std::move(_moveable.sprite_animation))
    , path(std::move(_moveable.path))
    , target(std::move(_moveable.target))
    , speed(std::move(_moveable.speed))
    , collision_buffer_x(std::move(_moveable.collision_buffer_x))
    , collision_buffer_y(std::move(_moveable.collision_buffer_y))
    , active(std::move(_moveable.active))
    , moving_toward_target(std::move(_moveable.moving_toward_target))
    , pathing(std::move(_moveable.pathing))
    , collidable(std::move(_moveable.collidable))
    , visible(std::move(_moveable.visible))
    , deactivate_end_path(std::move(_moveable.deactivate_end_path))
    , hide_end_path(std::move(_moveable.hide_end_path))
    , end_path_animation(std::move(_moveable.end_path_animation))
{

}

MobileSprite& MobileSprite::operator=(const MobileSprite& _copy)
{
    if (this != &_copy)
    {
        MobileSprite temp(_copy);

        std::swap(sprite_animation, temp.sprite_animation);
        std::swap(path, temp.path);
        std::swap(target, temp.target);
        std::swap(speed, temp.speed);
        std::swap(collision_buffer_x, temp.collision_buffer_x);
        std::swap(collision_buffer_y, temp.collision_buffer_y);
        std::swap(active, temp.active);
        std::swap(moving_toward_target, temp.moving_toward_target);
        std::swap(pathing, temp.pathing);
        std::swap(collidable, temp.collidable);
        std::swap(visible, temp.visible);
        std::swap(deactivate_end_path, temp.deactivate_end_path);
        std::swap(hide_end_path, temp.hide_end_path);
        std::swap(end_path_animation, temp.end_path_animation);
    }
    return *this;
}

SpriteAnimation& MobileSprite::GetSpriteAnimation()
{
    return sprite_animation;
}

sf::Vector2f MobileSprite::GetPosition()
{
    return sprite_animation.GetPosition();
}

void MobileSprite::SetPosition(sf::Vector2f _position)
{
    sprite_animation.SetPosition(_position);
}

sf::Vector2f MobileSprite::GetTarget()
{
    return target;
}

void MobileSprite::SetTarget(sf::Vector2f _target)
{
    target = _target;
}

int MobileSprite::GetHorizontalCollisionBuffer()
{
    return collision_buffer_x;
}

void MobileSprite::SetHorizontalCollisionBuffer(const int _buffer)
{
    collision_buffer_x = _buffer;
}

int MobileSprite::GetVerticalCollisionBuffer()
{
    return collision_buffer_y;
}

void MobileSprite::SetVerticalCollsionBuffer(const int _buffer)
{
    collision_buffer_y = _buffer;
}

bool MobileSprite::GetIsPathing()
{
    return pathing;
}

void MobileSprite::SetIsPathing(const bool _pathing)
{
    pathing = _pathing;
}

bool MobileSprite::GetDeactivateAfterPathing()
{
    return deactivate_end_path;
}

void MobileSprite::SetDeactivateAfterPathing(const bool _deactivate_end_path)
{
    deactivate_end_path = _deactivate_end_path;
}

bool MobileSprite::GetLoopPath()
{
    return loop_path;
}

void MobileSprite::SetLoopPath(const bool _loop_path)
{
    loop_path = _loop_path;
}

string MobileSprite::GetEndPathAnimation()
{
    return end_path_animation;
}

void MobileSprite::SetEndPathAnimation(const string _end_path_animation)
{
    end_path_animation = _end_path_animation;
}

bool MobileSprite::GetHideEndPath()
{
    return hide_end_path;
}

void MobileSprite::SetHideEndPath(const bool _hide_end_path)
{
    hide_end_path = _hide_end_path;
}

bool MobileSprite::GetIsVisible()
{
    return visible;
}

void MobileSprite::SetIsVisible(const bool _visible)
{
    visible = _visible;
}

float MobileSprite::GetSpeed()
{
    return speed;
}

void MobileSprite::SetSpeed(const float _speed)
{
    speed = _speed;
}

bool MobileSprite::GetIsActive()
{
    return active;
}

void MobileSprite::SetIsActive(const bool _active)
{
    active = _active;
}

bool MobileSprite::GetIsMoving()
{
    return moving_toward_target;
}

void MobileSprite::SetIsMoving(const bool _moving_towards_target)
{
    moving_toward_target = _moving_towards_target;
}

bool MobileSprite::GetIsCollibable()
{
    return collidable;
}

void MobileSprite::SetIsCollidable(const bool _collidable)
{
    collidable = _collidable;
}

sf::IntRect MobileSprite::GetBoundingBox()
{
    return sprite_animation.GetBoundingBox();
}

sf::IntRect MobileSprite::GetCollisionBox()
{
    return sf::IntRect(sprite_animation.GetBoundingBox().left + collision_buffer_x,
                       sprite_animation.GetBoundingBox().top + collision_buffer_y,
                       sprite_animation.GetWidth() - (2 * collision_buffer_x),
                       sprite_animation.GetHeight() - (2 * collision_buffer_y));
}

void MobileSprite::AddPathNode(const sf::Vector2f _node)
{
    path.push(_node);
}

void MobileSprite::AddPathNode(const int _x, const int _y)
{
    path.push(sf::Vector2f(_x, _y));
}

void MobileSprite::ClearPathNodes()
{
    while (!path.empty())
        path.pop();
}

void MobileSprite::Update(sf::Time _elapsed_time)
{
    if (active && moving_toward_target)
    {
        sf::Vector2f delta(target.x - sprite_animation.GetXPosition(), target.y - sprite_animation.GetYPosition());
        float delta_length = std::sqrt(delta.x * delta.x + delta.y * delta.y);

        if (delta_length > speed)
        {
            sf::Vector2f normalized(delta.x / delta_length, delta.y / delta_length);
            normalized *= speed;

            sf::Vector2f new_position(sprite_animation.GetXPosition() + normalized.x, sprite_animation.GetYPosition() + normalized.y);
            sprite_animation.SetPosition(new_position);
        }
        else
        {
            if (target == sprite_animation.GetPosition())
            {
                if (pathing)
                {
                    if (path.size() > 0)
                    {
                        target = path.front();
                        path.pop();
                        if (loop_path)
                            path.push(target);
                    }
                    else
                    {
                        if (!end_path_animation.empty() && !(sprite_animation.GetCurrentAnimation() == end_path_animation))
                            sprite_animation.SetCurrentAnimation(end_path_animation);
                        if (deactivate_end_path)
                            active = false;
                        if (hide_end_path)
                            visible = false;
                    }
                }
            }
            else
                sprite_animation.SetPosition(target);
        }
    }
    if (active)
        sprite_animation.Update(_elapsed_time);
}

void MobileSprite::Render(sf::RenderWindow& _window)
{
    if (visible)
        sprite_animation.Render(_window, 0, 0);
}