#include "monster.h"
#include "main.h"


Monster::Monster(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;
    this->inair = 0;
    this->upspeed = 0;
    this -> mx = 0;
    this -> my = 0;
    this -> mz = 0;

    static const GLfloat vertex_buffer_data[] = {
        -0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f, 0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f,
       0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,

        -0.2, 1, 0,
        0.2, 1, 0,
        0.2, 0, 0,
        0.2,  0, 0,
        -0.2, 1, 0,
        0.2, 1, 0,

        -0.4f,1,-0.4f,
        -0.4f,1, 0.4f,
        -0.4f, 1.8f, 0.4f,
        0.4f, 1.8f,-0.4f,
        -0.4f,1,-0.4f,
        -0.4f, 1.8f,-0.4f,
       0.4f,1, 0.4f,
        -0.4f,1,-0.4f,
        0.4f,1,-0.4f,
        0.4f, 1.8f,-0.4f,
        0.4f,1,-0.4f,
        -0.4f,1,-0.4f,
        -0.4f,1,-0.4f,
        -0.4f, 1.8f, 0.4f,
        -0.4f, 1.8f,-0.4f,
        0.4f,1, 0.4f,
        -0.4f,1, 0.4f,
        -0.4f,1,-0.4f,
        -0.4f, 1.8f, 0.4f,
        -0.4f,1, 0.4f,
        0.4f,1, 0.4f,
        0.4f, 1.8f, 0.4f,
        0.4f,1,-0.4f,
        0.4f, 1.8f,-0.4f,
        0.4f,1,-0.4f,
        0.4f, 1.8f, 0.4f,
        0.4f,1, 0.4f,
        0.4f, 1.8f, 0.4f,
        0.4f, 1.8f,-0.4f,
        -0.4f, 1.8f,-0.4f,
        0.4f, 1.8f, 0.4f,
        -0.4f, 1.8f,-0.4f,
        -0.4f, 1.8f, 0.4f,
        0.4f, 1.8f, 0.4f,
        -0.4f, 1.8f, 0.4f,
        0.4f,1, 0.4f,

        -0.4, 1.8, 0.4,
        0 , 2.5, 0,
        0.4, 1.8, 0.4,
        -0.4, 1.8, 0.4,
        -0.4, 1.8, -0.4,
        0, 2.5, 0,
        -0.4, 1.8, -0.4,
        0.4, 1.8, -0.4,
        0, 2.5, 0,
        0.4, 1.8, -0.4,
        0.4, 1.8, 0.4,
        0, 2.5, 0,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data, COLOR_PURPLE);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+6*2*3*3, COLOR_YELLOW);
    this->object[2] = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data+6*2*3*3+2*3*3, COLOR_DARK_PURPLE);
    this->object[3] = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data+6*2*3*3+2*3*3+6*2*3*3, COLOR_ORANGE);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick(int flag) {
}

