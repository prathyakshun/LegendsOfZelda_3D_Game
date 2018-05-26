
#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
 //   this->rotation = -15;
    speed = 1;

    GLfloat vertex_buffer_data[60*3*6];
    GLfloat vertex_buffer_data2[60*3*6];

//    static const GLfloat vertex_buffer_data[] = {
//        -300, 0, -300,
//        -300, 0, 300,
//        300, 0, 300,
//        300, 0, 300,
//        300, 0, -300,
//        -300, 0, -300
//    };

    int k = 0, i=0;
    for (i=0;i<1200;i+=20)
    {
        vertex_buffer_data[k++] = -600 + i; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = -300;
        vertex_buffer_data[k++] = -600 + i; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = 300;
        vertex_buffer_data[k++] = -600 + i + 30; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = 300;
        vertex_buffer_data[k++] = -600 + i + 30; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = 300;
        vertex_buffer_data[k++] = -600 + i; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = -300;
        vertex_buffer_data[k++] = -600 + i + 30; vertex_buffer_data[k++] = 0; vertex_buffer_data[k++] = 300;
    }

    k = 0;
    for (i=10;i<1200;i+=20)
    {
        vertex_buffer_data2[k++] = -600 + i; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = -300;
        vertex_buffer_data2[k++] = -600 + i; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = 300;
        vertex_buffer_data2[k++] = -600 + i + 30; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = 300;
        vertex_buffer_data2[k++] = -600 + i + 30; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = 300;
        vertex_buffer_data2[k++] = -600 + i; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = -300;
        vertex_buffer_data2[k++] = -600 + i + 30; vertex_buffer_data2[k++] = 0.01; vertex_buffer_data2[k++] = 300;
    }

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

    this->object[0] = create3DObject(GL_TRIANGLES, 60*6, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 60*6, vertex_buffer_data2, COLOR_WATER2, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform1f(Matrices.transparent_ability, 0.45);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    glDisable(GL_BLEND);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {
//    this->rotation += speed;
//     this->position.x -= speed;
//     this->position.y -= speed;
}

