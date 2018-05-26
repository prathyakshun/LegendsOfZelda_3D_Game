#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation1;
    double upspeed;
    double inair;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag);
    double speed;
private:
    VAO *object;
};

#endif // CANNON_H
