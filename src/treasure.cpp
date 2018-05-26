#include "treasure.h"
#include "main.h"

Treasure::Treasure(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
 //   this->rotation = -15;
    speed = 1;
    this->timer=500;

        GLfloat g_vertex_buffer_data[] = {
                    -2.0f,-2.0f,-2.0f,
                    -2.0f,-2.0f, 2.0f,
                    -2.0f, 2.0f, 2.0f,
                    2.0f, 2.0f,-2.0f,
                    -2.0f,-2.0f,-2.0f,
                    -2.0f, 2.0f,-2.0f,
                   2.0f,-2.0f, 2.0f,
                    -2.0f,-2.0f,-2.0f,
                    2.0f,-2.0f,-2.0f,
                    2.0f, 2.0f,-2.0f,
                    2.0f,-2.0f,-2.0f,
                    -2.0f,-2.0f,-2.0f,
                    -2.0f,-2.0f,-2.0f,
                    -2.0f, 2.0f, 2.0f,
                    -2.0f, 2.0f,-2.0f,
                    2.0f,-2.0f, 2.0f,
                    -2.0f,-2.0f, 2.0f,
                    -2.0f,-2.0f,-2.0f,
                    -2.0f, 2.0f, 2.0f,
                    -2.0f,-2.0f, 2.0f,
                    2.0f,-2.0f, 2.0f,
                    2.0f, 2.0f, 2.0f,
                    2.0f,-2.0f,-2.0f,
                    2.0f, 2.0f,-2.0f,
                    2.0f,-2.0f,-2.0f,
                    2.0f, 2.0f, 2.0f,
                    2.0f,-2.0f, 2.0f,
                    2.0f, 2.0f, 2.0f,
                    2.0f, 2.0f,-2.0f,
                    -2.0f, 2.0f,-2.0f,
                    2.0f, 2.0f, 2.0f,
                    -2.0f, 2.0f,-2.0f,
                    -2.0f, 2.0f, 2.0f,
                    2.0f, 2.0f, 2.0f,
                    -2.0f, 2.0f, 2.0f,
                    2.0f,-2.0f, 2.0f
        };

        static const GLfloat color_buffer_data[] = {
            1, 0.843137, 0,
             0.941176, 0.901961, 0.54902,
            1, 0.941176, 0.960784,
            1, 0.980392, 0.803922,
            0.933333 ,0.866667, 0.509804,
            1, 0.713725, 0.756863,
            1, 0.627451, 0.478431,
            1 ,0.647059 ,0,
            1 ,0.270588 ,0,
            0.803922 ,0.521569, 0.247059,
            0.980392, 0.501961, 0.447059,
            0.956863, 0.643137, 0.37647,
             0.556863, 0.556863, 0.219608,
            0.776471, 0.443137, 0.443137,
            0.823529, 0.705882, 0.54902,
            1 ,0.388235, 0.278431,
            0.960784, 0.870588, 0.701961,
            1, 1, 0,
            1, 0.843137, 0,
             0.941176, 0.901961, 0.54902,
            1, 0.941176, 0.960784,
            1, 0.980392, 0.803922,
            0.933333 ,0.866667, 0.509804,
            1, 0.713725, 0.756863,
            1, 0.627451, 0.478431,
            1 ,0.647059 ,0,
            1 ,0.270588 ,0,
            0.803922 ,0.521569, 0.247059,
            0.980392, 0.501961, 0.447059,
            0.956863, 0.643137, 0.37647,
             0.556863, 0.556863, 0.219608,
            0.776471, 0.443137, 0.443137,
            0.823529, 0.705882, 0.54902,
            1 ,0.388235, 0.278431,
            0.960784, 0.870588, 0.701961,
            1, 1, 0,
        };

    this->object = create3DObject(GL_TRIANGLES, 6*2*3, g_vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Treasure::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.3, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Treasure::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Treasure::tick() {
}

