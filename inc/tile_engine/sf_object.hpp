#ifndef SF_OBJECT_HPP
#define SF_OBJECT_HPP

#include <string>
    using std::string;

#include <SFML/Graphics.hpp>

namespace sftile
{
class Loader;

class Object
{
friend class Loader;
public:
    Object();

    Object(const Object& _copy);

    Object(Object&& _moveable);

    Object& operator=(const Object& _copy);

    string GetName();
    void SetName(string _name);

    string GetType();
    void SetType(string _type);

    sf::Vector2i GetPosition();
    void SetPosition(sf::Vector2i _position);

    sf::Vector2i GetDimensions();
    void SetDimensions(sf::Vector2i _dimensions);

    float GetRotation();
    void SetRotation(float _rotation);

    int GetGid();
    void SetGid(int _gid);

    bool IsVisible();
    void SetVisible(bool _visible);

    sf::IntRect GetBoundingBox();

private:
    // Arbitrary string for the name
    string name;

    // Arbitrary string for the type
    string type;

    //Vector of the position of the object
    sf::Vector2i position;

    // Vector of the dimensions of the object
    sf::Vector2i dimensions;

    // Angle to rotate the object to
    float rotation;

    // Optional GID of a tile to use for the object
    int gid;

    // If true, object will be rendered
    bool visible;
};

}

#endif