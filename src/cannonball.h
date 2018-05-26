#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation1;
    double rotation2;
    float upspeed;
    double zspeed;
    int inair;
    double radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag, int rev, int rev2);
    double speed;
private:
    VAO *object;
};

#endif // CANNONBALL_H

