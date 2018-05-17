#include <GL/glew.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>

/*
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();             //clear the matrix
        //viewing transformation
    gluLookAt (0.0, 0.0, 5.0, 2.0, 0.0, 0.0, 1.0, 1.0, -1.0);
    //glTranslatef(0.0, 0.0, -5.0);
    //glRotatef(90.0, 0.0, 1.0, 0.0)
    glScalef (1.0, 2.0, 1.0);      //modeling transformation
    glutWireCube (1.0);
    glFlush ();
    
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // projection tranformation just like lens of the camera
    // perspective projection->glFrustum
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    //gluPerspective(30.0, 2.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
 */

/*
// BLENDING EFFECTS
#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4
static float solidZ = MAXZ;
static float transparentZ = MINZ;
static GLuint sphereList, cubeList;

static void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat position[] = { 0.5, 0.5, 1.0, 0.0 };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    sphereList = glGenLists(1);
    glNewList(sphereList, GL_COMPILE);
    glutSolidSphere (0.4, 16, 16);
    glEndList();
    
    cubeList = glGenLists(1);
    glNewList(cubeList, GL_COMPILE);
    glutSolidCube(0.6);
    glEndList();
}

void display(void)
{
    GLfloat mat_solid[] = { 0.75, 0.75, 0.0, 1.0 };
    GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
    GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix ();
    glTranslatef (-0.15, -0.15, solidZ);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();
    
    glPushMatrix ();
    glTranslatef (0.15, 0.15, transparentZ);
    glRotatef (15.0, 1.0, 1.0, 0.0);
    glRotatef (30.0, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    glCallList (cubeList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
                 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
                 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void animate(void)
{
    if (solidZ <= MINZ || transparentZ >= MAXZ)
        glutIdleFunc(NULL);
    else {
        solidZ -= ZINC;
        transparentZ += ZINC;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'a':
        case 'A':
            solidZ = MAXZ;
            transparentZ = MINZ;
            glutIdleFunc(animate);
            break;
        case 'r':
        case 'R':
            solidZ = MAXZ;
            transparentZ = MINZ;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
 */


// anti-aliasing effect
static float rotAngle = 0.;

/*  Initialize antialiasing for RGBA mode, including alpha
 *  blending, hint, and line width.  Print out implementation
 *  specific info on line width granularity and width.
 */
/*
void init(void)
{
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(5);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

 //Draw 2 diagonal lines to form an X
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f (0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(-rotAngle, 0.0, 0.0, 0.1);
    glBegin (GL_LINES);
    glVertex2f (-0.5, 0.5);
    glVertex2f (0.5, -0.5);
    glEnd ();
    glPopMatrix();
    
    glColor3f (0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(rotAngle, 0.0, 0.0, 0.1);
    glBegin (GL_LINES);
    glVertex2f (0.5, 0.5);
    glVertex2f (-0.5, -0.5);
    glEnd ();
    glPopMatrix();
    
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D (-1.0, 1.0,
                    -1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w);
    else
        gluOrtho2D (-1.0*(GLfloat)w/(GLfloat)h,
                    1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'r':
        case 'R':
            rotAngle += 20.;
            if (rotAngle >= 360.) rotAngle = 0.;
            glutPostRedisplay();
            break;
        case 27:  //Escape Key
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (200, 200);
    glutCreateWindow (argv[0]);
    init();
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutDisplayFunc (display);
    glutMainLoop();
    return 0;
}
*/

static GLint fogMode;

static void init(void)
{
    GLfloat position[] = { 0.5, 0.5, 3.0, 0.0 };
    
    glEnable(GL_DEPTH_TEST);
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {
        GLfloat mat[3] = { 0.1745, 0.01175, 0.01175 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
        mat[0] = 0.61424; mat[1] = 0.04136; mat[2] = 0.04136;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
        mat[0] = 0.727811; mat[1] = 0.626959; mat[2] = 0.626959;
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6*128.0);
    }
    
    /* Fog Effect */
    glEnable(GL_FOG);
    {
        GLfloat fogColor[4] = {0.5,0.5,0.5,1.0};
        fogMode = GL_EXP;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.35);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 5.0);
        
    }
    
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

static void renderSphere(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();
}

/* display() draws 5 spheres at different z positions.
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderSphere(-2., -0.5, -1.0);
    renderSphere(-1., -0.5, -2.0);
    renderSphere(0., -0.5, -3.0);
    renderSphere(1., -0.5, -4.0);
    renderSphere(2., -0.5, -5.0);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w,
                2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.5*(GLfloat)w / (GLfloat)h,
                2.5*(GLfloat)w / (GLfloat)h, -2.5, 2.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'f':
        case 'F':
            if (fogMode == GL_EXP) {
                fogMode = GL_EXP2;
                printf("Fog mode is GL_EXP2\n");
            }
            else if (fogMode == GL_EXP2) {
                fogMode = GL_LINEAR;
                printf("Fog mode is GL_LINEAR\n");
            }
            else if (fogMode == GL_LINEAR) {
                fogMode = GL_EXP;
                printf("Fog mode is GL_EXP\n");
            }
            glFogi(GL_FOG_MODE, fogMode);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
