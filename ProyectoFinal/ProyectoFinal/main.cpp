//
//  main.cpp
//  3D_3
//
//  Created by Isaac Tellez and Paul Virueña on 17/10/18.
//  Copyright © 2018 Paul Virueña Iturriaga. All rights reserved.
//
/*
 * Proyecto final de Gráficas por Computadora
 */

//#include <windows.h>  // for MS Windows
#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

// Global variables
char title[] = "Proyecto Final";
int w = 1600;
int h = 900;
GLfloat angleSph = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]
GLboolean d = true;
int numSph = 2; //variable de prueba
bool tSph = true;
bool cSph = false;
struct cube{
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float trans;
    float large;
};
struct sphere{
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float trans;
    float radio;
};
struct ellipsoid{
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float trans;
    float radio;
};
vector<cube> cubes;
vector<sphere> spheres;
vector<ellipsoid> ellipsoids;

void createCube();
void createSphere();
void createEllipsoid();

void keyboardPressed(unsigned char key, int x, int y)
{
     switch(key) {
     case 'a':
             createCube();
             break;
     case '2':
     case '3':
     case  27:   // ESC
     exit(0);
     }
}

void mouseClick(int button, int state, int x, int y)
{
    cout<<button;
    cout<<state;
    cout<<"x: "<<x;
    cout<<"y: "<<y<<endl;
}

cube newCube(float cR, float cG, float cB, float x, float y, float z, float t, float l){
    
    cube myCube;    // = {cR, cG, cB, x, y, z, t, l};
    myCube.colorR = cR;
    myCube.colorG = cG;
    myCube.colorB = cB;
    myCube.positionX = x;
    myCube.positionY = y;
    myCube.positionZ = z;
    myCube.trans = t;
    myCube.large = l;
    return myCube;
}

sphere newSphere(float cR, float cG, float cB, float x, float y, float z, float t, float r){
    sphere mySphere;    // = {cR, cG, cB, x, y, z, t, r};
    mySphere.colorR = cR;
    mySphere.colorG = cG;
    mySphere.colorB = cB;
    mySphere.positionX = x;
    mySphere.positionY = y;
    mySphere.positionZ = z;
    mySphere.trans = t;
    mySphere.radio = r;
    return mySphere;
}

ellipsoid newEllipsoid(float cR, float cG, float cB, float x, float y, float z, float t, float r){
    ellipsoid myEllipsoid;  // = {cR, cG, cB, x, y, z, t, r};
    myEllipsoid.colorR = cR;
    myEllipsoid.colorG = cG;
    myEllipsoid.colorB = cB;
    myEllipsoid.positionX = x;
    myEllipsoid.positionY = y;
    myEllipsoid.positionZ = z;
    myEllipsoid.trans = t;
    myEllipsoid.radio = r;
    return myEllipsoid;
}

void drawSphere(float x, float y, float z) {
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
    //glColor3d(1, 0, 0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    /*angleSph += 0.2f;
     
     if(tSph){
     glTranslatef(1, 0, 0);
     }
     if(cSph){
     
     }*/
}

void drawEllipsoid(float x, float y, float z) {
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
    glColor3d(0, 0, 1);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.75, 0.35, 0.35);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
    /*angleSph += 0.2f;
     
     if(tSph){
     glTranslatef(1, 0, 0);
     }
     if(cSph){
     
     }*/
}

void drawCube(float x, float y, float z) {
    // Render a pyramid consists of 4 triangles
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
    //glColor3d(0, 1, 0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(1.0);
    glPopMatrix();
        /*angleSph += 0.2f;
     
     if(tSph){
     glTranslatef(1, 0, 0);
     }
     if(cSph){
     
     }*/
}

void createCube(){
    int rCR, rCG, rCB, rX, rY, rZ;
    rCR = rand()%(2);
    rCG = rand()%(2);
    rCB = rand()%(2);
    rX = (rand()%(101)) + (-50);
    rY = (rand()%(81)) + (-40);
    rZ = (rand()%(21)) * -1;
    cube c = newCube(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 0, 1);
    cubes.push_back(c);
    cout<<'z: '<<rZ<<endl;
}

void createSphere(){
    int rCR, rCG, rCB, rX, rY, rZ;
    rCR = rand()%(2);
    rCG = rand()%(2);
    rCB = rand()%(2);
    cout << "R: " << rCR << " G: " << rCG << " B: " << rCB << endl;
    rX = rand()%(4-(-4) + 1) + (-4);
    rY = rand()%(3- (-3) + 1) + (-3);
    rZ = (rand()%(99-0 + 1))*-1;
    sphere s = newSphere(rCR, rCG, rCB, rX, rY, rZ, 0, 1);
    spheres.push_back(s);
}

void createEllipsoid(){
    int rCR, rCG, rCB, rX, rY, rZ;
    rCR = rand()%(2);
    rCG = rand()%(2);
    rCB = rand()%(2);
    cout << "R: " << rCR << " G: " << rCG << " B: " << rCB << endl;
    rX = (rand()%(101)) + (-50);
    rY = (rand()%(81)) + (-40);
    rZ = (rand()%(21)) * -1;
    ellipsoid e = newEllipsoid(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 0, 1);
    ellipsoids.push_back(e);
}

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LESS);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
 whenever the window needs to be re-painted. */

void display() {
    float i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    
    //viewport menu figures
    glViewport(0, 0, 300, h);
    if (h == 0) h = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)300 / (GLfloat)h;
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    
    // Set up orthographic projection view [NEW]
    if (300 >= h) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 0.1, 100);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-1.5, 1.5, -1.5 / aspect, 1.5 / aspect, 0.1, 100);
    }
    
    //menu static figures
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCube(0.0f, 0.0f, -6.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawSphere(0.0f, -2.0f, -6.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(0.5f, 0.0f, 1.f, 0.0f);
    drawEllipsoid(0.0f, 2.0f, -6.0f);
    
    //Viewport stripes scene
    glViewport(300, 150, w-300, h-150);
    if (h == 0) h = 1;                // To prevent divide by 0
    GLfloat aspect1 = (GLfloat)(w-300) / (GLfloat)(h-150);
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    
    // Set up orthographic projection view [NEW]
    if (300 >= h) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        glOrtho(-1.0 * aspect1, 1.0 * aspect1, -1.0, 1.0, 0.1, 100);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-8.0, 8.0, -8.0 / aspect1, 8.0 / aspect1, 0.1, 100);
    }
    /*
    //Viewport command menu
    glViewport(0, 0, w-300, h-150);
    if (h == 0) h = 1;                // To prevent divide by 0
    GLfloat aspect2 = (GLfloat)(w-300) / (GLfloat)(h-150);
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    
    // Set up orthographic projection view [NEW]
    if (300 >= h) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        glOrtho(-1.0 * aspect2, 1.0 * aspect2, -1.0, 1.0, 0.1, 100);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-8.0, 8.0, -8.0 / aspect2, 8.0 / aspect2, 0.1, 100);
    }*/
    
    //The black stripes are at z = -50
    glColor3f(0.0f, 0.0f, 0.0f);
    for (i = -5.0f; i < 5; i = i+0.5) {
        glBegin(GL_QUADS);
        glVertex3f(i+0.25f, -5.0f, -10.0f);
        glVertex3f(i, -5.0f, -10.0f);
        glVertex3f(i, 5.0f, -10.0f);
        glVertex3f(i+0.25f,  5.0f, -10.0f);
        glEnd();
    }
    
    //Ploting figures
    for (int i = 0; i<cubes.size(); i++) {
        glColor3f(cubes[i].colorR, cubes[i].colorG, cubes[i].colorB);
        drawCube(cubes[i].positionX, cubes[i].positionY, cubes[i].positionZ);
    }
    
    for (int i = 0; i<spheres.size(); i++) {
        glColor3f(spheres[i].colorR, spheres[i].colorG, spheres[i].colorB);
        drawCube(spheres[i].positionX, spheres[i].positionY, spheres[i].positionZ);
    }
    
    for (int i = 0; i<ellipsoids.size(); i++) {
        glColor3f(ellipsoids[i].colorR, ellipsoids[i].colorG, ellipsoids[i].colorB);
        drawCube(ellipsoids[i].positionX, ellipsoids[i].positionY, ellipsoids[i].positionZ);
    }
    /*
     glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
     // Render a color-cube consisting of 6 quads with different colors
     glLoadIdentity();                 // Reset the model-view matrix
     glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
     //glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
     
     glLoadIdentity();
     glTranslatef(0, 0.0, 0.0);
     glPushMatrix();
     glutSolidCube(0.5);
     glPopMatrix();*/
    
    
    // Render a ellipsoid
    //glLoadIdentity();
    //glTranslatef(-1.5f, 0.0f, -6.0f);
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);
    /*drawSphere(-1.5f, 0.0f, -6.0f);
     if(d == true){
     drawSphere(-1.4f, 0.1f, -6.1f);
     }
     if(d==true){
     drawSphere(-1.6f, 0.2f, -6.2f);
     }
     //drawSphere(-1.6f, 0.2f, -6.2f);
     
     for(int i=0;i<numSph;i++){
     drawSphere(-1.5f+(0.2*i), 0.0f+(0.2*i), -6.0f+(0.2*i));
     }*/
    //glPushMatrix();
    //glTranslatef(0, 0.0, 0.0);
    //glutWireSphere(1.5, 50, 50);
    /*glPushMatrix();
     glTranslatef(0, 0.0, 0.0);
     glScalef(0.5, 0.5, 1);
     glutSolidSphere(1.5, 50, 50);*/
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    /*
     // Update the rotational angle after each refresh [NEW]
     angleSph += 0.2f;
     angleCube -= 0.15f;*/
    
}

void sphere() {
    
}



/* Called back when timer expired [NEW] */
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
        glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 0.1, 100);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-6.0, 6.0, -6.0 / aspect, 6.0 / aspect, 0.1, 100);
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(w, h);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    srand(time(0));
    createCube();
    createCube();
    createCube();
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutKeyboardFunc(keyboardPressed);
    glutMouseFunc(mouseClick);
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
