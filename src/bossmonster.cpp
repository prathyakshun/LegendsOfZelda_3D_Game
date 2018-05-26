#include "bossmonster.h"
#include "main.h"


Bossmonster::Bossmonster(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;
    this->radius = 2;
    this->inair = 0;
    this->upspeed = 0;
    this->zspeed = 0.8;
    this->life = 2;
    this->mx = 0;
    this->my = 0;
    this->mz = 0;
    this->touched = 0;
    static const GLfloat g_vertex_buffer_data1[] = {
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

        -0.2, 3, 0,
        0.2, 3, 0,
        0.2, 2, 0,
        0.2,  2, 0,
        -0.2, 3, 0,
        0.2, 3, 0,

        -0.8f,3,-0.8f,
        -0.8f,3, 0.8f,
        -0.8f, 4.6f, 0.8f,
        0.8f, 4.6f,-0.8f,
        -0.8f,3,-0.8f,
        -0.8f, 4.6f,-0.8f,
       0.8f,3, 0.8f,
        -0.8f,3,-0.8f,
        0.8f,3,-0.8f,
        0.8f, 4.6f,-0.8f,
        0.8f,3,-0.8f,
        -0.8f,3,-0.8f,
        -0.8f,3,-0.8f,
        -0.8f, 4.6f, 0.8f,
        -0.8f, 4.6f,-0.8f,
        0.8f,3, 0.8f,
        -0.8f,3, 0.8f,
        -0.8f,3,-0.8f,
        -0.8f, 4.6f, 0.8f,
        -0.8f,3, 0.8f,
        0.8f,3, 0.8f,
        0.8f, 4.6f, 0.8f,
        0.8f,3,-0.8f,
        0.8f, 4.6f,-0.8f,
        0.8f,3,-0.8f,
        0.8f, 4.6f, 0.8f,
        0.8f,3, 0.8f,
        0.8f, 4.6f, 0.8f,
        0.8f, 4.6f,-0.8f,
        -0.8f, 4.6f,-0.8f,
        0.8f, 4.6f, 0.8f,
        -0.8f, 4.6f,-0.8f,
        -0.8f, 4.6f, 0.8f,
        0.8f, 4.6f, 0.8f,
        -0.8f, 4.6f, 0.8f,
        0.8f,3, 0.8f,

        -0.4, 4.6, 0.4,
        0 , 5.3, 0,
        0.4, 4.6, 0.4,
        -0.4, 4.6, 0.4,
        -0.4, 4.6, -0.4,
        0, 5.3, 0,
        -0.4, 4.6, -0.4,
        0.4, 4.6, -0.4,
        0, 5.3, 0,
        0.4, 4.6, -0.4,
        0.4, 4.6, 0.4,
        0, 5.3, 0,
    };
    GLfloat g_vertex_buffer_data[30*90*3*3];                // Array containing the vertices of each triangle
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
//    for (i=0;i<90;i++)
//    {
//        for (j=0;j<360;j+=12)
//        {
//            g_vertex_buffer_data[k++] = this->radius*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
//            g_vertex_buffer_data[k++] = this->radius*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
//            g_vertex_buffer_data[k++] = -1*this->radius*cos(i*M_PI/180.0f);
//            g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = this->radius*sin(glm::radians(i));  g_vertex_buffer_data[k++] = 0;
//            g_vertex_buffer_data[k++] = this->radius*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
//            g_vertex_buffer_data[k++] = this->radius*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
//            g_vertex_buffer_data[k++] = this->radius*.3*cos(i*M_PI/180.0f);
//        }
//    }

    this->object[0] = create3DObject(GL_TRIANGLES, 6*2*3, g_vertex_buffer_data1, COLOR_GREEN);
    this->object[1] = create3DObject(GL_TRIANGLES, 30*90*3, g_vertex_buffer_data, color);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, g_vertex_buffer_data1+6*2*3*3, COLOR_YELLOW);
    this->object[3] = create3DObject(GL_TRIANGLES, 6*2*3, g_vertex_buffer_data1+6*2*3*3+2*3*3, COLOR_ORANGE);
    this->object[4] = create3DObject(GL_TRIANGLES, 4*3, g_vertex_buffer_data1+6*2*3*3+2*3*3+6*2*3*3, COLOR_RED);
}

void Bossmonster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);

}

void Bossmonster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bossmonster::tick(int flag, int rev) {
}

