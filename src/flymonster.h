#include "main.h"
#ifndef FLYMONSTER_H
#define FLYMONSTER_H


class Flymonster {
public:
    Flymonster() {}
    Flymonster(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation1;
    float rotation2;
    double upspeed;
    double yacc;
    int inair;
    int life;
    double mx;
    double my;
    double mz;
    int shootcounter=0;
    int shot = 0;
    void draw(glm::mat4 VP);
    void Cannondraw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag);
    double speed;
private:
    VAO *object[5];
};

#endif // FLYMONSTER_H

