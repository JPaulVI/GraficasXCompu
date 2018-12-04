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
//title of the proyect
char title[] = "Proyecto Final";
//width and height of the window
int w = 1600;
int h = 900;
//limits of scene
int xmin = -6;
int xmax = 6;
int ymin= -5;
int ymax = 5;
int zmin = 0;
int zmax = -20;
int zint = -10;
//angle variables
GLfloat angleSph = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]
GLboolean d = true;
//?
bool tSph = true;
bool cSph = false;
bool isCubeMoving = false;
bool isEllipsoidMoving = false;
bool isSphereMoving = false;
char fig = 's';
//menu commands text
//string str[];
char e[] = "E        Escalar";
char m[] = "M       Mover";
char c[] = "C        Cambiar de color";
char r[] = "R        Rotar";
char t[] = "T        Transparente";
char esc[] = "ESC    Salir";

struct cube{
    float colorR;
    float colorG;
    float colorB;
    float positionX;
    float positionY;
    float positionZ;
    float trans;
    float large;
    float dx;
    float dy;
    float dz;
    float dt;
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
    float dx;
    float dy;
    float dz;
    float dt;
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
    float dx;
    float dy;
    float dz;
    float dt;
};
vector<cube> cubes;
vector<sphere> spheres;
vector<ellipsoid> ellipsoids;

void createCube();
void createSphere();
void createEllipsoid();
void setMov(char fig);

void keyboardPressed(unsigned char key, int x, int y)
{
     switch(key) {
         case 'c':
             createCube();
             break;
         case 's':
             createSphere();
             break;
         case 'e':
             createEllipsoid();
             break;
         case 'm':
             setMov(fig);
             break;
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
    
    if(button == 0 && state == 0){
        if(x<300){
            if(y<290){
                fig = 'e';
            } else{
                if(y<500){
                    fig = 'c';
                }else{
                    fig = 's';
                }
            }
        }
        cout << fig << endl;
    }
    
}

cube newCube(float cR, float cG, float cB, float x, float y, float z, float t, float l){
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
    myCube.dt = 0;
    return myCube;
}

sphere newSphere(float cR, float cG, float cB, float x, float y, float z, float t, float r){
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

ellipsoid newEllipsoid(float cR, float cG, float cB, float x, float y, float z, float t, float r){
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
    myEllipsoid.dt = 0;
    return myEllipsoid;
}

void drawSphere(float x, float y, float z) {
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
    //glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.5, 50, 50);
    //glPopMatrix();
    /*angleSph += 0.2f;
     
     if(tSph){
     glTranslatef(1, 0, 0);
     }
     if(cSph){
     
     }*/
}

void drawEllipsoid(float x, float y, float z) {
    //glRotatef(angleSph, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
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
    glPushMatrix();
    //glColor3f(0, 1,0);
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
}

void createSphere(){
    int rCR, rCG, rCB, rX, rY, rZ;
    rCR = rand()%(2);
    rCG = rand()%(2);
    rCB = rand()%(2);
    cout << "R: " << rCR << " G: " << rCG << " B: " << rCB << endl;
    rX = (rand()%(101)) + (-50);
    rY = (rand()%(81)) + (-40);
    rZ = (rand()%(21)) * -1;
    sphere s = newSphere(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 0, 1);
    spheres.push_back(s);
}

void createEllipsoid(){
    int rCR, rCG, rCB, rX, rY, rZ;
    rCR = rand()%(2);
    rCG = rand()%(2);
    rCB = rand()%(2);
    rX = (rand()%(101)) + (-50);
    rY = (rand()%(81)) + (-40);
    rZ = (rand()%(21)) * -1;
    ellipsoid e = newEllipsoid(rCR, rCG, rCB, rX*0.1, rY*0.1, rZ, 0, 1);
    ellipsoids.push_back(e);
}

/*
void renderBitmapString(float x, float y,char str){
    const char *c;
    glRasterPos2f(x, y);
    c = str.
    for (c=str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
}
*/

void setMov(char fig){

    if(fig == 'c'){
        isCubeMoving = !isCubeMoving;
        cout<<"isCubeMoving"<<isCubeMoving<<endl;
        for(int i=0;i<cubes.size();i++){
            cubes[i].dx = rand()%(101)*0.001;
            cubes[i].dy = rand()%(101)*0.001;
            //cubes[i].dy = 0;
            cubes[i].dz = 0;
        }
    }
    if(fig == 'e'){
        isEllipsoidMoving = !isEllipsoidMoving;
        for(int i=0;i<ellipsoids.size();i++){
            ellipsoids[i].dx = 0;
            ellipsoids[i].dy = rand()%(101)*0.001;
            ellipsoids[i].dz = rand()%(101)*0.001;
            //ellipsoids[i].dz = 0;
        }
    }
    if(fig == 's'){
        isSphereMoving = !isSphereMoving;
        for(int i=0;i<spheres.size();i++){
            spheres[i].dx = rand()%(101)*0.001;
            spheres[i].dy = rand()%(101)*0.001;
            spheres[i].dz = rand()%(101)*0.001;
        }
    }
    
}

void setRot(char fig){
    
    if(fig == 'c'){
        for(int i=0;i<cubes.size();i++){
            cubes[i].dt = rand()%(101)*0.1;
        }
    }
    if(fig == 'e'){
        for(int i=0;i<ellipsoids.size();i++){
            ellipsoids[i].dt = rand()%(101)*0.1;
        }
    }
    if(fig == 's'){
        for(int i=0;i<spheres.size();i++){
            spheres[i].dt = rand()%(101)*0.1;
        }
    }
    
}

void movCube(cube &c){
    
    if(c.positionX<xmin || c.positionX>xmax){
        c.dx = (-c.dx);
    }
    
    if(c.positionY<ymin || c.positionY>ymax){
        c.dy = -c.dy;
    }
    
    c.positionX = c.positionX + c.dx;
    cout<<"delta x: "<<c.dx<<endl;
    cout<<"pos x: "<<c.positionX<<endl;
    c.positionY += c.dy;
    
    //glTranslatef(c.positionX+c.dx, c.positionY+c.dy, c.positionZ);
    
}

void movEllipsoid(ellipsoid &e){
    
    if(e.positionY<ymin || e.positionY>ymax){
        e.dy = -e.dy;
    }
    
    if(e.positionZ<zmin || e.positionZ>zmax){
        e.dz = -e.dz;
    }
    
    e.positionY += e.dy;
    e.positionZ += e.dz;
    
    //glTranslatef(e.positionX, e.positionY+e.dy, e.positionZ+e.dz);
    
}

void movSphere(sphere &s){
    
    if(s.positionX<xmin || s.positionX>xmax){
        s.dx = -s.dx;
    }
    
    if(s.positionY<ymin || s.positionY>ymax){
        s.dy = -s.dy;
    }
    
    if(s.positionZ<zmin || s.positionZ>zmax){
        s.dz = -s.dz;
    }
    
    s.positionX += s.dx;
    s.positionY += s.dy;
    s.positionZ += s.dz;
    
    //glTranslatef(s.positionX+s.dx, s.positionY+s.dy, s.positionZ+s.dz);
    
}

void addDeltas(int x){
    
    if(isCubeMoving){
        for(int i=0; i<cubes.size(); i++){
            movCube(cubes[i]);
        }
    }
    
    if(isEllipsoidMoving){
        for(int i=0; i<ellipsoids.size(); i++){
            movEllipsoid(ellipsoids[i]);
        }
    }
    
    if(isSphereMoving){
        for(int i=0; i<spheres.size(); i++){
            movSphere(spheres[i]);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, addDeltas, 0);
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
    
    glMatrixMode(GL_MODELVIEW);  // To operate on the Projection matrix
    glLoadIdentity();
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, arreglo, );
    //glLightfv(GL_LIGHT0, GL_DIFUSE, arreglo)
    //glLightfv(GL_LIGHT0, GL_POSITION, arreglo)
    
    GLfloat dirVector [ ] = {1.0, 0.0, 0.0};
    GLfloat light1PosType [ ] = {2.0, 0.0, 3.0, 1.0};
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, dirVector);
    glLightfv (GL_LIGHT1,GL_POSITION, light1PosType);
    glEnable (GL_LIGHT1);
    GLfloat light2PosType [ ] = {0.0, 1.0, 0.0, 0.0};
    glLightfv (GL_LIGHT2, GL_DIFFUSE, dirVector);
    glLightfv (GL_LIGHT1,GL_POSITION, light2PosType);
    glEnable (GL_LIGHT2);
    
    //viewport menu figures
    glViewport(0, 0, 300, h-150);
    GLfloat aspect = (GLfloat)300 / (GLfloat)(h-150);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-1.5, 1.5, -1.5 / aspect, 1.5 / aspect, 0.1, 100);
    
    //menu static figures
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(0.5f, 0.0f, 1.f, 0.0f);
    drawEllipsoid(0.0f, 2.0f, -6.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCube(0.0f, 0.0f, -6.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawSphere(0.0f, -2.0f, -6.0f);
    
    //Viewport stripes scene
    glViewport(300, 150, w-300, h-150);
    GLfloat aspect1 = (GLfloat)(w-300) / (GLfloat)(h-150);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-8.0, 8.0, -8.0 / aspect1, 8.0 / aspect1, 0.1, 100);
    
    //The black stripes are at z = -50
    glColor3f(0.0f, 0.0f, 0.0f);
    for (i = -6.0f; i < 6; i = i+0.5) {
        glBegin(GL_QUADS);
        glVertex3f(i+0.25f, -5.0f, -10.0f);
        glVertex3f(i, -5.0f, -10.0f);
        glVertex3f(i, 5.0f, -10.0f);
        glVertex3f(i+0.25f,  5.0f, -10.0f);
        glEnd();
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Ploting figures
    for (int i = 0; i<cubes.size(); i++) {
        glColor3f(cubes[i].colorR, cubes[i].colorG, cubes[i].colorB);
        glPushMatrix();
        drawCube(cubes[i].positionX, cubes[i].positionY, cubes[i].positionZ);
        glPopMatrix();
    }
    
    for (int i = 0; i<spheres.size(); i++) {
        glColor3f(spheres[i].colorR, spheres[i].colorG, spheres[i].colorB);
        glPushMatrix();
        drawSphere(spheres[i].positionX, spheres[i].positionY, spheres[i].positionZ);
        glPopMatrix();
    }
    
    for (int i = 0; i<ellipsoids.size(); i++) {
        glColor3f(ellipsoids[i].colorR, ellipsoids[i].colorG, ellipsoids[i].colorB);
        glPushMatrix();
        drawEllipsoid(ellipsoids[i].positionX, ellipsoids[i].positionY, ellipsoids[i].positionZ);
        glPopMatrix();
    }
    
    //Viewport command menu
    glViewport(0, 0, w, 150);
    GLfloat aspect2 = (GLfloat)(w) / (GLfloat)(150);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    glOrtho(-8.0, 8.0, -8.0 / aspect2, 8.0 / aspect2, 0.1, 100);
    
    /*
    glFontBegin(&font);
    glScalef(8.0, 8.0, 8.0);
    glTranslatef(30, 30, 0);
    glFontTextOut("Test", 5, 5, 0);
    glFontEnd();
    glFlush();*/
    
    /*
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(50,100,"Font Rendering - Programming Techniques");
    //renderBitmapString(300,220, (void*)font, s);
    renderBitmapString(300,240,"Esc - Quit");
    glPopMatrix();
     */
    
    /*
    //set the position of the text in the window
    glRasterPos3f(x3, y3, z3);
    //get the length of the string to display
    int len = (int)strlen(string);
    //loop to display character by character
    for (int i1 = 0; i1 < len; i1++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i1]);
  */
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
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
        glOrtho(-3.0 *aspect,3.0*aspect, -3.0, 3.0, 0.1, 100);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        glOrtho(-6.0, 6.0, -6.0/aspect, 6.0/aspect, 0.1, 100);
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
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    //glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutTimerFunc(25, addDeltas, 0);
    glutKeyboardFunc(keyboardPressed);
    glutMouseFunc(mouseClick);
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}

