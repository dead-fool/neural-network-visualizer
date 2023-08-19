


#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <neuralNetworkParser.h>

#include <stdio.h>
#define USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include "iostream"
#include <time.h>
static double yPosDelta = 0.0;
static double xPosDelta = 0.0;
static double xRotationDelta = 0.0;
static double zRotationDelta = 0.0;
static int select = 0;
std::vector<std::vector<float> > input_activation;
std::vector<std::vector<float> > fc1_activation;
std::vector<std::vector<float> > fc2_activation;
std::vector<std::vector<float> > fc3_activation;
std::vector<std::vector<float> > fc4_activation;
std::vector<std::vector<float> > output_activation;



//static vector< vector<float> > input_activation;

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
    ymax = znear * tanf(fovyInDegrees * 3.14159 / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}


using namespace std;

bool flag = false;
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

void displayPoint(GLfloat x, GLfloat y, GLfloat z, GLfloat size)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor4f(1.0, 1.0, 1.0, 0.05);
    glVertex3f(x, y, z);
    glEnd();
}

void displayLine(GLfloat a1, GLfloat b1, GLfloat c1, GLfloat a2, GLfloat b2, GLfloat c2, GLfloat transparency, GLfloat R, GLfloat G, GLfloat B) {
    glBegin(GL_LINE_LOOP);
    glColor4f(R,G,B, transparency * 0.001);
    glVertex3f(a1, b1, c1);
    glVertex3f(a2, b2, c2);
    glVertex3f(a2, b2, c2);
    glEnd();
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
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    glScalef(0.5, 0.5, 0.5);
    glEnable(GL_BLEND);
    float dead_transparency_line = 0.2;
    float live_transparency_line = 0.5;
    float a, b, c;



    //output
    
    

    int a1 = 27, b1 = 0;

    for (a = 0; a <= 1.35; a = a + 0.05)
    {
        b1 = 0;
        for (b = 0; b <= 1.35; b = b + 0.05)
        {
            //Input Layer 
            glPointSize(5.0);
            glBegin(GL_POINTS);
            glColor4f(0.0, 0.0, input_activation[select][a1 * 28 + b1], 1.0);
            glVertex3f(0.05 + b, (0.05 + a), 0.0);
            glEnd();
            b1++;
            //input_activation[0][a1 * 28 +b1]
        }
        a1--;
    }
        
    a1 = 31, b1 = 0;
        
    //fc1
    for (a = 0.275; a < 1.05; a += 0.025)
    {
        b1 = 0;
        for (b = 0.275; b < 1.05; b += 0.025)
        {
            //fc1 
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glColor4f(0.0, fc1_activation[select][a1 * 32 + b1], 0.0, 1);
            glVertex3f(0.025 + b, (0.025 + a), 0.75);
            glEnd();
            b1++;
        }
        a1--;
    }
    a1 = 31;
    //fc2
    for (a = 0.275; a < 1.05; a += 0.025)
    {
        b1 = 0;
        for (b = 0.275; b < 1.05; b += 0.025)
        {
            //fc1 
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glColor4f(0.0, fc2_activation[select][a1 * 32 + b1], 0.0, 1);
            glVertex3f(0.025 + b, (0.025 + a), 1.5);
            glEnd();
            b1++;
        }
        a1--;
    }

    a1 = 31;
    //fc3
    for (a = 0.275; a < 1.05; a += 0.025)
    {
        b1 = 0;
        for (b = 0.275; b < 1.05; b += 0.025)
        {
            //fc3 
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glColor4f(fc3_activation[select][a1 * 32 + b1], 0.0, 0.0, 1);
            glVertex3f(0.025 + b, (0.025 + a), 2.25);
            glEnd();
            b1++;
        }
        a1--;
    }

    a1 = 0;
    //fc4

    for (a = 0; a < 1.35; a += 0.135)
    {
        glPointSize(3.0);
        glBegin(GL_POINTS);
        glColor4f(0.0, 1.0, fc4_activation[0][a1], 1.0);
        glVertex3f(a, 0.675, 3);
        glEnd();
        a1++;
    }

    //output
    a1 = 0;
    for (a = 0; a < 1.35; a += 0.135)
    {
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor4f(1.0, output_activation[select][a1], 1.0, 1.0);
        glVertex3f(a, 0.675, 3.75);
        glEnd();
        a1++;
    }

    if (flag == true)
    {
        // display the networks
        for (int i = 0; i < 28; i++) {
            for (int i1 = 0; i1 < 28; i1++) {
                for (int j = 0; j < 32; j++) {
                    for (int j1 = 0; j1 < 32; j1++) {
                        if (fc1_activation[select][(31 - j) * 32 + j1] > 0.4) {
                            float a1 = i * 0.05 + 0.05, b1 = (i1 + 1) * 0.05;
                            float a2 = (j + 1) * 0.025 + 0.275, b2 = (j1 + 1) * 0.025 + 0.275;
                            displayLine(b1, a1, 0, a2, b2, 0.75, input_activation[select][(27 - i) * 28 + i1], 1, 0, 1);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 32; i++) {
            for (int i1 = 0; i1 < 32; i1++) {
                for (int j = 0; j < 32; j++) {
                    for (int j1 = 0; j1 < 32; j1++) {
                        if (fc2_activation[select][(31 - j) * 32 + j1] > 0.4) {
                            float a1 = i * 0.025 + 0.025 + 0.275, b1 = (i1 + 1) * 0.025 + 0.275;
                            float a2 = (j + 1) * 0.025 + 0.275, b2 = (j1 + 1) * 0.025 + 0.275;
                            displayLine(b1, a1, 0.75, a2, b2, 1.5, fc1_activation[select][(31 - i) * 32 + i1], 0, 1, 1);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 32; i++) {
            for (int i1 = 0; i1 < 32; i1++) {
                for (int j = 0; j < 32; j++) {
                    for (int j1 = 0; j1 < 32; j1++) {
                        if (fc3_activation[select][(31 - j) * 32 + j1] > 0.4) {
                            float a1 = i * 0.025 + 0.025 + 0.275, b1 = (i1 + 1) * 0.025 + 0.275;
                            float a2 = (j + 1) * 0.025 + 0.275, b2 = (j1 + 1) * 0.025 + 0.275;
                            displayLine(b1, a1, 1.5, a2, b2, 2.25, fc2_activation[select][(31 - i) * 32 + i1], 0, 0, 1);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 32; i++) {
            for (int i1 = 0; i1 < 32; i1++) {
                for (int j = 0; j < 10; j++) {
                    if (fc4_activation[select][j] > 0.4) {
                        float a1 = i * 0.025 + 0.025 + 0.275, b1 = (i1 + 1) * 0.025 + 0.275;
                        float a2 = (j) * 0.135, b2 = 0.675;
                        displayLine(b1, a1, 2.25, a2, b2, 3, fc3_activation[select][(31 - i) * 32 + i1] * 5, 0, 1, 1);
                    }
                }
            }
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (output_activation[select][j] < 0.3) {
                    float a1 = i * 0.025 + 0.025 + 0.275, b1 = 0.675;
                    float a2 = (j) * 0.135, b2 = 0.675;
                    displayLine(a1, b1, 3, a2, b2, 3.75, fc4_activation[select][i] * 100, 0.5, 1, 0.7);
                }
            }
        }
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
    /*yRotated += 0.05;
    if (leftMousePressed) {
        yRotated += yPosDelta;
    }
    */
    displaynetwork(window);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        flag = !flag;
    }
    
    if (action = GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
        select++;
    }
    
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*
    yRotated = yRotated - (ypos - yPosPrev) * 0.05;
    std::cout << yRotated << std::endl;
    */
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    yRotated += yoffset * 2.0;
}


int main(int argc, char** argv)
{
    NpyArray inputLayer = getSelectedNumpyArray("input", "activity.npz");
    NpyArray fc1 = getSelectedNumpyArray("fc1", "activity.npz");
    NpyArray fc2 = getSelectedNumpyArray("fc2", "activity.npz");
    NpyArray fc3 = getSelectedNumpyArray("fc3", "activity.npz");
    NpyArray fc4 = getSelectedNumpyArray("fc4", "activity.npz");
    NpyArray output = getSelectedNumpyArray("output", "activity.npz");

    vector <float> temp1;
    
    for (int slice_data =0; slice_data < 100; slice_data++ )
    {
        //input layer
        for (int x = 0; x < 28 * 28; x++)
        {
            temp1.push_back(inputLayer.DataVector<float>()[slice_data * 28*28 + x]);
            
        }
        input_activation.push_back(temp1);
        temp1.clear();
        
        //fc1
        // 
        for (int x = 0; x < 32 * 32; x++)
        {
            temp1.push_back(fc1.DataVector<float>()[slice_data * 32*32 + x]);

        }
        fc1_activation.push_back(temp1);
        temp1.clear();

        
        //fc2
        // 
        for (int x = 0; x < 32 * 32; x++)
        {
            temp1.push_back(fc2.DataVector<float>()[slice_data * 32*32 + x]);

        }
        fc2_activation.push_back(temp1);
        temp1.clear();
        
        //fc3
        // 
        for (int x = 0; x < 32 * 32; x++)
        {
            temp1.push_back(fc3.DataVector<float>()[slice_data * 32*32 + x]);

        }
        fc3_activation.push_back(temp1);
        temp1.clear();

        //cout << fc4.Shape()[2] << endl;

        
        
        //fc4
        // 
        //vector<float> temp11;
        //std::cout << fc4.Shape()[2] << endl;
        std::cout << slice_data << endl;
        float max = INT_MIN;

        for (int x = 0; x < 10; x++)
        {
            float val = fc4.DataVector<float>()[slice_data * 10 + x];
            if (val > max) {
                max = val;
            }
            temp1.push_back(val);
        }

        if (max != 0.0) {
            for (int x = 0; x < 10; x++)
            {
                temp1.push_back(temp1[x] / max);
            }
        }

        std::cout << slice_data << endl;
        fc4_activation.push_back(temp1);
        temp1.clear();
        
        //output
        // 

        max = INT_MIN;
        for (int x = 0; x < 10; x++)
        {
            float val = output.DataVector<float>()[slice_data * 10 + x];
            if (val > max) {
                max = val;
            }
            temp1.push_back(val);
        }

        if (max != 0.0) {
            for (int x = 0; x < 10; x++)
            {
                temp1.push_back(temp1[x] / max);
            }
        }
        output_activation.push_back(temp1);
        temp1.clear();
        
        
    }
    
    // 
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
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        //glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwPollEvents();
    }
    //Assign  the function used in events

    return 0;
}

