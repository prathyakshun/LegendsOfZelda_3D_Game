#include "main.h"

#ifndef TREASURE_H
#define TREASURE_H


class Treasure {
public:
    Treasure() {}
    Treasure(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // TREASURE_H


