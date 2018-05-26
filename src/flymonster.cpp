#include "flymonster.h"
#include "main.h"

Flymonster::Flymonster(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation1 = 0;
    speed = 1;
    this->inair = 0;
    this->upspeed = 0;
    this -> mx = 0;
    this -> my = 0;
    this -> mz = 0;
    this->shootcounter=0;
    this->shot = 0;

    static const GLfloat vertex_buffer_data[] = {
        -0.6f,0.6f,-0.6+2.0f,
        -0.6f,0.6f, 0.6+2.0f,
        -0.6f, 0.2f, 0.6f+2.0,
        0.6f, 0.2f,-0.6f+2.0,
        -0.6f,0.6f,-0.6f+2.0,
        -0.6f, 0.2f,-0.6+2.0f,
       0.6f,0.6f, 0.6f+2.0,
        -0.6f,0.6f,-0.6+2.0f,
        0.6f,0.6f,-0.6+2.0f,
        0.6f, 0.2f,-0.6+2.0f,
        0.6f,0.6f,-0.6+2.0f,
        -0.6f,0.6f,-0.6+2.0f,
        -0.6f,0.6f,-0.6+2.0f,
        -0.6f, 0.2f, 0.6+2.0f,
        -0.6f, 0.2f,-0.6+2.0f,
        0.6f,0.6f, 0.6+2.0f,
        -0.6f,0.6f, 0.6+2.0f,
        -0.6f,0.6f,-0.6+2.0f,
        -0.6f, 0.2f, 0.6+2.0f,
        -0.6f,0.6f, 0.6+2.0f,
        0.6f,0.6f, 0.6f+2.0,
        0.6f, 0.2f, 0.6+2.0f,
        0.6f,0.6f,-0.6+2.0f,
        0.6f, 0.2f,-0.6+2.0f,
        0.6f,0.6f,-0.6+2.0f,
        0.6f, 0.2f, 0.6+2.0f,
        0.6f,0.6f, 0.6+2.0f,
        0.6f, 0.2f, 0.6+2.0f,
        0.6f, 0.2f,-0.6+2.0f,
        -0.6f, 0.2f,-0.6+2.0f,
        0.6f, 0.2f, 0.6+2.0f,
        -0.6f, 0.2f,-0.6+2.0f,
        -0.6f, 0.2f, 0.6+2.0f,
        0.6f, 0.2f, 0.6+2.0f,
        -0.6f, 0.2f, 0.6+2.0f,
        0.6f,0.6f, 0.6+2.0f,

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

        -0.4, 0.6, 0.4+2.0,
        0 , 1.3, 0+2.0,
        0.4, 0.6, 0.4+2.0,
        -0.4, 0.6, 0.4+2.0,
        -0.4, 0.6, -0.4+2.0,
        0, 1.3, 0+2.0,
        -0.4, 0.6, -0.4+2.0,
        0.4, 1.3, -0.4+2.0,
        0, 1.3, 0+2.0,
        0.4, 0.6, -0.4+2.0,
        0.4, 0.6, 0.4+2.0,
        0, 0.6, 0+2.0,
    };

    GLfloat vertex_buffer_cannon[3*3*100*360];
    double pi = 22.0/7;                                     // pi in radians
    double in_angle = (pi/180.0f);                          // 1 degree angle of rotation in radians
    printf("in_angle is %lf\n",in_angle);
    int i=0, j=0, k=0;
    double cx = 0, cy = 0, cz = 2;
    GLfloat g_vertex_buffer1[] = {cx-0.3, cy, cz};               // Initital x,y point to be rotated later on
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
        /*cy+=0.1;*/    cz-=0.02;
        g_vertex_buffer1[0] = cx-0.1;   g_vertex_buffer1[1] = cy; g_vertex_buffer1[2]=cz;
    }

    this->object[0] = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data, COLOR_LASER_GRAY);
//    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+6*2*3*3, COLOR_YELLOW);
//    this->object[2] = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data+6*2*3*3+2*3*3, COLOR_DARK_PURPLE);
    this->object[3] = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data+6*2*3*3+2*3*3+6*2*3*3, COLOR_LASER_TOP);
    this->object[4] = create3DObject(GL_TRIANGLES, 360*100*3, vertex_buffer_cannon, COLOR_BLACK, GL_FILL);
}

void Flymonster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
//    draw3DObject(this->object[1]);
//    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
}

void Flymonster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Flymonster::tick(int flag) {
}

