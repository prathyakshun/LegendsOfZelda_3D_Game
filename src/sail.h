#include "main.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {}
    Sail(float x, float y, color_t color);
    glm::vec3 position;
    float rotation1;
    float upspeed;
    int inair;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag);
    double speed;
private:
    VAO *object;
};


#endif // SAIL_H
