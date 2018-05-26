#include "tree.h"
#include "main.h"

Tree::Tree(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
 //   this->rotation = -15;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        0, 5, 0,
        0.5, 5, 0,
        0, 0,0,
        0, 0, 0,
        0.5, 5, 0,
        0.5, 0, 0,

        -1, 5, -0,
        1, 5, 0,
        -1, 7, 0,
        -1, 7, 0,
        1, 5, 0,
        1, 7, 0,


    };

    static const GLfloat color_buffer_data[] = {
//        0, 0, 0.545098,
//        0, 0, 0.501961,
//        0, 0, 0.501961,
//        0, 0.74902, 1,
//        0.117647, 0.564706, 1,
//        0.282353, 0.239216, 0.545098,
0.254902, 0.411765, 0.882353,
        0.254902, 0.411765, 0.882353,
        0.254902, 0.411765, 0.882353,
        0.254902, 0.411765, 0.882353,
        0.254902, 0.411765, 0.882353,
        0.254902, 0.411765, 0.882353,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+6*3, COLOR_GREEN, GL_FILL);
}

void Tree::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef6*
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Tree::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Tree::tick() {
}

