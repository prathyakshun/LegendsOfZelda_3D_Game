#include "main.h"
#include "string.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "sail.h"
#include "cannon.h"
#include "cannonball.h"
#include "rock.h"
#include "health.h"
#include "monster.h"
#include "bossmonster.h"
#include "boost.h"
#include "gift.h"
#include "barrel.h"
#include "land.h"
#include "man.h"
#include "treasure.h"
#include "tree.h"
#include "flymonster.h"
#include "laser.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

extern bool cannon_keyboard_input, drag_pan;
extern double drag_oldx, drag_oldy;
Ball ball1;
Water water1;
Land land1;
Sail sail1;
Barrel barrel1;
Treasure treasure1;
Tree tree1;
Man man1;
Laser laser1;
Cannonball cannonball1;
Flymonster flymonster1;
vector <Cannonball> cannonballarr;
vector <Rock> rockarr;
vector <Health> healtharr;
vector <Monster> monsterarr;
vector <Bossmonster> bossmonsterarr;
vector <Boost> boostarr;
vector <Gift> giftarr;
vector <Barrel> barrelarr;
vector <Tree> treearr;
vector <Flymonster> flymonsterarr;
vector <Laser> laserarr;
vector <double> xarr, yarr, zarr;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
int cannon_counter = 0, rev = 1, comeup=-1, init_rocks = 1, rockup=-1,barrelup=-1, ret=0, windcounter=0, monstercounter=0, boostcounter=0,jumpcounter=0, rev2=-1, lockcounter=0, only_man=0, manboatcounter=0, detected_land_boat_collision=0, counterlevel=0, screen_x=0, disableboat_bounce=0;
double windx = 0, windy = 0, windz = 0;
double upmove=1, downmove=1, rightmove=1, leftmove=1;
double upmoved=0, downmoved=0, rightmoved=0, leftmoved=0, eye9y = 60;


Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw(int ret) {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    int rev = 1;
    if (ball1.rotation1 >= 90 && ball1.rotation1 <= 270) rev = -1;
    glm::vec3 eye, target;
    /* Standard start look ahead View */
    if (ret == 0)
    {
        eye.x = 5*cos(camera_rotation_angle*M_PI/180.0f);
        eye.y = 0;
        eye.z = 5*sin(camera_rotation_angle*M_PI/180.0f);
        target.x = 0;   target.y = 0;   target.z = 0;
    }
    /* Top View */
    if (ret == 1)
    {
        eye.x = ball1.position.x;  eye.y = 60; eye.z = ball1.position.z+1;
        target.x = ball1.position.x;   target.y = ball1.position.y;   target.z = ball1.position.z;
    }
    /* Tower-Base View */
    if (ret == 2)
    {
        eye.x = 0;  eye.y = 0;  eye.z = 5;
        target.x = ball1.position.x;   target.y = ball1.position.y;   target.z = ball1.position.z;
    }
    /* Follow-cam View */
    if (ret == 3)
    {
        eye.x = ball1.position.x+12*sin(glm::radians(ball1.rotation1));
        eye.y = 2;
        eye.z = ball1.position.z+9*cos(glm::radians(ball1.rotation1));
        target.x = ball1.position.x+3*sin(glm::radians(ball1.rotation1));
        target.y = ball1.position.y+3;   target.z = ball1.position.z+3*cos(glm::radians(ball1.rotation1));
    }
    /* Boat View First-person view */
    if (ret == 4)
    {
        eye.x = ball1.position.x-1*sin(glm::radians(ball1.rotation1));
        eye.y = ball1.position.y+2;
        eye.z = ball1.position.z-1*cos(glm::radians(ball1.rotation1));
        target.x = ball1.position.x-3*sin(glm::radians(ball1.rotation1));
        target.y = ball1.position.y+1;   target.z = ball1.position.z-3*cos(glm::radians(ball1.rotation1));
    }
    /* Side View */
    if (ret == 5)
    {
        eye.x = ball1.position.x;
        eye.y = 1;
        eye.z = ball1.position.z-1;
        target.x = -(cos(glm::radians(ball1.rotation1)));
        target.y = ball1.position.y+1;   target.z = ball1.position.z-3;
    }
    /* Tower-Top View */
    if (ret == 6)
    {
        eye.x = 0;
        eye.y = 60;
        eye.z = -10;
        target.x = ball1.position.x;
        target.y = ball1.position.y;
        target.z = ball1.position.z;
    }
    /* Follow-man View */
    if (ret == 7)
    {
        eye.x = man1.position.x+4*sin(glm::radians(man1.rotation1));
        eye.y = man1.position.y+2;
        eye.z = man1.position.z+4*cos(glm::radians(man1.rotation1));
        target.x = man1.position.x-3*sin(glm::radians(man1.rotation1));
        target.y = man1.position.y+1;   target.z = man1.position.z-4*cos(glm::radians(man1.rotation1));
    }
    /* First person man View */
    if (ret == 8)
    {
        eye.x = man1.position.x-1*sin(glm::radians(man1.rotation1));
        eye.y = man1.position.y+2;
        eye.z = man1.position.z-1*cos(glm::radians(man1.rotation1));
        target.x = man1.position.x-3*sin(glm::radians(man1.rotation1));
        target.y = man1.position.y+1;   target.z = man1.position.z-3*cos(glm::radians(man1.rotation1));
    }

    /* Helio View */
    if (ret == 9)
    {
        eye.x = ball1.position.x;  eye.y = eye9y; eye.z = ball1.position.z+1;
        target.x = ball1.position.x;   target.y = ball1.position.y;   target.z = ball1.position.z;
        if (upmove) {upmoved+=0.1;}
        if (downmove)  {downmoved+=0.1;}
        if (leftmove)   {leftmoved+=0.1;}
        if (rightmove)  {rightmoved+=0.1;}
        target.z += upmoved;target.z -= downmoved;target.x -= leftmoved;target.x += rightmoved;
    }

    if (ret != 9)   {leftmoved=0;   rightmoved=0;   upmoved=0;  downmoved=0;}
//    /* Placing hearts */
//    double placer = 0.5;
//    int i =0;
//    for (i=0;i<healtharr.size();i++)
//    {
//        if (i%2==0) placer += 0.5;
//        healtharr[i].set_position(target.x+placer, target.y, target.z);
//    }

//    eye.x = ball1.position.x;
//    eye.y = ball1.position.y+3;
//    eye.z = ball1.position.z+9;
//    target.x = ball1.position.x-5*sin(glm::radians(ball1.rotation1));
//    target.y = ball1.position.y+2;   target.z = ball1.position.z-3;
    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    land1.draw(VP);
    ball1.draw(VP);
    ball1.Cannondraw(VP);
//    ball1.Splashdraw(VP);
    sail1.draw(VP);
//    tree1.draw(VP);
    treasure1.draw(VP);

    man1.draw(VP);
//    flymonster1.draw(VP);

    int i =0;
    printf("Laserarr.size is %d hello\n", laserarr.size());
    for (i=0;i<laserarr.size();i++) laserarr[i].draw(VP);
    for (i=0;i<flymonsterarr.size();i++)    flymonsterarr[i].draw(VP);
    for (i=0;i<cannonballarr.size();i++)    cannonballarr[i].draw(VP);
    for (i=0;i<rockarr.size();i++)  rockarr[i].draw(VP);
    for (i=0;i<ball1.life;i++)    healtharr[i].draw(VP);
    for (i=0;i<monsterarr.size();i++)    monsterarr[i].draw(VP);
    for (i=0;i<bossmonsterarr.size();i++)    bossmonsterarr[i].draw(VP);
    for (i=0;i<boostarr.size();i++) boostarr[i].draw(VP);
    for (i=0;i<giftarr.size();i++)  giftarr[i].draw(VP);
    for (i=0;i<barrelarr.size();i++)   barrelarr[i].draw(VP);
    for (i=0;i<treearr.size();i++)  treearr[i].draw(VP);
    water1.draw(VP);
}

/* For zooming on mouse scroll */
void zooming(double yoffset)
{
        if (yoffset > 0)    eye9y += 5;
        else if (yoffset < 0)   eye9y -= 5;
//        if (screen_zoom <= 0)   eye9y = 0.1;
    printf("eye9y is %lf\n", eye9y);
}

/* Collision Detection Functions */
bool detect_rock_boat_collision(Ball a, Rock b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_cannon_rock_collision(Rock a, Cannonball b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_monster_boat_collision(Ball a, Monster b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_bossmonster_boat_collision(Ball a, Bossmonster b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+0.5 && b.position.x >= a.position.x-0.5  && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_boost_boat_collision(Ball a, Boost b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2)
        return 1;
    else
        return 0;
}

bool detect_gift_boat_collision(Ball a, Gift b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2)
        return 1;
    else
        return 0;
}

bool detect_cannon_monster_collision(Monster a, Cannonball b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_cannon_bossmonster_collision(Bossmonster a, Cannonball b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+2 && b.position.y >= a.position.y-2)
        return 1;
    else
        return 0;
}

bool detect_barrel_boat_collision(Ball a, Barrel b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && a.position.y >= 0)
        return 1;
    else
        return 0;
}

bool detect_boat_land_collision(Land a, Ball b)
{
    if (b.position.x <= a.position.x + 50 && b.position.x >= a.position.x - 50 && b.position.z <= a.position.z + 50 && b.position.z >= a.position.z -50)
        return 1;
    else
        return 0;
}

bool detect_boat_man_collision(Ball a, Man b)
{
    if (b.position.z <= a.position.z+3 && b.position.z >= a.position.z-3 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2)
        return 1;
    else
        return 0;
}

bool detect_man_treasure_collision(Man a, Treasure b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2)
        return 1;
    else
        return 0;
}

bool detect_man_land_collision(Land a, Man b)
{
    if (b.position.x <= a.position.x + 50 && b.position.x >= a.position.x - 50 && b.position.z <= a.position.z + 50 && b.position.z >= a.position.z -50)
        return 1;
    else
        return 0;
}

bool detect_laser_boat_collision(Ball a, double xa, double ya, double za)
{
//    if (xa <= a.position.x + 1 && xa >= a.position.x - 1 && ya <= a.position.z + 1 && ya >= a.position.z - 1 && za <= a.position.y+1 && za >= a.position.y-1)
      if(xa == a.position.x && ya == a.position.y && za == a.position.z)
        return 1;
    else
        return 0;
}

bool detect_cannon_flymonster_collision(Flymonster a, Cannonball b)
{
    if (b.position.z <= a.position.z+2 && b.position.z >= a.position.z-2 && b.position.x <= a.position.x+2 && b.position.x >= a.position.x-2 && b.position.y <= a.position.y+1 && b.position.y >= a.position.y-1)
        return 1;
    else
        return 0;
}

int tick_input(GLFWwindow *window) {
    upmove=0;   leftmove=0; rightmove=0;    downmove=0;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int zero = glfwGetKey(window, GLFW_KEY_0);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int six = glfwGetKey(window, GLFW_KEY_6);
    int seven = glfwGetKey(window, GLFW_KEY_7);
    int eight = glfwGetKey(window, GLFW_KEY_8);
    int nine = glfwGetKey(window, GLFW_KEY_9);
    int l = glfwGetKey(window, GLFW_KEY_L);
    int g = glfwGetKey(window, GLFW_KEY_G);
    int p = glfwGetKey(window, GLFW_KEY_P);
    int o = glfwGetKey(window, GLFW_KEY_O);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int y = glfwGetKey(window, GLFW_KEY_Y);


    if (zero)   ret = 0;
    if (one)    ret = 1;
    if (two)    ret = 2;
    if (three)  ret = 3;
    if (four)   ret = 4;
    if (five)   ret = 5;
    if (six)    ret = 6;
    if (seven)  ret = 7;
    if (eight)  ret = 8;
    if (nine)   ret = 9;

    /* Cheats to increase health and score */
    if (t)  ball1.score += 10;
    if (y)  {ball1.life = 10;    printf("life is %d\n", ball1.life);}

    /* Player getting out of the ship */
    printf("detec is %d\n",detect_boat_land_collision(land1, ball1));
    printf("det is %d\n", detected_land_boat_collision);
    if (g && man1.inboat==1 && (detected_land_boat_collision == 1 || ball1.lock == 1) && manboatcounter==0)
    {
        disableboat_bounce = 1;
        printf("WORKING?\n");
        man1.inboat = 0;
        manboatcounter=1;
    }
    if(manboatcounter!=0)   {manboatcounter++; manboatcounter%=100;}

    /* Player getting back on to the boat */
    if (g && man1.inboat==0 && (detected_land_boat_collision == 1 || ball1.lock == 1) && manboatcounter==0) {ball1.position.y = -1; man1.position.y = 0;    man1.inboat=1;  manboatcounter=1;    man1.rotation1=ball1.rotation1;    man1.set_position(ball1.position.x, 0, ball1.position.z);}

    // Change view when man is out of the ship */
    if (man1.inboat == 0 && !(ret == 7 || ret == 8))   ret = 7;

    /* Taking care of locking when near the island */
    if (l)
    {
        ball1.lock = 0;
        lockcounter=1;
        ball1.position.y = -1;
        man1.position.y = 0;
        sail1.position.y = -1;
    }
    if (lockcounter != 0)   {lockcounter++; lockcounter%=100;}

    /* Mouse drag detection */
    if (ret == 9)
    {
        int drag_pan = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (drag_pan)
        {
            if (drag_oldx == -1 || drag_oldy == -1)
            {
                glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
            }
            else
            {
                double newx, newy;
                glfwGetCursorPos(window, &newx, &newy);
                if (newx < drag_oldx)   leftmove = 1;
                else if (newx > drag_oldx)  rightmove = 1;
                if (newy < drag_oldy)   upmove = 1;
                else if (newy > drag_oldy)  downmove = 1;
                drag_oldx = newx;
                drag_oldy = newy;
            }
        }
    }
    double x1=0, y1=0;
    int left_button;
    if (ret == 4)
    {
        GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
        glfwSetCursor(window, cursor);
    }
    else    glfwSetCursor(window, NULL);
//  if (ret == 4) to be removed
//    if (ret == 4)
//    {
        left_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (left_button)
        {
            glfwGetCursorPos(window, &x1, &y1);
            printf("mouse x1 %lf y1 %lf\n", x1, y1);
            if (ret != 9)   f = 1;
        }
        glfwGetCursorPos(window, &x1, &y1);

        /* Changing boat direction with cursor */
        if (ret == 4)
        {
            if (x1 >= (screen_x/2))  {ball1.rotation1 -= (x1-(screen_x/2))/1000; man1.rotation1 = ball1.rotation1;}
            if (x1 <= (screen_x/2))  {ball1.rotation1 += ((screen_x/2)-x1)/1000; man1.rotation1 = ball1.rotation1;}
        }
//    }

    /* Fire only after an interval has passed after the last cannon firing */
    if (f && cannon_counter==0)
    {
        cannon_counter++;
        Cannonball cannonball1 = Cannonball(ball1.position.x-2.9*sin(glm::radians(ball1.rotation1)), ball1.position.y+0.8+sin(glm::radians(ball1.rotation2))*1, ball1.position.z-2.9*cos(glm::radians(ball1.rotation1)), COLOR_BLACK);
        cannonball1.rotation1 = ball1.rotation1;
        if (x1 >= (screen_x/2) && left_button)  cannonball1.rotation1 -= (x1-(screen_x/2))/10;
        if (x1 <= (screen_x/2) && left_button)  cannonball1.rotation1 += ((screen_x/2)-x1)/10;
        cannonball1.rotation2 = ball1.rotation2;
        cannonball1.speed = 1.2;
        cannonball1.upspeed = cannonball1.speed * sin(glm::radians(cannonball1.rotation2));
        cannonball1.zspeed = cannonball1.speed * cos(glm::radians(cannonball1.rotation2));
        cannonballarr.push_back(cannonball1);
    }
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (space && ball1.inair == 0)
    {
        if (man1.inboat == 1)
        {
            ball1.upspeed = 0.7;
            sail1.upspeed = 0.7;
            ball1.inair = 1;
            sail1.inair=1;
            ball1.tick(0);
            sail1.tick(0);
        }
        if (man1.inair == 0)
        {
            man1.upspeed = 0.7;
            man1.inair=1;
            man1.tick(0);
        }
    }

    /* Camera angle changing*/
    if (p)  camera_rotation_angle += 1;
    if (o)  camera_rotation_angle -= 1;

    /* Cannon lift up and down */
    if (w)
    {
        ball1.rotation2 += 1;
        if (ball1.rotation2 >= 90)  ball1.rotation2 = 90;
    }
    if (s)
    {
        ball1.rotation2 -= 1;
        if (ball1.rotation2 <= 0)   ball1.rotation2 = 0;
    }

    if (left) {
        int dir = 1;
        if (down)   dir = -1;
        if (man1.inboat == 1)
        {

            ball1.rotation1 += dir*1;
            sail1.rotation1 += dir*1;
        }
        man1.rotation1 += dir*1;
    }
    if (right)
    {
        int dir = 1;
        if (down)   dir = -1;
        if (man1.inboat==1)
        {
            ball1.rotation1 -= dir*1;
            sail1.rotation1 -= dir*1;
        }
        man1.rotation1 -= dir*1;
    }
    detected_land_boat_collision = 0;
    if ((up && ball1.lock==0) || (up && man1.inboat==0))
    {
        int extra=1;
        if (ball1.inair)    extra=3;
        if (man1.inboat==1)
        {
            printf("here rotation is %lf\n", ball1.rotation1);
            printf ("rev is %d\n",rev);
            printf("sine is %lf\n", (sin(glm::radians(ball1.rotation1))*0.1));
            ball1.position.z -= -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            ball1.position.x -= extra*ball1.speed * (sin(glm::radians(ball1.rotation1))*0.1);
            sail1.position.z -= -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            sail1.position.x = ball1.position.x;
        }
        man1.position.z -= -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1));
        man1.position.x -= extra*ball1.speed * (sin(glm::radians(man1.rotation1))*0.1);
        if (!detect_man_land_collision(land1, man1) && man1.inboat==0)
        {
            man1.position.z += -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1));
            man1.position.x += extra*ball1.speed * (sin(glm::radians(man1.rotation1))*0.1);
        }
        if (detect_boat_land_collision(land1, ball1))
        {
            detected_land_boat_collision = 1;
            ball1.position.z += -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            ball1.position.x += extra*ball1.speed * (sin(glm::radians(ball1.rotation1))*0.1);
            sail1.position.z += -extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            sail1.position.x = ball1.position.x;
            if (man1.inboat == 1)
            {
                man1.position.z += (-extra*ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1))-0.00001);
                man1.position.x += (extra*ball1.speed * (sin(glm::radians(man1.rotation1))*0.1)-0.00001);

            }
        }
    }
    if ((down && ball1.lock==0) || (down && man1.inboat==0))
    {
        if (man1.inboat==1)
        {
            ball1.position.z += -ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            ball1.position.x += ball1.speed * (sin(glm::radians(ball1.rotation1))*0.1);
            sail1.position.z += -ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            sail1.position.x = ball1.position.x;
        }
        man1.position.z += -ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1));
        man1.position.x += ball1.speed * (sin(glm::radians(man1.rotation1))*0.1);
        if (!detect_man_land_collision(land1, man1) && man1.inboat==0)
        {
            man1.position.z -= -ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1));
            man1.position.x -= ball1.speed * (sin(glm::radians(man1.rotation1))*0.1);
        }
        if (detect_boat_land_collision(land1, ball1))
        {
            detected_land_boat_collision = 1;
            ball1.position.z -= -ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            ball1.position.x -= ball1.speed * (sin(glm::radians(ball1.rotation1))*0.1);
            sail1.position.z -= -ball1.speed * rev2*rev*0.1*cos(glm::radians(ball1.rotation1));
            sail1.position.x = ball1.position.x;
            if (man1.inboat == 1)
            {
                man1.position.z -= -ball1.speed * rev2*rev*0.1*cos(glm::radians(man1.rotation1));
                man1.position.x -= ball1.speed * (sin(glm::radians(man1.rotation1))*0.1);
            }
         }
    }
    return ret;
}

void tick_elements() {
    GLint m_viewport[4];
    glGetIntegerv( GL_VIEWPORT, m_viewport );
    printf("screen size %d %d %d %d\n", m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
    screen_x = m_viewport[2];

    /* Displaying titlebat text */
    char stitle[1000];   stitle[0] = '\0';
    char title1st[] = "Legends of Zelda - Level "; char time1st[] = " Points \t\t\t Time remaining "; char req_score[] = " GET ";   char health1st[] = "\tHEALTH :";
    char levelstr[10], timestr[10], req_scorestr[10], health_str[10], score_str[10];
    sprintf(levelstr,"%d",ball1.level);
    sprintf(timestr, "%d",60-counterlevel/60);
    sprintf(req_scorestr, "%d", ball1.level*10);
    sprintf(health_str, "%d", ball1.life);
    sprintf(score_str, "%d", ball1.score);
    strcat(stitle,title1st);
    strcat(stitle, levelstr);
    strcat(stitle, req_score);
    strcat(stitle, score_str);
    strcat(stitle, " / ");
    strcat(stitle, req_scorestr);
    strcat(stitle, health1st);
    strcat(stitle, health_str);
    strcat(stitle,time1st);
    strcat(stitle,timestr);
    glfwSetWindowTitle(window, stitle);


    printf(" Player score is %d\n", ball1.score);
    printf("ret is %d\n", ret);
    printf("man1.inboat is %d\n", man1.inboat);
    /* Up - Down movement of boat and rocks*/
    if (ball1.position.y <= -1.65)   comeup = 1;
    if (ball1.position.y >= -1) comeup = -1;
    if (rockarr.size()>0 && rockarr[0].position.y <= -1.7)  rockup = 1;
    if (rockarr.size()>0 && rockarr[0].position.y == -1)    rockup = -1;
    if (barrelarr.size()>0 && barrelarr[0].position.y <= -2.2)    barrelup = 1;
    if (barrelarr.size()>0 && barrelarr[0].position.y>=-1.6)  barrelup = -1;
    int i = 0, j = 0;
    for (i=0;i<rockarr.size();i++)  rockarr[i].position.y += rockup*0.005;
    for (i=0;i<monsterarr.size();i++)   monsterarr[i].position.y += rockup*0.005;
    for (i=0;i<bossmonsterarr.size();i++)  bossmonsterarr[i].position.y += rockup*0.005;
    for (i=0;i<barrelarr.size();i++)    barrelarr[i].position.y += barrelup*0.005;
    if (ball1.lock == 0 /*&& disableboat_bounce == 0*/)
    {
        ball1.position.y += comeup*0.01;
        sail1.position.y += comeup*0.01;
        man1.position.y += comeup*0.01;
    }
    treasure1.rotation += 1;
    for (i=0;i<boostarr.size();i++) boostarr[i].rotation+=1;
    for (i=0;i<giftarr.size();i++)  giftarr[i].rotation+=1;

    /* Laser from flying monsters */
    for (i=0;i<flymonsterarr.size();i++)
    {
        if (flymonsterarr[i].shootcounter == 0)
        {
            if (flymonsterarr[i].shot == 1)
            {
                laserarr.erase(laserarr.begin()+i);
                xarr.erase(xarr.begin()+i); yarr.erase(yarr.begin()+i); zarr.erase(zarr.begin()+i);
            }
            flymonsterarr[i].shot = 1;
            xarr.push_back(ball1.position.x);
            yarr.push_back(4);
            zarr.push_back(ball1.position.z);
            flymonsterarr[i].shootcounter = 1;
            laser1 = Laser(flymonsterarr[i].position.x, flymonsterarr[i].position.y, flymonsterarr[i].position.z, xarr[i], yarr[i], zarr[i], COLOR_LASER_RED);
            laserarr.push_back(laser1);
//            if (flymonsterarr[i].shootcounter)  {xarr.erase(xarr.begin()+i);    yarr.erase(yarr.begin()+i); zarr.erase(zarr.begin()+i);}
        }
        else
        {
            if (flymonsterarr[i].shootcounter == 100)   {yarr[i] = 3;}
            if (flymonsterarr[i].shootcounter == 200)   {yarr[i] = 0;}
            if (flymonsterarr[i].shootcounter == 300)   {yarr[i] = -1;}
            laserarr.erase(laserarr.begin()+i);
            laser1 = Laser(flymonsterarr[i].position.x, flymonsterarr[i].position.y, flymonsterarr[i].position.z, xarr[i], yarr[i], zarr[i], COLOR_LASER_RED);
            laser1.shotme = 1;
            laserarr.push_back(laser1);
        }
        if (flymonsterarr[i].shootcounter != 0) flymonsterarr[i].shootcounter++;
        flymonsterarr[i].shootcounter %= 400;
    }

    /* Laser-Boat collision */
    for (i=0;i<laserarr.size();i++) if (detect_laser_boat_collision(ball1, xarr[i], yarr[i], zarr[i]) && laserarr[i].shotme!=1 && ball1.lock == 0)    {laserarr[i].shotme = 0; ball1.life--;}

    /* Cannon-Flymonster collision */
    for (i=0;i<flymonsterarr.size();i++)
        for (j=0;j<cannonballarr.size();j++)
            if (detect_cannon_flymonster_collision(flymonsterarr[i], cannonballarr[j])) {ball1.score += 100;    laserarr.erase(laserarr.begin()+i);    flymonsterarr.erase(flymonsterarr.begin()+i);   cannonballarr.erase(cannonballarr.begin()+j);}
    if (flymonsterarr.size() == 0) {for (i=0;i<laserarr.size();i++)    laserarr.erase(laserarr.begin()+i);}

    /* Boat-Rock collision */
    for (i=0;i<rockarr.size();i++)
        if (detect_rock_boat_collision(ball1, rockarr[i]))   {ball1.life--; rockarr.erase(rockarr.begin()+i);}

    /* Boat-Monster collision */
    for (i=0;i<monsterarr.size();i++)
        if (detect_monster_boat_collision(ball1, monsterarr[i])) {ball1.life--;  monsterarr.erase(monsterarr.begin()+i);}

    /* Boat-Bossmonster collision */
    for (i=0;i<bossmonsterarr.size();i++)
        if (detect_bossmonster_boat_collision(ball1, bossmonsterarr[i]) && bossmonsterarr[i].touched == 0)
        {
            ball1.life--;
            bossmonsterarr[i].touched = 1;
        }

    /* Boat-Boost collision */
    if (boostcounter % 1000 == 0)    {boostcounter = 0;  ball1.speed = 1;}
    boostcounter++;
    for (i=0;i<boostarr.size();i++)
        if (detect_boost_boat_collision(ball1, boostarr[i])) {ball1.speed = 7;    boostarr.erase(boostarr.begin()+i);   boostcounter=1;}

    /* Boat-Gift collision */
    for (i=0;i<giftarr.size();i++)
        if (detect_gift_boat_collision(ball1, giftarr[i]))
        {
            if (giftarr[i].type == 0)   {ball1.score+=10;}
            else if (giftarr[i].type == 1)  {ball1.life = 10;}
            giftarr.erase(giftarr.begin()+i);
        }

    /* Rock-Cannon collision */
    for (i=0;i<rockarr.size();i++)
        for (j=0;j<cannonballarr.size();j++)
            if (detect_cannon_rock_collision(rockarr[i], cannonballarr[j]))
                {ball1.score += 3;  rockarr.erase(rockarr.begin()+i);   cannonballarr.erase(cannonballarr.begin()+j);}

    /* Monster-Cannon collision */
    for (i=0;i<monsterarr.size();i++)
        for (j=0;j<cannonballarr.size();j++)
            if (detect_cannon_monster_collision( monsterarr[i], cannonballarr[j]))
                {ball1.score += 5;  Gift gift1 = Gift(monsterarr[i].position.x, monsterarr[i].position.y+1, monsterarr[i].position.z, COLOR_RED); gift1.type = rand()%2;    giftarr.push_back(gift1);  monsterarr.erase(monsterarr.begin()+i);   cannonballarr.erase(cannonballarr.begin()+j);}

    /* Bossmonster-Cannon collision */
    for (i=0;i<bossmonsterarr.size();i++)
        for (j=0;j<cannonballarr.size();j++)
            if (detect_cannon_bossmonster_collision( bossmonsterarr[i], cannonballarr[j]))
            {
                bossmonsterarr[i].life--;
                if (bossmonsterarr[i].life == 0)    {ball1.score += 7;  Boost boost1 = Boost(bossmonsterarr[i].position.x, 0, bossmonsterarr[i].position.z, COLOR_YELLOW);   boostarr.push_back(boost1);bossmonsterarr.erase(bossmonsterarr.begin()+i);}
                cannonballarr.erase(cannonballarr.begin()+j);
            }

    /* Boat-barrel collision */
    for (i=0;i<barrelarr.size();i++)
        if (detect_barrel_boat_collision( ball1, barrelarr[i]) && jumpcounter==0) {ball1.score += 5;    jumpcounter++;}

    /* Land-Boat collision */
    if (detected_land_boat_collision == 1 && lockcounter==0)   ball1.lock = 1;

    /* Man-Treasure collision */
    if (detect_man_treasure_collision(man1, treasure1)) {ball1.score+=1000;    treasure1.set_position(1000,1000,1000);}

    if (jumpcounter != 0)   {jumpcounter++; jumpcounter%=30;}

    /* Gift disappearing after time interval */
    for (i=0;i<giftarr.size();i++)
        if (giftarr[i].timer == 0)  giftarr.erase(giftarr.begin()+i);
        else    giftarr[i].timer--;

    /* Deciding wind and Moving the boat with wind flow */
    if (windcounter % 300 == 0)
    {
        windcounter = 0;
        int wx = rand()%3, wy = rand()%3, wz = rand()%3;
        if (wx == 0)    windx = -0.01;
        else if (wx == 1)   windx = 0;
        else    windx = 0.01;

        if (wz == 0)    windz = -0.01;
        else if (wz == 1)   windz = 0;
        else    windz = 0.01;
    }
    windcounter++;

    /* Sail rotation with wind */
    printf("sail1,rotation1 is %lf\n", sail1.rotation1);
    if (windz == 0) windz = 0.000001;
    double wind_angle = atan(-windx/windz);
    sail1.rotation1 = glm::degrees(wind_angle);

    /* Move boat with the wind */
    if (ball1.lock == 0)
    {
        ball1.position.z += windz;
        ball1.position.x += windx;
        sail1.position.z += windz;
        sail1.position.x += windx;
        man1.position.x += windx;
        man1.position.z += windz;
    }
    /* Moving the monsters */
    if (monstercounter % 500 == 0)
    {
        monstercounter = 0;
        for (i=0;i<monsterarr.size();i++)
        {
            int mx = rand()%3, my = rand()%3, mz = rand()%3;
            if (mx == 0)    monsterarr[i].mx = -0.05;
            else if (mx == 1)   monsterarr[i].mx = 0;
            else    monsterarr[i].mx = 0.05;

            if (mz == 0)    monsterarr[i].mz = -0.05;
            else if (mz == 1)   monsterarr[i].mz = 0;
            else    monsterarr[i].mz = 0.05;
        }
        for (i=0;i<bossmonsterarr.size();i++)
        {
            int mx = rand()%3, my = rand()%3, mz = rand()%3;
            if (mx == 0)    bossmonsterarr[i].mx = -0.03;
            else if (mx == 1)   bossmonsterarr[i].mx = 0;
            else    bossmonsterarr[i].mx = 0.03;

            if (mz == 0)    bossmonsterarr[i].mz = -0.03;
            else if (mz == 1)   bossmonsterarr[i].mz = 0;
            else    bossmonsterarr[i].mz = 0.03;
        }
        for (i=0;i<flymonsterarr.size();i++)
        {
            int mx = rand()%3, my = rand()%3, mz = rand()%3;
            if (mx == 0)    flymonsterarr[i].mx = -0.03;
            else if (mx == 1)   flymonsterarr[i].mx = 0;
            else    flymonsterarr[i].mx = 0.03;

            if (mz == 0)    flymonsterarr[i].mz = -0.03;
            else if (mz == 1)   flymonsterarr[i].mz = 0;
            else    flymonsterarr[i].mz = 0.03;
        }

    }
    monstercounter++;
    for (i=0;i<monsterarr.size();i++)
    {
        monsterarr[i].position.z += monsterarr[i].mz;
        monsterarr[i].position.x += monsterarr[i].mx;
    }
    for (i=0;i<bossmonsterarr.size();i++)
    {
        bossmonsterarr[i].position.z += bossmonsterarr[i].mz;
        bossmonsterarr[i].position.x += bossmonsterarr[i].mx;
    }
    for (i=0;i<flymonsterarr.size();i++)
    {
        flymonsterarr[i].position.z += flymonsterarr[i].mz;
        flymonsterarr[i].position.x += flymonsterarr[i].mx;
    }

    /* Taking care of rotation and changing z axis movement */
    if (ball1.rotation1 > 360)  ball1.rotation1 = (int)ball1.rotation1 % 360;
    if (ball1.rotation1 < 0)    ball1.rotation1 += 360;
    if (ball1.rotation1 >= 90 && ball1.rotation1 <= 270)  {rev = -1;    rev2=1;}
    else    {rev = 1;    rev2=-1;}

    /* For taking care fo cannon firing interval */
    if (cannon_counter%20 == 0)    cannon_counter=0;
    else    cannon_counter++;

    ball1.tick(0);
    sail1.tick(0);
    man1.tick(0);
    i = 0;

    /* Movement of cannonballs */
    for (i=0;i<cannonballarr.size();i++)
    {
        cannonballarr[i].tick(0, rev, rev2);
    }
    /* Erasing cannonballs */
    for (i=0;i<cannonballarr.size();i++)
    {
        if (cannonballarr[i].position.y <= -3)  cannonballarr.erase(cannonballarr.begin()+i);
    }

    /* Placing hearts */
    double placer = 0.5;
    for (i=0;i<healtharr.size();i++)
    {
        if (i%2==0) placer += 0.5;
        healtharr[i].set_position(placer+ball1.position.x,ball1.position.y+1, ball1.position.z);
    }
    cout << "camera rotation angle " << camera_rotation_angle << endl;
    cout << "ball1.rotation1 " << ball1.rotation1 << endl;
//    camera_rotation_angle += 1;

    counterlevel++;
    if (ball1.life <= 0)
    {
       printf("GAME OVER\n");
       printf("Successfully completed %d levels\n",ball1.level-1);
       exit(0);
    }
    if (counterlevel == 60*60)
    {
        counterlevel = 0;
        if (ball1.score < ball1.level*10)
        {
            printf("GAME OVER\n");
            printf("Successfully completed %d levels\n",ball1.level-1);
            exit(0);
        }
        else    ball1.level++;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, -1, COLOR_RED);
    water1 = Water(0, -2.2, COLOR_BLUE);
    land1 = Land(-200, -2, 100, COLOR_LIGHT_BROWN);
    sail1 = Sail(0, -1, COLOR_GRAY);
    barrel1 = Barrel(-100, -2,0, COLOR_BROWN);
    sail1.rotation1 = 335;
    man1 = Man(0, 0, -4, COLOR_GREEN);   // was -1 for y
    treasure1 = Treasure(-200, 0, 100, COLOR_YELLOW);

//    tree1 = Tree(0, 0,0, COLOR_BROWN);
    int i = 0;
    for (i=0;i<3;i++)
    {
        flymonster1 = Flymonster(3, 5,0,COLOR_RED);
        flymonsterarr.push_back(flymonster1);
    }
    for (i=0;i<50;i++)
    {
        int x = -250 + rand()%100;
        int z = 50 + rand()%100;
        tree1 = Tree(x, -1, z, COLOR_BROWN);
        tree1.rotation = rand()%360;
        treearr.push_back(tree1);
    }
    for (i=0;i<10;i++)
    {
        Health health1 = Health(0, 1,0, COLOR_PINK);
        if (i%2==1) health1.rotation1 = 180;
        healtharr.push_back(health1);
    }
    for (i=0;i<10;i++)
    {
        int x = -100 + rand()%200;
        int z = -100 + rand()%200;
        barrel1 = Barrel(x, -1, z, COLOR_BROWN);
        barrelarr.push_back(barrel1);
    }
    for (i=0;i<20;i++)
    {
        int x = -100 + rand()%200;
        int z = -100 + rand()%200;
        int rot = rand()%360;
        Rock rock1 = Rock(x, -1, z, COLOR_ROCK);
        rock1.rotation1 = rot;
        rockarr.push_back(rock1);
    }
    for (i=0;i<50;i++)
    {
        int x = -100 + rand()%200;
        int z = -100 + rand()%200;
        int rot = rand()%360;
        Monster monster1 = Monster(x, -1.5, z, COLOR_RED);
//        monster1.rotation1 = rot;
        monsterarr.push_back(monster1);
    }
    for (i=0;i<10;i++)
    {
        int x = -100 + rand()%200;
        int z = -100 + rand()%200;
        int rot = rand()%360;
        Bossmonster bossmonster1 = Bossmonster(x, -1, z, COLOR_RED);
//        monster1.rotation1 = rot;
        bossmonsterarr.push_back(bossmonster1);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices.transparent_ability = glGetUniformLocation(programID, "trans");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    // Enable blending
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    int ret = -1;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw(ret);
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            ret = tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f, 1.0f, 300.0f);
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
