#include "rock.h"
#include "main.h"


Rock::Rock(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;
    this->radius = 2;
    this->inair = 0;
    this->upspeed = 0;
    this->zspeed = 0.8;

    GLfloat g_vertex_buffer_data[2*30*90*3*3];                // Array containing the vertices of each triangle
    int k=0,i=0, j=0;
    for (i=0;i<90;i++)
    {
        for (j=0;j<360;j+=12)
        {
            g_vertex_buffer_data[k++] = this->radius*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*cos(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = this->radius*sin(glm::radians(i));  g_vertex_buffer_data[k++] = 0;
            g_vertex_buffer_data[k++] = this->radius*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*cos(i*M_PI/180.0f);
        }
    }
    for (i=0;i<90;i++)
    {
        for (j=0;j<360;j+=12)
        {
            g_vertex_buffer_data[k++] = this->radius*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = -1*this->radius*cos(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = this->radius*sin(glm::radians(i));  g_vertex_buffer_data[k++] = 0;
            g_vertex_buffer_data[k++] = this->radius*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = this->radius*.3*cos(i*M_PI/180.0f);
        }
    }
//    GLfloat g_vertex_buffer_data[] = {
//                -0.6f,-0.6f,-0.6f,
//                -0.6f,-0.6f, 0.6f,
//                -0.6f, 0.6f, 0.6f,
//                0.6f, 0.6f,-0.6f,
//                -0.6f,-0.6f,-0.6f,
//                -0.6f, 0.6f,-0.6f,
//               0.6f,-0.6f, 0.6f,
//                -0.6f,-0.6f,-0.6f,
//                0.6f,-0.6f,-0.6f,
//                0.6f, 0.6f,-0.6f,
//                0.6f,-0.6f,-0.6f,
//                -0.6f,-0.6f,-0.6f,
//                -0.6f,-0.6f,-0.6f,
//                -0.6f, 0.6f, 0.6f,
//                -0.6f, 0.6f,-0.6f,
//                0.6f,-0.6f, 0.6f,
//                -0.6f,-0.6f, 0.6f,
//                -0.6f,-0.6f,-0.6f,
//                -0.6f, 0.6f, 0.6f,
//                -0.6f,-0.6f, 0.6f,
//                0.6f,-0.6f, 0.6f,
//                0.6f, 0.6f, 0.6f,
//                0.6f,-0.6f,-0.6f,
//                0.6f, 0.6f,-0.6f,
//                0.6f,-0.6f,-0.6f,
//                0.6f, 0.6f, 0.6f,
//                0.6f,-0.6f, 0.6f,
//                0.6f, 0.6f, 0.6f,
//                0.6f, 0.6f,-0.6f,
//                -0.6f, 0.6f,-0.6f,
//                0.6f, 0.6f, 0.6f,
//                -0.6f, 0.6f,-0.6f,
//                -0.6f, 0.6f, 0.6f,
//                0.6f, 0.6f, 0.6f,
//                -0.6f, 0.6f, 0.6f,
//                0.6f,-0.6f, 0.6f
//    };

    this->object = create3DObject(GL_TRIANGLES, 30*90*2*3, g_vertex_buffer_data, color);
}

void Rock::draw(glm::mat4 VP) {
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

void Rock::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rock::tick(int flag, int rev) {
}

