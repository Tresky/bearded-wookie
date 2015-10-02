#ifndef FRAME_ANIMATION_HPP
#define FRAME_ANIMATION_HPP

#include <string>
    using std::string;

#include <SFML/Graphics.hpp>

/*
 * @class FrameAnimation
 * @desc The FrameAnimation class represents a single
 *   animation to be assigned to a sprite. This could
 *   be a "walk-left" animations or something of the
 *   sort. There are loads of different settings that
 *   can be applied to this class in order to have 
 *   different effects on the animation.
 */
class FrameAnimation
{
public:
    /*
     * Constructor
     *
     * @param[in] _initial_frame sf::Rect representing the first frame of the animation
     * @param[in] _frame_count Integer specifying the number of frames in the animation
     */
    FrameAnimation(const sf::IntRect _initial_frame, const int _frame_count);

    /*
     * Constructor
     *
     * @param[in] _x Integer specifying the left-most pixel of the first frame's sf::Rect
     * @param[in] _y Integer specifying the top-most pixel of the first frame's sf::Rect
     * @param[in] _width Integer specifying how wide each frame of the animation is
     * @param[in] _height Integer specifying how tall each frame of the animation is
     * @param[in] _frame_count Integer specifying the number of frames in the animation
     */
    FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count);

    /*
     * Constructor
     *
     * @param[in] _x Integer specifying the left-most pixel of the first frame's sf::Rect
     * @param[in] _y Integer specifying the top-most pixel of the first frame's sf::Rect
     * @param[in] _width Integer specifying how wide each frame of the animation is
     * @param[in] _height Integer specifying how tall each frame of the animation is
     * @param[in] _frame_count Integer specifying the number of frames in the animation
     * @param[in] _frame_length Amount of time in seconds that each frame is displayed
     */
    FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length);

    /*
     * Constructor
     *
     * @param[in] _x Integer specifying the left-most pixel of the first frame's sf::Rect
     * @param[in] _y Integer specifying the top-most pixel of the first frame's sf::Rect
     * @param[in] _width Integer specifying how wide each frame of the animation is
     * @param[in] _height Integer specifying how tall each frame of the animation is
     * @param[in] _frame_count Integer specifying the number of frames in the animation
     * @param[in] _frame_length Amount of time in seconds that each frame is displayed
     * @param[in] _next_animation String containing the title of the animation to play next
     */
    FrameAnimation(const int _x, const int _y, const int _width, const int _height, const int _frame_count, const float _frame_length, const string _next_animation);

    // Copy constructor
    FrameAnimation(const FrameAnimation& _copy);

    // Move constructor
    FrameAnimation(FrameAnimation&& _moveable);

    // Copy assignment operator
    FrameAnimation& operator=(FrameAnimation& _copy);

    /*
     * Returns the number of frames in the animation as an integer.
     *
     * @retval Integer of the number of frames in the animation
     */
    int GetFrameCount();

    /*
     * Sets the number of frames in the animations.
     *
     * @param[in] _frame_count Number of frames as an integer
     */
    void SetFrameCount(const int _frame_count);

    /*
     * Returns the current frame as an integer.
     *
     * @retval Integer index of the current frame showing
     */
    int GetCurrentFrame();

    /*
     * Sets the current frame of the animation.
     *
     * @param[in] _current_frame Current frame to set as an integer
     */
    void SetCurrentFrame(const int _current_frame);

    /*
     * Returns the current length of each frame in seconds.
     *
     * @retval Float representing the seconds each frame in shown
     */
    float GetFrameLength();

    /*
     * Sets the frame length for each frame in seconds.
     *
     * @param[in] _frame_length Seconds to display each frame
     */
    void SetFrameLength(const float _frame_length);

    /*
     * Returns the width of each frame.
     *
     * @retval Integer representing the width of each frame in pixels
     */
    int GetFrameWidth();

    /*
     * Returns the height of each frame.
     *
     * @retval Integer representing the height of each frame in pixels
     */
    int GetFrameHeight();

    /*
     * Returns the current sf::IntRect of the current frame.
     *
     * @retval sf::IntRect of the current frame in the animation
     */
    sf::IntRect GetRect();

    /*
     * Returns the number of times the animation has been played.
     *
     * @retval Integer representing the number of time played
     */
    int GetPlayCount();

    /*
     * Sets the amount of times that the animation has been played.
     *
     *
     */
    void SetPlayCount(const int _play_count);

    /*
     * Returns the title of the next animation to play.
     *
     * @retval String with the title of the next animation
     */
    string GetNextAnimation();

    /*
     * Sets the title of the next animation to play.
     *
     * @param[in] _next_animations String with the title of the next animation
     */
    void SetNextAnimation(const string _next_animation);

    /*
     * Updates the current state of the animation by swapping frames.
     *
     * @param[in] _elapsed_time Current frame time; used to time frames
     */
    void Update(sf::Time _elapsed_time);

    /*
     * Returns a FrameAnimation with the same settings.
     *
     * @retval FrameAnimation with the same settings as (this)
     */
    FrameAnimation Clone();

private:
    // Initial frame of animation
    // All of frames are calculated off of this one
    sf::IntRect initial_frame;

    // Number of frames in animation
    int frame_count;

    // Frame currently being displayed
    // This is from 0 to frame_count - 1
    int current_frame;

    // Amount of time to display each frame
    float frame_length;

    // Amount of time passed since we last animated
    float frame_timer;

    // Number of times this animation has been played
    int play_count;

    // Animation that should be played after this one
    string next_animation;

    // Represents the direction to change the animation
    // (+1) means add one to the current_frame
    // (-1) means sub one from the frame current_frame
    // This allows us to alternate and have a "ping-pong"
    // effect when animating.
    // 
    // Frame Index:
    // 1 - 2 - 3 - 2 - 1...
    int frame_delta;
};

#endif