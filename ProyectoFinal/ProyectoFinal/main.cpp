//
//  main.cpp
//  3D_3
//
//  Created by Isaac Tellez and Paul Virueña on 17/10/18.
//  Copyright © 2018 Isaac Tellez and Paul Virueña Iturriaga. All rights reserved.
//
/*
 * Proyecto final de Gráficas por Computadora
 */

//Code based on ntu.edu.sg
//http://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_examples.html
//#include <windows.h>  // for MS Windows
#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

// Global variables
//Title of the proyect
char title[] = "Proyecto Final";
//Width and height of the window
int w = 1440;
int h = 900;
//Limits of scene
int xmin = -8;
int xmax = 8;
int ymin = -5;
int ymax = 5;
int zmin = -20;
int zmax = 0;
int zint = -10;
//Level of transparency and scale
double levelS = 1;
double levelT = 0;
// Refresh interval in milliseconds
int refreshMills = 15;
GLboolean d = true;
//Booleans to know if a figure is to be moved or spinned
bool isCubeMoving = false;
bool isEllipsoidMoving = false;
bool isSphereMoving = false;
bool isCubeSpinning = false;
bool isEllipsoidSpinnig = false;
bool isSphereSpinning = false;
//Character to indicate the figure to apply an action
//Set on sphere by default
char fig = 's';

//Structures with properties of figures
//R, G, B.- Color of the figure
//X, Y, Z.- Position of the figure
//angle.- Current angle (not used)
//trans.- Transparency value
//large/radio.- Size-related property
//dx, dy, dz, dt.- Represents the change in any of the given properties (x, y, z, orientation)
struct cube {
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float angle;
    float trans;
    float large;
    float dx;
    float dy;
    float dz;
    float dt;
};

struct sphere {
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float trans;
    float radio;
    float dx;
    float dy;
    float dz;
    float dt;
};

struct ellipsoid {
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float angle;
    float trans;
    float radio;
    float dx;
    float dy;
    float dz;
    float dt;
};

//Vectors to keep all figures of the same type
vector<cube> cubes;
vector<sphere> spheres;
vector<ellipsoid> ellipsoids;

//Declaration of some methods to be used
//C++ requires them to be declared before the first use
void createCube();
void createSphere();
void createEllipsoid();
void setMov(char fig);
void setRot(char fig);
void setColors(char fig);
void setScale(char fig, double s);
void setTrans(char fig, double s);

//Method to read keyboard input
//Functionality is implemented as stated on the project requirements
//The number keys need to be pressed before using either scale or transparency functions
void keyboardPressed(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
            createCube();
            break;
        case 's':
            createSphere();
            break;
        case 'a':
            createEllipsoid();
            break;
        case 'c':
            setColors(fig);
            break;
        case 'm':
            setMov(fig);
            break;
        case 'r':
            setRot(fig);
            break;
        case 'e':
            setScale(fig, levelS);
            break;
        case 't':
            setTrans(fig, levelT);
            break;
        case '1':
            levelS = 0.5;
            levelT = 0.1;
            break;
        case '2':
            levelS = 0.6;
            levelT = 0.2;
            break;
        case '3':
            levelS = 0.7;
            levelT = 0.3;
            break;
        case '4':
            levelS = 0.8;
            levelT = 0.4;
            break;
        case '5':
            levelS = 0.9;
            levelT = 0.5;
            break;
        case '6':
            levelS = 1.2;
            levelT = 0.6;
            break;
        case '7':
            levelS = 1.3;
            levelT = 0.7;
            break;
        case '8':
            levelS = 1.4;
            levelT = 0.8;
            break;
        case '9':
            levelS = 1.5;
            levelT = 0.9;
            break;
        case  27:   // ESC
            exit(0);
            break;
    }
}

//Method to read mouse input
//Used the position of the left menu figures to determine the type of figure each action will apply to
void mouseClick(int button, int state, int x, int y)
{
    //Test prints to verify mouse clicks, including button pressed and (x,y) position
    cout << button;
    cout << state;
    cout << "x: " << x;
    cout << "y: " << y << endl;
    
    if (button == 0 && state == 0) {
        if (x<300) {
            if (y<300) {
                fig = 'e';
            }
            else {
                if (y<620) {
                    fig = 'c';
                }
                else {
                    fig = 's';
                }
            }
        }
    }
    
}

//Constructors for each type of figure
cube newCube(float cR, float cG, float cB, float x, float y, float z, float t, float l) {
    cube myCube;
    myCube.colorR = cR;
    myCube.colorG = cG;
    myCube.colorB = cB;
    myCube.positionX = x;
    myCube.positionY = y;
    myCube.positionZ = z;
    myCube.trans = t;
    myCube.large = l;
    myCube.dx = 0;
    myCube.dy = 0;
    myCube.dz = 0;
    myCube.dt = 1;
    myCube.angle = 0;
    return myCube;
}

sphere newSphere(float cR, float cG, float cB, float x, float y, float z, float t, float r) {
    sphere mySphere;
    mySphere.colorR = cR;
    mySphere.colorG = cG;
    mySphere.colorB = cB;
    mySphere.positionX = x;
    mySphere.positionY = y;
    mySphere.positionZ = z;
    mySphere.trans = t;
    mySphere.radio = r;
    mySphere.dx = 0;
    mySphere.dy = 0;
    mySphere.dz = 0;
    mySphere.dt = 0;
    return mySphere;
}

ellipsoid newEllipsoid(float cR, float cG, float cB, float x, float y, float z, float t, float r) {
    ellipsoid myEllipsoid;
    myEllipsoid.colorR = cR;
    myEllipsoid.colorG = cG;
    myEllipsoid.colorB = cB;
    myEllipsoid.positionX = x;
    myEllipsoid.positionY = y;
    myEllipsoid.positionZ = z;
    myEllipsoid.trans = t;
    myEllipsoid.radio = r;
    myEllipsoid.dx = 0;
    myEllipsoid.dy = 0;
    myEllipsoid.dz = 0;
    myEllipsoid.dt = 1;
    myEllipsoid.angle = 0;
    return myEllipsoid;
}

//Drawing code for each type of figure
//Sphere doesn't receive a theta (angle) value as spinning is not defined for this type
void drawSphere(float x, float y, float z, float r) {
    r = (double)r;
    glTranslatef(x, y, z);
    glutSolidSphere(r, 50, 50);
}

//For the rotation of both ellipsoid and cube, a translation to the origin is performed first,
//then the rotation and lastly it is placed on its right position
void drawEllipsoid(float x, float y, float z, float t, float r) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(t, 0, 1, 1);
    glTranslatef(0, 0, 0);
    glScalef(0.75, 0.35, 0.35);
    glutSolidSphere(r, 50, 50);
    glPopMatrix();
}

void drawCube(float x, float y, float z, float t, float l) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(t, 1, 1, 0);
    glTranslatef(0, 0, 0);
    glutSolidCube(l);
    glPopMatrix();
}

//Generate random values for each figure parameter
//Colors are generated in a range from 0.0 to 0.5
//rX, rY and rZ are generated in a range of values inside the scene
void createCube() {
    int rCR, rCG, rCB, rX, rY, rZ;
    //rCR = rand() % (2);
    //rCG = rand() % (2);
    //rCB = rand() % (2);
    rCR = (rand() % (51))*.1;
    rCG = (rand() % (51))*.1;
    rCB = (rand() % (51))*.1;
    rX = (rand() % (101)) + (-50);
    rY = (rand() % (81)) + (-40);
    rZ = (rand() % (21)) * -1;
    cube c = newCube(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 1, 1);
    cubes.push_back(c);
}

void createSphere() {
    int rCR, rCG, rCB, rX, rY, rZ;
    //rCR = rand() % (2);
    //rCG = rand() % (2);
    //rCB = rand() % (2);
    rCR = (rand() % (51))*.1;
    rCG = (rand() % (51))*.1;
    rCB = (rand() % (51))*.1;
    rX = (rand() % (101)) + (-50);
    rY = (rand() % (81)) + (-40);
    rZ = (rand() % (21)) * -1;
    sphere s = newSphere(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 1, 0.5);
    spheres.push_back(s);
}

void createEllipsoid() {
    int rCR, rCG, rCB, rX, rY, rZ;
    //rCR = rand() % (2);
    //rCG = rand() % (2);
    //rCB = rand() % (2);
    rCR = (rand() % (51))*.1;
    rCG = (rand() % (51))*.1;
    rCB = (rand() % (51))*.1;
    rX = (rand() % (101)) + (-50);
    rY = (rand() % (81)) + (-40);
    rZ = (rand() % (21)) * -1;
    ellipsoid e = newEllipsoid(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 1, 1);
    ellipsoids.push_back(e);
}

//Method that receives a character for determining which figure to apply movement to
//Movement is set as specified on the project requirements
//'c'.- Cubes only have x and y movement
//'e'.- Ellipsoids have y and z movement
//'s'.- Ellipsoids have movement on all axes
void setMov(char fig) {
    if (fig == 'c') {
        isCubeMoving = !isCubeMoving;
        for (int i = 0;i<cubes.size();i++) {
            cubes[i].dx = rand() % (101)*0.001;
            cubes[i].dy = rand() % (101)*0.001;
            //cubes[i].dy = 0;
            cubes[i].dz = 0;
        }
    }
    if (fig == 'e') {
        isEllipsoidMoving = !isEllipsoidMoving;
        for (int i = 0;i<ellipsoids.size();i++) {
            ellipsoids[i].dx = 0;
            ellipsoids[i].dy = rand() % (101)*0.001;
            ellipsoids[i].dz = rand() % (101)*0.001;
            //ellipsoids[i].dz = 0;
        }
    }
    if (fig == 's') {
        isSphereMoving = !isSphereMoving;
        for (int i = 0;i<spheres.size();i++) {
            spheres[i].dx = rand() % (101)*0.001;
            spheres[i].dy = rand() % (101)*0.001;
            spheres[i].dz = rand() % (101)*0.001;
        }
    }
    
}

//Determine whether or not a figure is to spin
void setRot(char fig) {
    
    if (fig == 'c') {
        isCubeSpinning = !isCubeSpinning;
    }
    if (fig == 'e') {
        isEllipsoidSpinnig = !isEllipsoidSpinnig;
    }
    
}

//Method to randomize color on figures
void setColors(char fig) {
    if (fig == 'c') {
        for (int i = 0;i<cubes.size();i++) {
            cubes[i].colorR = rand() % (2);
            cubes[i].colorG = rand() % (2);
            cubes[i].colorB = rand() % (2);
        }
    }
    if (fig == 'e') {
        for (int i = 0;i<ellipsoids.size();i++) {
            ellipsoids[i].colorR = rand() % (2);
            ellipsoids[i].colorG = rand() % (2);
            ellipsoids[i].colorB = rand() % (2);
        }
    }
    if (fig == 's') {
        for (int i = 0;i<spheres.size();i++) {
            spheres[i].colorR = rand() % (2);
            spheres[i].colorG = rand() % (2);
            spheres[i].colorB = rand() % (2);
        }
    }
}

//Method to scale figures depending on the number key pressed
void setScale(char fig, double s) {
    if (fig == 'c') {
        for (int i = 0;i<cubes.size();i++) {
            cubes[i].large = cubes[i].large*s;
        }
    }
    if (fig == 'e') {
        for (int i = 0;i<ellipsoids.size();i++) {
            ellipsoids[i].radio = ellipsoids[i].radio*s;
        }
    }
    if (fig == 's') {
        isSphereMoving = !isSphereMoving;
        for (int i = 0;i<spheres.size();i++) {
            spheres[i].radio = spheres[i].radio*s;
        }
    }
}

//Method to scale figures depending on the number key pressed
void setTrans(char fig, double s) {
    if (fig == 'c') {
        for (int i = 0;i<cubes.size();i++) {
            cubes[i].trans = s;
        }
    }
    if (fig == 'e') {
        for (int i = 0;i<ellipsoids.size();i++) {
            ellipsoids[i].trans = s;
        }
    }
    if (fig == 's') {
        isSphereMoving = !isSphereMoving;
        for (int i = 0;i<spheres.size();i++) {
            spheres[i].trans = s;
        }
    }
}

//Mov methods are in charge of determining the direction of movement of the figures,
//depending on its current position and direction
//If its at the edge of the visible scene, it changes direction
void movCube(cube &c) {
    
    if (c.positionX<xmin || c.positionX>xmax) {
        c.dx = (-c.dx);
    }
    
    if (c.positionY<ymin || c.positionY>ymax) {
        c.dy = -c.dy;
    }
    
    c.positionX = c.positionX + c.dx;
    c.positionY = c.positionY + c.dy;
}

void movEllipsoid(ellipsoid &e) {
    
    if (e.positionY<ymin || e.positionY>ymax) {
        e.dy = -e.dy;
    }
    
    if (e.positionZ<zmin || e.positionZ>zmax) {
        e.dz = -e.dz;
    }
    
    e.positionY = e.positionY + e.dy;
    e.positionZ = e.positionZ + e.dz;
}

void movSphere(sphere &s) {
    
    if (s.positionX<xmin || s.positionX>xmax) {
        s.dx = -s.dx;
    }
    
    if (s.positionY<ymin || s.positionY>ymax) {
        s.dy = -s.dy;
    }
    
    if (s.positionZ<zmin || s.positionZ>zmax) {
        s.dz = -s.dz;
    }
    
    s.positionX = s.positionX + s.dx;
    s.positionY = s.positionY + s.dy;
    s.positionZ = s.positionZ + s.dz;
}

//Rot methods are in charge of determining the direction and magnitude of spin
//It is always in one direction and the axes are determined in the "draw" methods
void rotCube(cube &c) {
    
    c.dt = c.dt + rand() % (101)*0.1;
    
}

void rotEllipsoid(ellipsoid &e) {
    
    e.dt = e.dt + rand() % (101)*0.1;
    
}

//Method responsible for updating the movement parameters of every figure on the scene
//Using glutTimerFunc, this method is being updated every 25 milliseconds
void addDeltas(int x) {
    
    if (isCubeMoving) {
        for (int i = 0; i<cubes.size(); i++) {
            movCube(cubes[i]);
        }
    }
    
    if (isCubeSpinning) {
        for (int i = 0; i<cubes.size(); i++) {
            rotCube(cubes[i]);
        }
    }
    
    if (isEllipsoidMoving) {
        for (int i = 0; i<ellipsoids.size(); i++) {
            movEllipsoid(ellipsoids[i]);
        }
    }
    
    if (isEllipsoidSpinnig) {
        for (int i = 0; i<ellipsoids.size(); i++) {
            rotEllipsoid(ellipsoids[i]);
        }
    }
    
    if (isSphereMoving) {
        for (int i = 0; i<spheres.size(); i++) {
            movSphere(spheres[i]);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(25, addDeltas, 0);
}

/* Initialize OpenGL Graphics */
void initGL() {
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

//Code extracted from programming-techniques.com and adapted to our work
//Receives a position (x,y) and a string to be displayed
//Uses glutBitmapCharacter to generate a bitmap with the specified font and size
//https://www.programming-techniques.com/2012/05/font-rendering-in-glut-using-bitmap.html
void renderBitmapString(float x, float y, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(300, w, w - 150, 0);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
//end of external code

/* Handler for window-repaint event. Called back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    float i;
    
    glEnable(GL_NORMALIZE);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_MODELVIEW);  // To operate on the Projection matrix
    glLoadIdentity();
    
    //Lights position and color
    GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat Color0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Position0[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    GLfloat Color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat Position1[] = { 0.0f, 10.0f, 0.0f, 0.0f  };
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, Color0);
    glLightfv(GL_LIGHT0, GL_POSITION, Position0);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Color1);
    glLightfv(GL_LIGHT1, GL_POSITION, Position1);
    
    //Viewport for left menu figures
    glViewport(0, 0, 300, h);
    GLfloat aspect = (GLfloat)300 / (GLfloat)(h);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-1.5, 1.5, -1.5 / aspect, 1.5 / aspect, 0.1, 100);
    
    //Left menu static figures
    glColor3f(1.0f, 0.0f, 0.0f);
    drawEllipsoid(0.0f, 2.5f, -6.0f, 0, 1);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCube(0.0f, 0.0f, -6.0f, 0, 1);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawSphere(0.0f, -2.5f, -6.0f, 0.5);
    
    //Viewport for main scene
    glViewport(300, 150, w - 300, h - 150);
    GLfloat aspect1 = (GLfloat)(w - 300) / (GLfloat)(h - 150);
    
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-8.0, 8.0, -8.0 / aspect1, 8.0 / aspect1, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Plotting figures by iterating over figure vectors and getting every parameter needed
    for (int i = 0; i<cubes.size(); i++) {
        glColor4f(cubes[i].colorR, cubes[i].colorG, cubes[i].colorB, cubes[i].trans);
        glPushMatrix();
        drawCube(cubes[i].positionX, cubes[i].positionY, cubes[i].positionZ, cubes[i].dt, cubes[i].large);
        glPopMatrix();
    }
    
    for (int i = 0; i<spheres.size(); i++) {
        glColor4f(spheres[i].colorR, spheres[i].colorG, spheres[i].colorB, spheres[i].trans);
        glPushMatrix();
        drawSphere(spheres[i].positionX, spheres[i].positionY, spheres[i].positionZ, spheres[i].radio);
        glPopMatrix();
    }
    
    for (int i = 0; i<ellipsoids.size(); i++) {
        glColor4f(ellipsoids[i].colorR, ellipsoids[i].colorG, ellipsoids[i].colorB, ellipsoids[i].trans);
        glPushMatrix();
        drawEllipsoid(ellipsoids[i].positionX, ellipsoids[i].positionY, ellipsoids[i].positionZ, ellipsoids[i].dt, ellipsoids[i].radio);
        glPopMatrix();
    }
    
    //Code for black stripes
    //The black stripes are at z = -50
    glColor3f(0.0f, 0.0f, 0.0f);
    for (i = -9.0f; i < 9; i = i + 0.5) {
        glBegin(GL_QUADS);
        glVertex3f(i + 0.25f, -6.0f, -10.0f);
        glVertex3f(i, -6.0f, -10.0f);
        glVertex3f(i, 6.0f, -10.0f);
        glVertex3f(i + 0.25f, 6.0f, -10.0f);
        glEnd();
    }
    
    //Viewport command menu
    glViewport(300, 0, w - 300, 150);
    GLfloat aspect2 = (GLfloat)(w - 300) / (GLfloat)(150);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-8.0, 8.0, -8.0 / aspect2, 8.0 / aspect2, 0.1, 100);
    
    //menu commands text
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(350, 700, "e - Escalar (se necesita un nivel de escalado)");
    renderBitmapString(350, 550, "c - Cambiar de color de figura");
    renderBitmapString(350, 400, "q - Agregar elipsoide");
    renderBitmapString(350, 250, "a - Agregar cubo");
    renderBitmapString(350, 100, "z - Agregar esfera");
    renderBitmapString(800, 700, "m - Mover figura");
    renderBitmapString(800, 550, "r - Rotar figura");
    renderBitmapString(800, 400, "t - Cambia transparencia (se necesita un nivel de transparencia)");
    renderBitmapString(800, 250, "ESC - Salir del programa");
    
    glPopMatrix();
    resetPerspectiveProjection();
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Called back when timer expired */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    
    // Set up orthographic projection view [NEW]
    if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        glOrtho(-3.0 *aspect, 3.0*aspect, -3.0, 3.0, 0.1, 100);
    }
    else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-6.0, 6.0, -6.0 / aspect, 6.0 / aspect, 0.1, 100);
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(w, h);           // Set the window's initial width & height
    glutInitWindowPosition(50, 50);     // Position the window's initial top-left corner
    glutCreateWindow(title);            // Create window with the given title
    srand(time(0));                     //Function used for random values
    glutDisplayFunc(display);           // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);           // Register callback handler for window re-size event
    initGL();                           // Our own OpenGL initialization
    glutTimerFunc(25, addDeltas, 0);    // First timer call every 25 ms
    glutKeyboardFunc(keyboardPressed);  //
    glutMouseFunc(mouseClick);          //
    glutMainLoop();                     // Enter the infinite event-processing loop
    return 0;
}
