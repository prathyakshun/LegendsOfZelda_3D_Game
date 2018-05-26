#include "cannon.h"
#include "main.h"


Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;

    GLfloat vertex_buffer_cannon[3*3*100*360];
    double pi = 22.0/7;                                     // pi in radians
    double in_angle = (pi/180.0f);                          // 1 degree angle of rotation in radians
    printf("in_angle is %lf\n",in_angle);
    int i=0, j=0, k=0;
    double cx = 0, cy = 0, cz = 0;
    GLfloat g_vertex_buffer1[] = {cx-0.1, cy, cz};               // Initital x,y point to be rotated later on
    for (j=0;j<100;j++)
    {
        for (i=0;i<360;i++)
        {
            vertex_buffer_cannon[k] = cx; k++;
            vertex_buffer_cannon[k] = cy; k++;
            vertex_buffer_cannon[k] = cz; k++;
            vertex_buffer_cannon[k] = g_vertex_buffer1[0];  k++;
            vertex_buffer_cannon[k] = g_vertex_buffer1[1];  k++;
            vertex_buffer_cannon[k] = g_vertex_buffer1[2];  k++;
            vertex_buffer_cannon[k] = g_vertex_buffer1[0]*cos(in_angle) - g_vertex_buffer1[1]*sin(in_angle);    k++;
            vertex_buffer_cannon[k] = g_vertex_buffer1[0]*sin(in_angle) + g_vertex_buffer1[1]*cos(in_angle);    k++;
            vertex_buffer_cannon[k] = cz; k++;
            double tmpx = g_vertex_buffer1[0], tmpy = g_vertex_buffer1[1];
            g_vertex_buffer1[0] = tmpx*cos(in_angle) - tmpy*sin(in_angle);
            g_vertex_buffer1[1] = tmpx*sin(in_angle) + tmpy*cos(in_angle);
        }
        /*cy+=0.1;*/    cz-=0.01;
        g_vertex_buffer1[0] = cx-0.1;   g_vertex_buffer1[1] = cy; g_vertex_buffer1[2]=cz;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*100*3, vertex_buffer_cannon, color);
}

void Cannon::draw(glm::mat4 VP) {
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

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick(int flag) {

//    this->rotation += speed;
//     this->position.x -= speed;
//     this->position.y -= speed;
}

