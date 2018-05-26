#include "health.h"
#include "main.h"


Health::Health(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;
    this->inair = 0;
    this->upspeed = 0;

    static const GLfloat vertex_buffer_data[] = {
        0, 0.2, 0,
        -0.2, 0.2,0,
        0, 0, 0,

    };

    this->object = create3DObject(GL_TRIANGLES, 1*3*3, vertex_buffer_data, color);
}

void Health::draw(glm::mat4 VP) {
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

void Health::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, 0);
}

void Health::tick(int flag) {
}

