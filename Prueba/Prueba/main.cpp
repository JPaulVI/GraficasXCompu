#include <GLUT/glut.h>

static int width = 1600;
static int height = 900;
static int alpha = 0.01;
static int beta = 0.01;
static int gamma = 0.01;
//https://stackoverflow.com/questions/726379/how-to-use-multiple-viewports-in-opengl/1327092#1327092

static float cubeAngle = 10;

void creaFigurasMenu() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //creo cubo
    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    //-----------------------------------------------------
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScaled(1.5, 1.5, 1.50);
    //aqui sirve para rotar el cubo
    glRotatef(20+cubeAngle, 1, 0, 0);
    glRotatef(20 + cubeAngle, 0, 1, 0);
    glRotatef(20 + cubeAngle, 0, 0, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(1);
    glPopMatrix();
    cubeAngle += 10;
    //-----------------------------------------------------
    
    glPushMatrix();
    glTranslatef(0.0, -3.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    GLfloat lightColor0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightPos0[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
    
    
    //el visor empleado en la visualización
    glViewport(5, 5, width/3 , height);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    //los primeros tres parametros representan el punto en el cual se està fijando la visualizaciòn
    //los siguientes tres parámetros indican hacia que punto se está observando (así generando el vector V)
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1);
    glRotatef(alpha, 1.0, 0, 0); //rotate alpha around the x axis
    glRotatef(beta, 0, 1.0, 0); //rotate beta around the y axis
    glRotatef(gamma, 0, 0, 1.0);
    creaFigurasMenu();
    
    
    
    
    glViewport(5+width/3, 0, width/3*2-10, height);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -2.0);
    glutWireTeapot(1);
    
    
    
    glFlush();
}

static void reshape(int w, int h) {
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(50, 0);
    glutCreateWindow(argv[0]);
    glClearColor(0.3, 0.6, 0.9, 0.0);
    //glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
