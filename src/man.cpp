#include "man.h"
#include "main.h"

Man::Man(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
 //   this->rotation = -15;
    this->upspeed = 0;
    this->rotation1 = 0;
    this->rotation2 = 5;
    speed = 1;
    this->inair=0;
    this->inboat = 1;
    this->timer=500;

        GLfloat vertex_buffer_data[] = {

            /* Body */
                    -0.35f,-0.5f,-0.15f,
                    -0.35f,-0.5f, 0.15f,
                    -0.35f, 0.5f, 0.15f,
                    0.35f, 0.5f,-0.15f,
                    -0.35f,-0.5f,-0.15f,
                    -0.35f, 0.5f,-0.15f,
                   0.35f,-0.5f, 0.15f,
                    -0.35f,-0.5f,-0.15f,
                    0.35f,-0.5f,-0.15f,
                    0.35f, 0.5f,-0.15f,
                    0.35f,-0.5f,-0.15f,
                    -0.35f,-0.5f,-0.15f,
                    -0.35f,-0.5f,-0.15f,
                    -0.35f, 0.5f, 0.15f,
                    -0.35f, 0.5f,-0.15f,
                    0.35f,-0.5f, 0.15f,
                    -0.35f,-0.5f, 0.15f,
                    -0.35f,-0.5f,-0.15f,
                    -0.35f, 0.5f, 0.15f,
                    -0.35f,-0.5f, 0.15f,
                    0.35f,-0.5f, 0.15f,
                    0.35f, 0.5f, 0.15f,
                    0.35f,-0.5f,-0.15f,
                    0.35f, 0.5f,-0.15f,
                    0.35f,-0.5f,-0.15f,
                    0.35f, 0.5f, 0.15f,
                    0.35f,-0.5f, 0.15f,
                    0.35f, 0.5f, 0.15f,
                    0.35f, 0.5f,-0.15f,
                    -0.35f, 0.5f,-0.15f,
                    0.35f, 0.5f, 0.15f,
                    -0.35f, 0.5f,-0.15f,
                    -0.35f, 0.5f, 0.15f,
                    0.35f, 0.5f, 0.15f,
                    -0.35f, 0.5f, 0.15f,
                    0.35f,-0.5f, 0.15f,

            /* Legs */
            -0.3, -0.5, 0,
            -0.3, -1.5, 0,
            -0.1, -0.5, 0,

            0.3, -0.5, 0,
            0.3, -1.5, 0,
            0.1, -0.5, 0,

            /* Hands */
            -0.35, 0.3, 0,
            -1, -0.5, 0,
            -0.35, 0.1, 0,

            0.35, 0.3, 0,
            1, -0.5, 0,
            0.35, 0.1, 0,

            /* Hat */
            -0.3,1.1,-0.4,
            0.3, 1.1, -0.4,
            -0.3, 1.1, 0.4,
            -0.3, 1.1, 0.4,
            0.3, 1.1, -0.4,
            0.3, 1.1, 0.4,

            0.3, 1.1, -0.3,
            0.3, 1.1, 0.3,
            0.3, 1, -0.3,
            0.3, 1, -0.3,
            0.3, 1.1, 0.3,
            0.3, 1, 0.3,

            -0.3, 1.1, -0.3,
            -0.3, 1.1, 0.3,
            -0.3, 1, -0.3,
            -0.3, 1, -0.3,
            -0.3, 1.1, 0.3,
            -0.3, 1, 0.3,

            -0.3, 1.1, 0.3,
            0.3, 1.1, 0.3,
            -0.3, 1, 0.3,
            -0.3, 1, 0.3,
            0.3, 1.1, 0.3,
            0.3, 1, 0.3,

            -0.3, 1.1, -0.3,
            0.3, 1.1, -0.3,
            -0.3, 1, -0.3,
            -0.3, 1, -0.3,
            0.3, 1.1, -0.3,
            0.3, 1, -0.3,
        };

        GLfloat g_vertex_buffer_data[2*90*360*3*3];                // Array containing the vertices of each triangle
        int k=0,i=0, j=0;
        for (i=0;i<90;i++)
        {
            for (j=0;j<360;j++)
            {
                g_vertex_buffer_data[k++] = .3*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = .3*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f)+0.75;
                g_vertex_buffer_data[k++] = .3*cos(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = .3*sin(glm::radians(i))+0.75;  g_vertex_buffer_data[k++] = 0;
                g_vertex_buffer_data[k++] = .3*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = .3*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f)+0.75;
                g_vertex_buffer_data[k++] = .3*cos(i*M_PI/180.0f);
            }
        }
        for (i=0;i<90;i++)
        {
            for (j=0;j<360;j++)
            {
                g_vertex_buffer_data[k++] = .3*cos(j*M_PI/180.0f)*sin(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = .3*sin(j*M_PI/180.0f)*sin(i*M_PI/180.0f)+0.75;
                g_vertex_buffer_data[k++] = -1*.3*cos(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = 0;  g_vertex_buffer_data[k++] = .3*sin(glm::radians(i))+0.75;  g_vertex_buffer_data[k++] = 0;
                g_vertex_buffer_data[k++] = .3*cos((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f);
                g_vertex_buffer_data[k++] = .3*sin((j+1)*M_PI/180.0f)*sin(i*M_PI/180.0f)+0.75;
                g_vertex_buffer_data[k++] = -1*.3*cos(i*M_PI/180.0f);
            }
        }
    this->object[0] = create3DObject(GL_TRIANGLES, 2*90*360*3, g_vertex_buffer_data, COLOR_PEACH);
    this->object[1] = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+6*2*3*3, COLOR_PURPLE2, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+6*2*3*3+6*3, COLOR_HAND, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data+6*2*3*3+6*3+6*3, COLOR_BLACK, GL_FILL);
}

void Man::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    // Rotate about y axis : Does the part for left and right
    glm::mat4 rotate    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1   =  rotate * glm::rotate((float) (this->rotation2 * M_PI / 180.0f), glm::vec3(1, 0, 0));             // Rotate about x axis
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.5, 0));
    Matrices.model *= (translate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
}

void Man::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Man::tick(int flag) {
    printf("position.y is %lf\n", this->position.y);
    if (this->position.y + this->upspeed <= 0)            // -1.8 is the level of the gorund
    {
        this->upspeed = 0;
        this->inair = 0;
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


