#include "laser.h"
#include "main.h"

Laser::Laser(float x, float y, float z, float x1, float y1, float z1,color_t color) {
    this->position = glm::vec3(x, y, z);
 //   this->rotation = -15;
    speed = 1;
    int shotme = 0;

    const GLfloat vertex_buffer_data[] = {
        x,y,z,
        (x1), (y1), (z1),
        x+0.2, y+0.2, z+0.2,
        x+0.2, y+0.2, z+0.2,
        (x1)*1.0f, (y1)*1.0f, (z1)*1.0f,
        (x1+0.2)*1.0f, (y1+0.2)*1.0f, (z1+0.2)*1.0f,
    };
    printf("x is %lf y is %lf z is %lf\n", x, y, z);
    printf("x1 is %lf y1 is %lf z1 is %lf\n", x1, y1, z1);
    printf("diff is %lf, %lf %lf\n", x1-x, y1-y, z1-z);

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

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Laser::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(0, 0, 0));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Laser::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Laser::tick() {
}

