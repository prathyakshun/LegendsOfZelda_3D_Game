#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, -4);
    this->rotation1 = 0;
    this->rotation2 = 40;
    this->rotation3 = -5;
    this->lock = 0;
    this->yacc = -0.02;
    this -> speed = 1;
    this->upspeed = 0;
    this->inair = 0;
    this->life = 10;
    this->score = 0;
    this -> level = 1;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        // Front part
        -1, 0.5, 2,
        -0.5, -0.5, 2,
        0, 0.5, 3,
        0, 0.5, 3,
        0, -0.5, 3,
        -0.5, -0.5,2,

        1, 0.5, 2,
        0.5, -0.5, 2,
        0, 0.5, 3,
        0, 0.5, 3,
        0, -0.5, 3,
        0.5,-0.5,2,


        // Behind part
        -1, 0.5, -2,
        -0.5, -0.5, -2,
        0, 0.5, -3,
        0, 0.5, -3,
        0, -0.5, -3,
        -0.5, -0.5,-2,

        1, 0.5, -2,
        0.5, -0.5, -2,
        0, 0.5, -3,
        0, 0.5, -3,
        0, -0.5, -3,
        0.5,-0.5,-2,

        // Left part
        -1, 0.5, 2,
        -0.5, -0.5, 2,
        -1, 0.5, -2,
        -1, 0.5, -2,
        -0.5, -0.5, 2,
        -0.5, -0.5, -2,

        // Right part
        1, 0.5, 2,
        0.5, -0.5, 2,
        1, 0.5, -2,
        1, 0.5, -2,
        0.5, -0.5, 2,
        0.5, -0.5, -2,

        // Bottom part
        -0.5, -0.5, 2,
        0.5, -0.5, 2,
        -0.5, -0.5, -2,
        -0.5, -0.5, -2,
        0.5, -0.5, -2,
        0.5, -0.5, 2,

        -0.5, -0.5, 2,
        0.5, -0.5, 2,
        0, -0.5, 3,

        -0.5, -0.5, -2,
        0.5, -0.5, -2,
        0, -0.5, -3,

        // Sail pole part
        0, 2.5, 0,
        0.1, 2.5, 0,
        0, -0.5, 0,
        0.1, 2.5, 0,
        0.1, -0.5, 0,
        0, -0.5, 0,

        /* Splash */
        -1, 0, 6,
        -0.3,0, 6,
        -1,0, -2,

        1, 0, 6,
        0.3,0, 6,
        1,0, -2,

//        // Cannon part
//        0, 1, -3,
//        0, 1.5, -4,
//        0, 1.2, -4,
//        0, 1.2, -4,
//        0, 0.5, -3,
//        0, 1, -3,




//        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//        -1.0f,-1.0f, 1.0f,
//        -1.0f, 1.0f, 1.0f, // triangle 1 : end
//        1.0f, 1.0f,-1.0f, // triangle 2 : begin
//        -1.0f,-1.0f,-1.0f,
//        -1.0f, 1.0f,-1.0f, // triangle 2 : end
//       1.0f,-1.0f, 1.0f,
//        -1.0f,-1.0f,-1.0f,
//        1.0f,-1.0f,-1.0f,
//        1.0f, 1.0f,-1.0f,
//        1.0f,-1.0f,-1.0f,
//        -1.0f,-1.0f,-1.0f,
//        -1.0f,-1.0f,-1.0f,
//        -1.0f, 1.0f, 1.0f,
//        -1.0f, 1.0f,-1.0f,
//        1.0f,-1.0f, 1.0f,
//        -1.0f,-1.0f, 1.0f,
//        -1.0f,-1.0f,-1.0f,
//        -1.0f, 1.0f, 1.0f,
//        -1.0f,-1.0f, 1.0f,
//        1.0f,-1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f,
//        1.0f,-1.0f,-1.0f,
//        1.0f, 1.0f,-1.0f,
//        1.0f,-1.0f,-1.0f,
//        1.0f, 1.0f, 1.0f,
//        1.0f,-1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f,-1.0f,
//        -1.0f, 1.0f,-1.0f,
//        1.0f, 1.0f, 1.0f,
//        -1.0f, 1.0f,-1.0f,
//        -1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f,
//        -1.0f, 1.0f, 1.0f,
//        1.0f,-1.0f, 1.0f
    };
    GLfloat vertex_buffer_cannon[3*3*100*360];
    double pi = 22.0/7;                                     // pi in radians
    double in_angle = (pi/180.0f);                          // 1 degree angle of rotation in radians
    printf("in_angle is %lf\n",in_angle);
    int i=0, j=0, k=0;
    double cx = 0, cy = 0, cz = 0;
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
        /*cy+=0.1;*/    cz-=0.01;
        g_vertex_buffer1[0] = cx-0.1;   g_vertex_buffer1[1] = cy; g_vertex_buffer1[2]=cz;
    }
    this->objectarr[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->objectarr[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data+(12*3), COLOR_RED, GL_FILL);
    this->objectarr[2] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data+(24*3), COLOR_ORANGE, GL_FILL);
    this->objectarr[3] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data+(36*3), COLOR_YELLOW, GL_FILL);
    this->objectarr[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+(48*3), COLOR_DARK_GREEN, GL_FILL);
    this->objectarr[6] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+(54*3), COLOR_DARK_BLUE, GL_FILL);
    this->objectarr[5] = create3DObject(GL_TRIANGLES, 360*100*3, vertex_buffer_cannon, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    // Rotate about y axis : Does the part for left and right
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1   =  rotate * glm::rotate((float) (5 * M_PI / 180.0f), glm::vec3(1, 0, 0));             // Rotate about x axis

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->objectarr[0]);
    draw3DObject(this->objectarr[1]);
    draw3DObject(this->objectarr[2]);
    draw3DObject(this->objectarr[3]);
    draw3DObject(this->objectarr[4]);
//    draw3DObject(this->objectarr[6]);
}

void Ball::Cannondraw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (glm::vec3(this->position.x-2.9*sin(glm::radians(this->rotation1)), this->position.y+0.8, this->position.z-2.9*cos(glm::radians(this->rotation1))));    // glTranslatef
    // Rotate about y axis : Does the part for left and right
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1   = rotate * glm::rotate((float) (rotation2 * M_PI / 180.0f), glm::vec3(1, 0, 0)) ;            // Rotate about x axis

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->objectarr[5]);
}

void Ball::Splashdraw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (glm::vec3(this->position.x-2.9*sin(glm::radians(this->rotation1)), this->position.y+0.8-2, this->position.z-2.9*cos(glm::radians(this->rotation1))));    // glTranslatef
    // Rotate about y axis : Does the part for left and right
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate1   = rotate * glm::rotate((float) (rotation3 * M_PI / 180.0f), glm::vec3(1, 0, 0)) ;            // Rotate about x axis

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->objectarr[6]);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int flag) {
    printf("position.y is %lf\n", this->position.y);
    if (this->position.y + this->upspeed <= -1)
    {
        this->upspeed = 0;
        this->inair = 0;
//        this -> position.y = -1;
    }
    else    this->inair = 1;
    if (flag == 0)
    {
        this->position.y += this->upspeed;
        this->upspeed -= 0.05;
    }
//    this->rotation += speed;
//     this->position.x -= speed;
//     this->position.y -= speed;
}

