#include "main.h"
#ifndef BOOST_H
#define BOOST_H


class Boost {
public:
    Boost() {}
    Boost(float x, float y,  float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BOOST_H

