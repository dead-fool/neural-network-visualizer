#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#define USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include "iostream"
#include <time.h>

void glhFrustumf2(float* matrix, float left, float right, float bottom, float top,
    float znear, float zfar)
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}



void glhPerspectivef2(float* matrix, float fovyInDegrees, float aspectRatio,
    float znear, float zfar)
{
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * 3.14159  / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}


using namespace std;

bool flag = true;
GLfloat xRotated, yRotated, zRotated;

void check(int value)
{
    if (flag == true)
    {
        flag = false;
    }
    else if (flag == false)
    {
        flag = true;
    }
    cout << flag << "\n";

    //glutTimerFunc(1000, check, 0);
}

void highlight_lines(float x, float y, float z, float live_transparency_line)
{
    float a, b, c;
    for (a = 0; a <= 0.5; a = a + 0.1)
    {
        for (b = 0; b <= 0.5; b = b + 0.1)
        {
            for (c = 0; c <= 0.5; c = c + 0.1)
            {
                //First Hidden Layer Plane 1 
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, live_transparency_line);
                glVertex3f(x, y, z);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glEnd();

                //First Hidden Layer Plane 4
                if (c < 0.44)
                {
                    glPointSize(3.0);
                    glBegin(GL_POINTS);
                    glVertex3f(x, y, z);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                    glColor4f(1.0, 1.0, 1.0, live_transparency_line);
                    glVertex3f(x, y, z);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glEnd();
                }

                //Second Hidden Layer Plane 1 
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, live_transparency_line);
                glVertex3f(0.1 + b, 0.1 + a, 0.4);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glEnd();

                //output layer 
                glPointSize(20.0);
                glBegin(GL_POINTS);
                glColor4f(0.0, 0.0, 1.0, 1.0);
                glVertex3f(0.2, 0.35, 1.2);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, live_transparency_line);
                glVertex3f(0.1 + b, 0.1 + a, 0.8);
                glVertex3f(0.2, 0.35, 1.2);
                glVertex3f(0.2, 0.35, 1.2);
                glEnd();

            }
        }
    }
}

void displaynetwork(GLFWwindow* window)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(-1.0, -0.75, -3.5); // -1.6 for scaling of 2.3
    // Red color used to draw.
    glColor3f(0.8, 0.2, 0.1);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glScalef(2.0, 2.0, 2.0);

    float dead_transparency_line = 0.08;
    float live_transparency_line = 0.15;
    float a, b, c;
    for (a = 0; a <= 0.5; a = a + 0.1)
    {
        for (b = 0; b <= 0.5; b = b + 0.1)
        {
            for (c = 0; c <= 0.5; c = c + 0.1)
            {
                //Input Layer 
                glPointSize(15.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.1 + a, 0.0);
                glEnd();

                //First Hidden Layer Plane 1 
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                glVertex3f(0.1 + b, 0.1 + a, 0.0);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glVertex3f(0.1 + b, 0.1 + c, 0.4);
                glEnd();

                //First Hidden Layer Plane 2
                if (c < 0.47)
                {
                    glPointSize(3.0);
                    glBegin(GL_POINTS);
                    glVertex3f(0.1 + b, 0.1 + a, 0.0);
                    glVertex3f(0.13 + b, 0.13 + c, 0.42);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                    glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                    glVertex3f(0.1 + b, 0.1 + a, 0.0);
                    glVertex3f(0.13 + b, 0.13 + c, 0.42);
                    glVertex3f(0.13 + b, 0.13 + c, 0.42);
                    glEnd();
                }

                //First Hidden Layer Plane 3
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glVertex3f(0.1 + b, 0.1 + a, 0.0);
                glVertex3f(0.07 + b, 0.07 + c, 0.42);
                glVertex3f(0.07 + b, 0.07 + c, 0.42);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                glVertex3f(0.1 + b, 0.1 + a, 0.0);
                glVertex3f(0.07 + b, 0.07 + c, 0.42);
                glVertex3f(0.07 + b, 0.07 + c, 0.42);
                glEnd();

                //First Hidden Layer Plane 4
                if (c < 0.44)
                {
                    glPointSize(3.0);
                    glBegin(GL_POINTS);
                    glVertex3f(0.1 + b, 0.1 + a, 0.0);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                    glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                    glVertex3f(0.1 + b, 0.1 + a, 0.0);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glVertex3f(0.17 + b, 0.16 + c, 0.44);
                    glEnd();
                }

                //Second Hidden Layer Plane 1 
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                glVertex3f(0.1 + b, 0.1 + a, 0.4);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glEnd();

                //Second Hidden Layer Plane 2
                if (c < 0.47)
                {
                    glPointSize(3.0);
                    glBegin(GL_POINTS);
                    glVertex3f(0.1 + b, 0.1 + a, 0.42);
                    glVertex3f(0.13 + b, 0.13 + c, 0.82);
                    glVertex3f(0.13 + b, 0.13 + c, 0.82);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                    glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                    glVertex3f(0.1 + b, 0.1 + a, 0.0);
                    glVertex3f(0.13 + b, 0.13 + c, 0.82);
                    glVertex3f(0.13 + b, 0.13 + c, 0.82);
                    glEnd();
                }

                //Output Layer
                glPointSize(3.0);
                glBegin(GL_POINTS);
                glColor4f(1.0, 1.0, 1.0, 0.05);
                glVertex3f(0.1 + b, 0.35, 1.2);
                glVertex3f(0.1 + b, 0.35, 1.2);
                glEnd();
                glBegin(GL_LINE_LOOP);
                glColor4f(1.0, 1.0, 1.0, dead_transparency_line);
                glVertex3f(0.1 + b, 0.1 + c, 0.8);
                glVertex3f(0.1 + a, 0.35, 1.2);
                glVertex3f(0.1 + a, 0.35, 1.2);
                glEnd();
            }
        }
    }

    if (flag == true)
    {
        //Inut image '1'
        glPointSize(15.0);
        glBegin(GL_POINTS);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex3f(0.3, 0.2, 0.0);
        glVertex3f(0.3, 0.3, 0.0);
        glVertex3f(0.3, 0.4, 0.0);
        glVertex3f(0.3, 0.5, 0.0);
        glVertex3f(0.3, 0.6, 0.0);
        glVertex3f(0.4, 0.5, 0.0);
        glVertex3f(0.2, 0.2, 0.0);
        glVertex3f(0.3, 0.2, 0.0);
        glVertex3f(0.4, 0.2, 0.0);
        glEnd();

        //Highlighting the active neurons 
        highlight_lines(0.3, 0.2, 0.0, live_transparency_line);
        highlight_lines(0.3, 0.3, 0.0, live_transparency_line);
        highlight_lines(0.3, 0.4, 0.0, live_transparency_line);
        highlight_lines(0.3, 0.5, 0.0, live_transparency_line);
        highlight_lines(0.3, 0.6, 0.0, live_transparency_line);
        highlight_lines(0.4, 0.5, 0.0, live_transparency_line);
        highlight_lines(0.2, 0.2, 0.0, live_transparency_line);
        highlight_lines(0.3, 0.2, 0.0, live_transparency_line);
        highlight_lines(0.4, 0.2, 0.0, live_transparency_line);
    }
    //Flushing the whole output
    glFlush();
    // sawp buffers called because we are using double buffering 
    glfwSwapBuffers(window);
}

void reshapenetwork(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    float projMatrix[16];
    glhPerspectivef2(projMatrix, 40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    //gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glMultMatrixf(projMatrix);  // Load the manually created matrix

    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void idlenetwork(GLFWwindow* window)
{
    yRotated += 0.05;
    displaynetwork(window);
}


int main(int argc, char** argv)
{
    //Initialize GLUT
    glfwInit();

    //double buffering used to avoid flickering problem in animation
    // window size
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1350, 950, "GP", nullptr, nullptr);
    glewInit();
    glfwMakeContextCurrent(window);
    // create the window 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    yRotated = 40;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    while (!glfwWindowShouldClose(window))
    {
        //glutDisplayFunc(displaynetwork);
        //glutReshapeFunc(reshapenetwork);
        //glutIdleFunc(idlenetwork);
        //Let start glut loop
        //glutTimerFunc(100, check, 0);
        //glutMainLoop();
        displaynetwork(window);
        reshapenetwork(1350, 950);
        idlenetwork(window);
        glfwPollEvents();
    }
    //Assign  the function used in events

    return 0;
}