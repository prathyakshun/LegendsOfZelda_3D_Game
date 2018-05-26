#include "sail.h"
#include "main.h"


Sail::Sail(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, -4);
    this->rotation1 = 0;
    speed = 1;
    this->inair = 0;
    this->upspeed = 0;

    static const GLfloat vertex_buffer_data[] = {
        0.1, 2.5, 0,
        1.2, 2.5, -1,
        0.3, 0.5, -1,
        0.3, 0.5, -1,
        0.1, -0.5, 0,
        0.1, 2.5, 0,

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sail::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sail::tick(int flag) {
    printf("position.y is %lf\n", this->position.y);
    if (this->position.y + this->upspeed <= -1)            // -1.8 is the level of the gorund
    {
        this->upspeed = 0;
        this->inair = 0;
    }
    else    this->inair = 1;
    if (flag == 0)
    {
        this->position.y += this->upspeed;
        this->upspeed -= 0.05;
    }
//    this->rotation += speed;
//     this->position.x -= speed;
//     this->position.y -= speed;
}

