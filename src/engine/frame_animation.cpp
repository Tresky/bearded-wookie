#include <iostream>
    using std::cout;
    using std::endl;
#include <climits>

#include "../../inc/engine/frame_animation.hpp"

FrameAnimation::FrameAnimation(const sf::IntRect _initial_frame, const int _frame_count)
    : initial_frame(_initial_frame)
    , frame_count(_frame_count)
    , current_frame(0)
    , frame_length(0.2f)
    , frame_timer(0.0f)
    , play_count(0)
    , next_animation("")
    , frame_delta(1)
{

}

FrameAnimation::FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count)
    : initial_frame(_x, _y, _width, _height)
    , frame_count(_frame_count)
    , current_frame(0)
    , frame_length(0.2f)
    , frame_timer(0.0f)
    , play_count(0)
    , next_animation("")
    , frame_delta(1)
{

}

FrameAnimation::FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length)
    : initial_frame(_x, _y, _width, _height)
    , frame_count(_frame_count)
    , current_frame(0)
    , frame_length(_frame_length)
    , frame_timer(0.0f)
    , play_count(0)
    , next_animation("")
    , frame_delta(1)
{

}

FrameAnimation::FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length, const string _next_animation)
    : initial_frame(_x, _y, _width, _height)
    , frame_count(_frame_count)
    , current_frame(0)
    , frame_length(_frame_length)
    , frame_timer(0.0f)
    , play_count(0)
    , next_animation(_next_animation)
    , frame_delta(1)
{

}

FrameAnimation::FrameAnimation(const FrameAnimation& _copy)
    : initial_frame(_copy.initial_frame)
    , frame_count(_copy.frame_count)
    , current_frame(_copy.current_frame)
    , frame_length(_copy.frame_length)
    , frame_timer(_copy.frame_timer)
    , play_count(_copy.play_count)
    , next_animation(_copy.next_animation)
    , frame_delta(_copy.frame_delta)
{

}

FrameAnimation::FrameAnimation(FrameAnimation&& _moveable)
    : initial_frame(std::move(_moveable.initial_frame))
    , frame_count(std::move(_moveable.frame_count))
    , current_frame(std::move(_moveable.current_frame))
    , frame_length(std::move(_moveable.frame_length))
    , frame_timer(std::move(_moveable.frame_timer))
    , play_count(std::move(_moveable.play_count))
    , next_animation(std::move(_moveable.next_animation))
    , frame_delta(std::move(_moveable.frame_delta))
{

}

FrameAnimation& FrameAnimation::operator=(FrameAnimation& _copy)
{
    if (this != &_copy)
    {
        FrameAnimation temp(_copy);

        std::swap(initial_frame, temp.initial_frame);
        std::swap(frame_count, temp.frame_count);
        std::swap(current_frame, temp.current_frame);
        std::swap(frame_length, temp.frame_length);
        std::swap(frame_timer, temp.frame_timer);
        std::swap(play_count, temp.play_count);
        std::swap(next_animation, temp.next_animation);
        std::swap(frame_delta, temp.frame_delta);
    }
    return *this;
}

int FrameAnimation::GetFrameCount()
{
    return frame_count;
}

void FrameAnimation::SetFrameCount(const int _frame_count)
{
    frame_count = _frame_count;
}

int FrameAnimation::GetCurrentFrame()
{
    return current_frame;
}

void FrameAnimation::SetCurrentFrame(const int _current_frame)
{
    if (_current_frame > frame_count - 1)
        current_frame = frame_count - 1;
    else if (_current_frame < 0)
        current_frame = 0;
    else
        current_frame = _current_frame;
}

float FrameAnimation::GetFrameLength()
{
    return frame_length;
}

void FrameAnimation::SetFrameLength(const float _frame_length)
{
    frame_length = _frame_length;
}

int FrameAnimation::GetFrameWidth()
{
    return initial_frame.width;
}

int FrameAnimation::GetFrameHeight()
{
    return initial_frame.height;
}

sf::IntRect FrameAnimation::GetRect()
{
    return { initial_frame.left + (initial_frame.width * current_frame), initial_frame.top, initial_frame.width, initial_frame.height };
}

int FrameAnimation::GetPlayCount()
{
    return play_count;
}

void FrameAnimation::SetPlayCount(const int _play_count)
{
    play_count = _play_count;
}

string FrameAnimation::GetNextAnimation()
{
    return next_animation;
}

void FrameAnimation::SetNextAnimation(const string _next_animation)
{
    next_animation = _next_animation;
}

void FrameAnimation::Update(sf::Time _elapsed_time)
{
    frame_timer += _elapsed_time.asSeconds();

    if (frame_timer >= frame_length)
    {
        frame_timer = 0.0f;

        // The "ping-pong" animations effect is determined here by alternating
        // the frame_delta between (-1) and (+1).
        if (current_frame == frame_count - 1 || (current_frame == 0 && frame_delta < 0))
            frame_delta *= (-1);

        current_frame = (current_frame + frame_delta) % frame_count;
        if (current_frame == 0)
            play_count = std::min(play_count + 1, INT_MAX);
    }
}

FrameAnimation FrameAnimation::Clone()
{
    return { initial_frame.left, initial_frame.top, initial_frame.width, initial_frame.height, frame_count, frame_length, next_animation };
}