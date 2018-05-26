#include "main.h"
#ifndef BOSSMONSTER_H
#define BOSSMONSTER_H


class Bossmonster {
public:
    Bossmonster() {}
    Bossmonster(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation1;
    float upspeed;
    double zspeed;
    int life;
    double mx;
    double my;
    int touched;
    double mz;
    int inair;
    double radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag, int rev);
    double speed;
private:
    VAO *object[5];
};

#endif // BOSSMONSTER_H


