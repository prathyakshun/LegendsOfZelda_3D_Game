#include "cannonball.h"
#include "main.h"


Cannonball::Cannonball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);            // z -3 for starting from boatfront
    this->rotation1 = 0;
    this->rotation2 = 0;
    this->speed = 1;
    this->radius = 0.8;
    this->inair = 0;
    this->upspeed = 0;
    this->zspeed = 0.8;

    double pi = 22.0/7;                                     // pi in radians
    double in_angle = (pi/180.0f);                         // Angle of rotation in radians
    printf("in_angle is %lf\n",in_angle);
    GLfloat g_vertex_buffer_data[2*90*360*3*3];                // Array containing the vertices of each triangle
    GLfloat g_vertex_buffer1[] = {-1*this->radius,0.0f};               // Initital x,y point to be rotated later on
    int k=0,i=0, j=0;
    for (i=0;i<90;i++)
    {
        for (j=0;j<360;j++)
        {
            g_vertex_buffer_data[k++] = .3*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*cos(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = .3*sin(glm::radians(i));  g_vertex_buffer_data[k++] = 0;
            g_vertex_buffer_data[k++] = .3*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*cos(i*M_PI/180.0f);
        }
    }
    for (i=0;i<90;i++)
    {
        for (j=0;j<360;j++)
        {
            g_vertex_buffer_data[k++] = .3*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = -1*.3*cos(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = .3*sin(glm::radians(i));  g_vertex_buffer_data[k++] = 0;
            g_vertex_buffer_data[k++] = .3*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = .3*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
            g_vertex_buffer_data[k++] = -1*.3*cos(i*M_PI/180.0f);
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 2*90*360*3, g_vertex_buffer_data, color);
}

void Cannonball::draw(glm::mat4 VP) {
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

void Cannonball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannonball::tick(int flag, int rev, int rev2) {          // rev takes care of rotation directions

    /* Cannonball movement */
    if (flag == 0)
    {
        this->position.y += this->upspeed;
        this->upspeed -= 0.05;
        this->position.z += rev2*rev*this->zspeed*cos(glm::radians(this->rotation1));
        this->position.x -= (sin(glm::radians(this->rotation1)));
    }
}
