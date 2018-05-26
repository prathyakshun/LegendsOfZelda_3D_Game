#include "main.h"
#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, color_t color);
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
    void draw(glm::mat4 VP);
    void Cannondraw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag);
    double speed;
private:
    VAO *object[4];
};

#endif // MONSTER_H

