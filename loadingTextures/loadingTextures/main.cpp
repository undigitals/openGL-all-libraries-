#include <iostream>
#include "BitmapReader.h"
#include <GLUT/glut.h>
#include <cmath>
#include <stdio.h>


using namespace std;

//camera settings
float ex=0, ey=0, ez=20, cx=0, cy=0, cz=-1;
//Texture variable
GLuint Texture;
//object parameter
float angle=0;
float anglex = 0;
bool Rotation = false;
bool UpDown = false;
bool move = false;

void Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(ex, ey, ez, 0, 0, 0, 0, 1, 1);
    glRotatef(anglex*50, 1, 0, 0);
    glRotatef(angle*50, 0, 1, 0);
    glScalef(3, 3, 3);
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
    for(int i =0;i<4;i++){
        glPushMatrix();
        glRotatef(90*i, 0, 1, 0);
        glTranslatef(0, 0, -1);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-1, -1, 0);
        
            glTexCoord2f(1, 0);
            glVertex3f(1, -1, 0);
        
            glTexCoord2f(1, 1);
            glVertex3f(1, 1, 0);
        
            glTexCoord2f(0, 1);
            glVertex3f(-1, 1, 0);
        glEnd();
        glPopMatrix();
    }
    
    for (int i=0; i<2;i++){
        glPushMatrix();
        glRotatef(180*i+90, 1, 0, 0);
        glTranslatef(0, 0, -1);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-1, 1, 0);
        
            glTexCoord2f(1, 0);
            glVertex3f(1, -1, 0);
        
            glTexCoord2f(1, 1);
            glVertex3f(1, 1, 0);
        
            glTexCoord2f(0, 1);
            glVertex3f(-1, 1, 0);
        glEnd();
        glPopMatrix();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void Resize( int w, int h){
    if(h==0) h=1;
    float aspect = w*1.0/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, aspect, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}


int prev_x=0;
int prev_y=0;
void Mouse (int btn, int sts, int x, int y){
    Rotation = (btn-GLUT_MIDDLE_BUTTON) || (sts- GLUT_DOWN);
    Rotation = !Rotation;
    if(Rotation) prev_x = x;
    
    UpDown = (btn-GLUT_MIDDLE_BUTTON) || (sts- GLUT_DOWN);
    UpDown = !UpDown;
    if(UpDown) prev_y = y;
    
    move = (btn-GLUT_RIGHT_BUTTON) || (sts-GLUT_DOWN);
    move = !move;
    if(move) prev_y=y;
}

void Motion(int x, int y){
    if(Rotation) angle +=-0.015*(x-prev_x);
    
    if(UpDown) anglex+=0.015*(y-prev_y);
    
    if(move) ez += 0.1*(prev_y-y);
    
    prev_y = y;
    prev_x = x;
}

GLuint LoadTexture(char* filename){
    GLuint ID;
    BitmapReader textureData(filename);
    
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, <#GLint border#>, <#GLenum format#>, <#GLenum type#>, <#const GLvoid *pixels#>);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    return ID;
}

void Keyboard (unsigned char key, int x, int y){
    char file[80];
    if(key == ' '){
        cout<<"Enter Texture Location";
        cin.get(file,79);
        Texture = LoadTexture(file);
        fflush(stdin);
    }
}

int main (int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(820, 100);
    glutInitWindowSize(500, 400);
    glutCreateWindow("Render");
    
    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutKeyboardFunc(Keyboard);
    
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    return 0;
}

























