#ifndef LASER_H
#define LASER_H

#include "main.h"

class Laser {
public:
    Laser() {}
    Laser(float x, float y, float z, float x1, float y1, float z1, color_t color);
    glm::vec3 position;
    float rotation;
    int shotme;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // LASER_H
