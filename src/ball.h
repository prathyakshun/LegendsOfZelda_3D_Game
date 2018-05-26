#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation1;
    float rotation2;
    float rotation3;
    double upspeed;
    double yacc;
    int inair;
    int life;
    int score;
    int lock;
    int level;
    double speed;
    void draw(glm::mat4 VP);
    void Cannondraw(glm::mat4 VP);
    void Splashdraw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag);
private:
    VAO *objectarr[7];
};

#endif // BALL_H
