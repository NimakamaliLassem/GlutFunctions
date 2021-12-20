/*********
   Traffic jam

PROBLEMS: Not anything I have noticed
----------
ADDITIONAL FEATURES:
1.There is a Menu that can take you to the game directly or indirectly (Through Guide Menu)
2.Traffic Light turns ON/OFF by using F1 so that cars stop when they see red light and vice versa.
3.Exit button:
    4.also turn blue when the mouse pointer is on it.
5.Guide button shows how to play in a new window so that it wont waste any space.
6.Guide button turn blue when Guide Menu is opened by clicking on it with mouse or using button esc.
7.You can change the color of all cars by using left/right arrow keys.
8.You can change the speed of all cars by using up/down arrow keys.
9.When you are about to spawn(put) a car on the top of another there program will tell you why you cannot and avoids collision
(in output screen there will be a message (printf statement) "If you spawn a car here it will colide with car number %d at X=%d Y=%d"
----------
Note: I have made sure that cars' lights are not considered for calculating the cars' collision
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1120
#define WINDOW_HEIGHT 480

#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532
//Colors Global
#define Red 0
#define Green 1 
#define Blue 2 
#define Purple 3
#define Yellow 4
#define Gray 5
#define Lime 6
#define Orange 7
#define Magneta 8
#define Beige 9
//Speed Global
#define Speed_1 0
#define Speed_2 1
#define Speed_3 2
#define Menu 0 
#define GameStart 1 
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
bool F1 = false;
bool Guide = false;
bool car = false;
bool activeTimer = false;
bool mouseE = false;
bool Timerio = false;
bool Hitbox = true;
int  winWidth, winHeight; // current Window width and height
int mode = Yellow;
int sp = Speed_1;
int StateM = Menu;
char color[10][10] = { "RED", "GREEN", "BLUE", "PURPLE", "YELLOW", "GRAY", "LIME", "ORANGE", "MAGENTA", "BEIGE" };
int speed1[3] = { 90, 40, 5 };
int speed[3] = { 30, 60, 90 };
char Page[2][5] = { "Menu", "Game" };
int r = 230, g = 25, b = 75;
int xC[10];
int yC[10];
int xyC[10][2];
int Con2 = 0;
int num, num2 = 1;
int xM, yM;
int timeCounter = 0;
int flag = 0;
int mouse_x, mouse_y;

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void onTimer(int v) {


    if (Timerio) {
        glutTimerFunc(speed1[sp], onTimer, 0);
        // Write your codes here.

        for (int k = 0; k < num; k++)
        {
            xC[k]++;

        }


        // to refresh the window it calls display() function
        glutPostRedisplay(); // display()
    }
}

void onTimer1(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    timeCounter++;
    glutPostRedisplay();
}
void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void drawCar(int num)
{
    /*if (num == Con2) {
        xyC[num][0] = xC[num];
        xyC[num][1] = yC[num];
        printf("X=%d, Y=%d, Con2=%d\n", xyC[num][0], xyC[num][1], Con2);
        Con2++;
    }*/
    //Apearing on the other side:
    for (int j = 0; j <= num; j++)
    {
        //1120 is the length of the window
        if ((xC[j] - 75) == 1120 / 2)
            xC[j] = -1120 / 2 - 160;
    }
    num++;
    //Lights:
    glColor3f(1, 1, 0.3);
    circle(xC[num - 1] + 75, yC[num - 1] + 15, 10);
    circle(xC[num - 1] + 75, yC[num - 1] - 15, 10);
    glColor4f(1, 1, 0.3, .3);
    //Light Effects:
    glBegin(GL_TRIANGLES);
    glVertex2f(xC[num - 1] + 75, yC[num - 1] + 15);
    glVertex2f(xC[num - 1] + 150, yC[num - 1] + 45);
    glVertex2f(xC[num - 1] + 150, yC[num - 1] - 15);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(xC[num - 1] + 75, yC[num - 1] - 15);
    glVertex2f(xC[num - 1] + 150, yC[num - 1] + 15);
    glVertex2f(xC[num - 1] + 150, yC[num - 1] - 45);
    glEnd();
    //Body:
    //"RED", "GREEN", "BLUE", "PURPLE", "YELLOW", "GRAY", "LIME", "ORANGE", "MAGENTA", "BEIGE"
    switch (mode)
    {
    case 0: glColor3ub(255, 0, 0);
        break;
    case 1: glColor3ub(60, 180, 75);
        break;
    case 2:glColor3ub(0, 0, 128);
        break;
    case 3:glColor3ub(150, 0, 150);
        break;
    case 4: glColor3ub(255, 255, 0);
        break;
    case 5: glColor3ub(128, 128, 128);
        break;
    case 6: glColor3ub(210, 245, 60);
        break;
    case 7: glColor3ub(245, 130, 48);
        break;
    case 8:glColor3ub(240, 50, 230);
        break;
    case 9: glColor3ub(255, 250, 200);

        break;
    }
    glRectd(xC[num - 1] - 75, yC[num - 1] - 35, xC[num - 1] + 75, yC[num - 1] + 35);
    //Side Mirrors:
    glColor3ub(0, 0, 0);
    glRectf(xC[num - 1] + 52.5, yC[num - 1] + 35, xC[num - 1] + 60, yC[num - 1] + 45);
    glRectf(xC[num - 1] + 52.5, yC[num - 1] - 35, xC[num - 1] + 60, yC[num - 1] - 45);
    //Windows:
    glColor3ub(40, 210, 235);
    glBegin(GL_QUADS);
    glVertex2f(xC[num - 1] - 50, yC[num - 1] + 30);
    glVertex2f(xC[num - 1] + 50, yC[num - 1] + 30);
    glVertex2f(xC[num - 1] + 40, yC[num - 1] + 15);
    glVertex2f(xC[num - 1] - 40, yC[num - 1] + 15);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xC[num - 1] - 40, yC[num - 1] - 15);
    glVertex2f(xC[num - 1] + 40, yC[num - 1] - 15);
    glVertex2f(xC[num - 1] + 50, yC[num - 1] - 30);
    glVertex2f(xC[num - 1] - 50, yC[num - 1] - 30);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xC[num - 1] - 43, yC[num - 1] + 15);
    glVertex2f(xC[num - 1] - 53, yC[num - 1] + 30);
    glVertex2f(xC[num - 1] - 53, yC[num - 1] - 30);
    glVertex2f(xC[num - 1] - 43, yC[num - 1] - 15);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xC[num - 1] + 43, yC[num - 1] - 15);
    glVertex2f(xC[num - 1] + 53, yC[num - 1] - 30);
    glVertex2f(xC[num - 1] + 53, yC[num - 1] + 30);
    glVertex2f(xC[num - 1] + 43, yC[num - 1] + 15);
    glEnd();
    glColor3f(0, 0, 0);
    circle(xC[num - 1], yC[num - 1], 14);
    glColor3f(1, 1, 1);
    circle(xC[num - 1], yC[num - 1], 12);
    if (num - 1 != 9) {
        glColor3f(0, 0, 0);
        vprint(xC[num - 1] - 5, yC[num - 1] - 5, GLUT_BITMAP_HELVETICA_18, "%d", num);
    }
    else {
        glColor3f(0, 0, 0);
        vprint(xC[num - 1] - 10, yC[num - 1] - 5, GLUT_BITMAP_HELVETICA_18, "%d", num);
    }

}

void display() {
    //
    // clear window to black
    glClearColor(0.255, 0.215, 0.15, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    //Menu
    if (StateM == 0)
    {
        glColor3ub(255, 255, 0);
        glRectf(-60, -20, 60, 20);
        glRectf(-60, -70, 60, -30);
        glRectf(-60, -120, 60, -80);
        print(-35, 50, "MENU", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3b(0, 0, 0);
        print(-35, -5, "PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
        print(-40, -60, "GUIDE", GLUT_BITMAP_TIMES_ROMAN_24);
        print(-30, -110, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    //Game
    else
    {


        //Asphalt
        glColor3f(.3, 0.3, 0.3);
        glBegin(GL_QUADS);
        glVertex2f(560, 200);
        glVertex2f(-560, 200);
        glVertex2f(-560, -200);
        glVertex2f(560, -200);
        glEnd();
        //Side Lines:
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(560, 150);
        glVertex2f(-560, 150);
        glVertex2f(-560, 140);
        glVertex2f(560, 140);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560, -150);
        glVertex2f(-560, -150);
        glVertex2f(-560, -140);
        glVertex2f(560, -140);
        glEnd();
        //Lines:
        glBegin(GL_QUADS);
        glVertex2f(560, -60);
        glVertex2f(560 - 140, -60);
        glVertex2f(560 - 140, -50);
        glVertex2f(560, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560, 60);
        glVertex2f(560 - 140, 60);
        glVertex2f(560 - 140, 50);
        glVertex2f(560, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 160, -60);
        glVertex2f(560 - 140 - 160, -60);
        glVertex2f(560 - 140 - 160, -50);
        glVertex2f(560 - 160, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 160, 60);
        glVertex2f(560 - 140 - 160, 60);
        glVertex2f(560 - 140 - 160, 50);
        glVertex2f(560 - 160, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 320, -60);
        glVertex2f(560 - 140 - 320, -60);
        glVertex2f(560 - 140 - 320, -50);
        glVertex2f(560 - 320, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 320, 60);
        glVertex2f(560 - 140 - 320, 60);
        glVertex2f(560 - 140 - 320, 50);
        glVertex2f(560 - 320, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 480, -60);
        glVertex2f(560 - 140 - 480, -60);
        glVertex2f(560 - 140 - 480, -50);
        glVertex2f(560 - 480, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 480, 60);
        glVertex2f(560 - 140 - 480, 60);
        glVertex2f(560 - 140 - 480, 50);
        glVertex2f(560 - 480, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 640, -60);
        glVertex2f(560 - 140 - 640, -60);
        glVertex2f(560 - 140 - 640, -50);
        glVertex2f(560 - 640, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 640, 60);
        glVertex2f(560 - 140 - 640, 60);
        glVertex2f(560 - 140 - 640, 50);
        glVertex2f(560 - 640, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 800, -60);
        glVertex2f(560 - 140 - 800, -60);
        glVertex2f(560 - 140 - 800, -50);
        glVertex2f(560 - 800, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 800, 60);
        glVertex2f(560 - 140 - 800, 60);
        glVertex2f(560 - 140 - 800, 50);
        glVertex2f(560 - 800, 50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 960, -60);
        glVertex2f(560 - 140 - 960, -60);
        glVertex2f(560 - 140 - 960, -50);
        glVertex2f(560 - 960, -50);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(560 - 960, 60);
        glVertex2f(560 - 140 - 960, 60);
        glVertex2f(560 - 140 - 960, 50);
        glVertex2f(560 - 960, 50);
        glEnd();
        //Traffic Light:
        glColor3f(0.15, 0.15, 0.15);
        glBegin(GL_QUADS);
        glVertex2f(112, 240);
        glVertex2f(-112, 240);
        glVertex2f(-112, 150);
        glVertex2f(112, 150);
        glEnd();
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(5, 240);
        glVertex2f(-5, 240);
        glVertex2f(-5, 150);
        glVertex2f(5, 150);
        glEnd();
        glColor3f(0, 0.2, 0);
        circle(57, 195, 30);
        glColor3f(1, 0, 0);
        circle(-57, 195, 30);

        if (F1)
        {
            glColor3f(0, 1, 0);
            circle(57, 195, 30);
            glColor3f(.2, 0, 0);
            circle(-57, 195, 30);
        }
        //Car
        for (int i = 0; i < num; i++)
            drawCar(i);
        //Variables
        glColor3f(1, 1, 0);
        vprint(-220, -225, GLUT_BITMAP_HELVETICA_18, "COLOR = << %s >>", color[mode]);
        print(135, -210, "/\\", GLUT_BITMAP_HELVETICA_18);
        print(135, -240, "\\/", GLUT_BITMAP_HELVETICA_18);
        vprint(50, -225, GLUT_BITMAP_HELVETICA_18, "SPEED = %d", speed[sp]);
        //Exit button

        if (mouseE)
        {
            glColor3ub(40, 210, 235);
            glRectf(-560, 200, -440, 240);
        }
        else {
            glColor3f(1, .5, 0);
            glRectf(-560, 200, -440, 240);
        }
        glColor3f(1, 1, 1);
        print(-555, 215, "EXIT (Space)", GLUT_BITMAP_HELVETICA_18);
        //Guide button
        glColor3f(1, .5, 0);
        glRectf(+560, 200, +440, 240);
        glColor3f(1, 1, 1);
        print(+450, 215, "GUIDE (Esc)", GLUT_BITMAP_HELVETICA_18);
        if (Guide)
        {
            glColor3ub(40, 210, 235);
            glRectf(+560, 200, +440, 240);
            glColor3f(1, 1, 1);
            print(+470, 215, "GUIDE", GLUT_BITMAP_HELVETICA_18);
            glColor3f(1, 1, 0);
            glRectf(-205, -155, 205, 155);
            glColor3ub(100, 0, 100);
            glRectf(-200, -150, 200, 150);
            glColor3ub(255, 255, 0);
            print(-40, 120, "[Guide]", GLUT_BITMAP_TIMES_ROMAN_24);
            print(-130, 90, "You can change the color of all", GLUT_BITMAP_HELVETICA_18);
            print(-160, 70, "cars by pressing RIGHT and LEFT keys.", GLUT_BITMAP_HELVETICA_18);
            print(-130, 20, "You can change the speed of all", GLUT_BITMAP_HELVETICA_18);
            print(-160, -10, "cars by pressing UP and DOWN keys.", GLUT_BITMAP_HELVETICA_18);
            print(-170, -60, "Press F1 to turn ON/OFF the traffic light.", GLUT_BITMAP_HELVETICA_18);
            print(-190, -100, "Press Esc/click on Guide to close Guide Menu", GLUT_BITMAP_HELVETICA_18);
            print(-100, -140, "Press F5 for Main Menu", GLUT_BITMAP_HELVETICA_18);
        }
        //Mouse Location
        glColor3ub(200, 0, 255);
        glRectf(-410, 200, -190, 240);
        glColor3b(1, 1, 1);
        vprint2(-400, 210, .2, "x: %d y: %d", xM, yM);
        //Name and ID
        glColor3ub(200, 0, 255);
        glRectf(+410, 200, +190, 240);
        glColor3b(1, 1, 1);
        print(+195, 217, "Nima Kamali Lassem", GLUT_BITMAP_TIMES_ROMAN_24);
        print(+270, 202, "22001471", GLUT_BITMAP_9_BY_15);



        // glColor3b(1, 1, 1);
         //vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
    }
    glutSwapBuffers();
}



//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == ' ')
        exit(0);
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        Guide = !Guide;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{

    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_F1: F1 = !F1;
        Timerio = !Timerio;
        onTimer(0);
        break; ;
    case GLUT_KEY_F5: StateM = 0;
    case GLUT_KEY_LEFT:
        if (mode == Red)
            mode = Beige;
        else
            mode--;
        break;
    case GLUT_KEY_RIGHT:
        if (mode == Beige)
            mode = Red;
        else
            mode++;
        break;
    case GLUT_KEY_DOWN:
        if (sp == Speed_1)
            sp = Speed_3;
        else
            sp--;
        break;
    case GLUT_KEY_UP:
        if (sp == Speed_3)
            sp = Speed_1;
        else
            sp++;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//

void onClick(int button, int stat, int x, int y)
{
    flag = 0;
    if (StateM == 1) {
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && mouse_y<120 && mouse_y>-120 && num < 10)
        {
            if (Con2 == 0)
            {
                xC[Con2] = mouse_x;
                yC[Con2] = mouse_y;

                car = !car;
                xyC[Con2][0] = mouse_x;
                xyC[Con2][1] = mouse_y;
                num++;
                Con2++;
            }
            else
            {
                for (int i = 0; i < Con2; i++)
                {
                    if ((mouse_x > xyC[i][0] - 170 && mouse_x < xyC[i][0] + 160) && (mouse_y > xyC[i][1] - 70 && mouse_y < xyC[i][1] + 70))
                    {
                        flag = 1;
                        printf("If you spawn a car here it will colide with car number %d at X=%d Y=%d\n", i + 1, mouse_x, mouse_y);
                    }


                }

                if (flag != 1)
                {

                    xC[Con2] = mouse_x;
                    yC[Con2] = mouse_y;
                    car = !car;
                    xyC[Con2][0] = mouse_x;
                    xyC[Con2][1] = mouse_y;
                    Con2++;
                    num++;
                }
            }
        }

        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && x < 120 && y < 40)
            exit(0);
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (x > 1000 && y < 40))
            Guide = !Guide;

    }
    else if (StateM == 0) {
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && x > 500 && x < 600 && y > 200 && y < 300)
            StateM = 1;
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && x > 500 && x < 600 && y>270 && y < 310)
            Guide = !Guide;
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && x > 500 && x < 600 && y>310 && y < 340)
            exit(0);
    }




    glutPostRedisplay();
}


//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.

}

void onMoveDown(int x, int y) {
    // Write your codes here.
   // if (x < -440 && y>200)
     //   mouseE = !mouseE;


    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.
    if (x < 120 && y < 40)
    {
        mouseE = true;
    }
    else mouseE = false;
    xM = x;
    yM = y;
    mouse_x = x - winWidth / 2;
    mouse_y = winHeight / 2 - y;
    // to refresh the window it calls display() function
    glutPostRedisplay();
}




void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Traffic Jam By Nima Kamali Lassem");

    glutDisplayFunc(display);

    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    timeCounter++;
#endif

    Init();

    glutMainLoop();

}