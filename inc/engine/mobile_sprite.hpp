#ifndef MOBILE_SPRITE_H
#define MOBILE_SPRITE_H

#include <string>
    using std::string;
#include <queue>
    using std::queue;

#include "sprite_animation.hpp"

class MobileSprite
{
public:
    explicit MobileSprite(sf::Texture _texture);

    MobileSprite(const MobileSprite& _copy);

    MobileSprite(MobileSprite&& _moveable);

    MobileSprite& operator=(const MobileSprite& _copy);

    SpriteAnimation& GetSpriteAnimation();

    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f _position);

    sf::Vector2f GetTarget();
    void SetTarget(sf::Vector2f _target);

    int GetHorizontalCollisionBuffer();
    void SetHorizontalCollisionBuffer(const int _buffer);

    int GetVerticalCollisionBuffer();
    void SetVerticalCollsionBuffer(const int _buffer);

    bool GetIsPathing();
    void SetIsPathing(const bool _pathing);

    bool GetDeactivateAfterPathing();
    void SetDeactivateAfterPathing(const bool _deactivate_end_path);

    bool GetLoopPath();
    void SetLoopPath(const bool _loop_path);

    string GetEndPathAnimation();
    void SetEndPathAnimation(const string _end_path_animation);

    bool GetHideEndPath();
    void SetHideEndPath(const bool _hide_end_path);

    bool GetIsVisible();
    void SetIsVisible(const bool _visible);

    float GetSpeed();
    void SetSpeed(const float _speed);

    bool GetIsActive();
    void SetIsActive(const bool _active);

    bool GetIsMoving();
    void SetIsMoving(const bool _moving_towards_target);

    bool GetIsCollibable();
    void SetIsCollidable(const bool _collidable);

    sf::IntRect GetBoundingBox();

    sf::IntRect GetCollisionBox();

    void AddPathNode(sf::Vector2f _node);
    void AddPathNode(const int _x, const int _y);
    void ClearPathNodes();

    void Update(sf::Time _elapsed_time);
    void Render(sf::RenderWindow& _window);

private:
    // Animation object holds graphical and animation data
    SpriteAnimation sprite_animation;

    // Queuer of pathing coordinates for movement
    queue<sf::Vector2f> path;

    // Target position to move to
    sf::Vector2f target;

    // Speed of movement of sprite
    float speed;

    // Clipping range for determining bounding-box style
    // collisions. They return the bounding box of the sprite
    // trimmed by a horizontal and vertical offset to get a 
    // collision "cushion".
    int collision_buffer_x;
    int collision_buffer_y;

    // An active sprite will be drawn but not updated
    bool active;

    // If true, the sprite will move towards the target position.
    // If false, the sprite will not process any pathing data
    bool moving_toward_target;

    // Determines if the sprite will follow the path in it's path queue.
    // When the sprite reaching the current 'node', the next one will be
    // used for pathing.
    bool pathing;

    // If true, any path 'node' popped from the queue will be
    // enqueued to the back.
    bool loop_path;

    // If true, the sprite will collide with other objects.
    bool collidable;

    // If true, the sprite will be drawn to the screen.
    bool visible;

    // If true, the sprite will be deactivated when the path queue is empty.
    bool deactivate_end_path;

    // If true, the sprite will be hidden when the path queue is empty.
    bool hide_end_path;

    // The named animation to play when the path queue is empty.
    string end_path_animation;
};

#endif