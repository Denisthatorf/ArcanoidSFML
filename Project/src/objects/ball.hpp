#include "defines.hpp"

#include "core/vector2d.hpp"

class Ball
{
private:
    static Sprite* _sprite;
    static int _radius;
    static float speed;

    vector2d<float> _position;
    vector2d<float> _velocity;
    
public:
    static void initSprites(float k);
    static void destroySprites();

    Ball();

    void draw();
    void update(unsigned int delta_time);
    void push(vector2d<float> vector);

    void setDirection(vector2d<float> vector);
    void setVelocity(vector2d<float> vector);
    void setPosition(vector2d<float> vector);
    void setCenterPosition(vector2d<float> vector);

    //vector2d<float> getDirection();
    vector2d<float> getPosition() const;
    vector2d<float> getCenterPosition() const;
    vector2d<float> getVelocity() const;
    int getRadius() const;
};
