#include "main.h"
#ifndef MAN_H
#define MAN_H


class Man {
public:
    Man() {}
    Man(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int timer;
    int inboat;
    int inair;
    double upspeed;
    double rotation1;
    double rotation2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(int flag);
    double speed;
private:
    VAO *object[5];
};

#endif // MAN_H

