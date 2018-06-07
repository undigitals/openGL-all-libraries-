#include <stdio.h>
#include <stdlib.h>
//#include <SFML/audio.hpp>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>

static double time = 0;  // Run_time variable
static double time2 = 0; // Jap_time variable
static double time3 = 0; // Rocket_time variable
static double time4 = 0; // ground_time variable
static double time6 = 0; // exit_time variable

GLfloat R_Arm_x = 0; // 오른쪽 어깨 right shoulder
GLfloat R_Arm_y = 0; // 오른쪽 팔 right arm
GLfloat L_Arm_x = 0; // 왼쪽 어깨 left shouler
GLfloat L_Arm_y = 0; // 왼쪽 팔 left arm
GLfloat R_Leg_x = 0; // 오른 허벅지 right thigh
GLfloat R_Leg_y = 0; // 오른 종아리 right calf
GLfloat L_Leg_x = 0; // 왼 허벅지 left thigh
GLfloat L_Leg_y = 0; // 왼 종아리 left calf
GLfloat R = 0; // 왼쪽 로켓 펀치 움직임 변수 left rochet punch action variable
GLfloat R2 = 0;// 오른쪽 로켓 펀치 움직임 변수 right rochet punch action variable

GLUquadricObj* cyl;// 실린더 객체 선언 cylinder object

int a = 0; // x축 기준(값이 1일 때 x축을 기준으로 회전) x axis (when value is 1, then rotate according x axis)
int b = 0; // y축 기준(값이 1일 때 y축을 기준으로 회전) y axix (when value is 1, then rotate according y axis)
int c = 0; // z축 기준(값이 1일 때 z축을 기준으로 회전) z axix (when value is 1, then rotate according z axis)

static int flag = 0; // wireframe 모드와 solid rendering 모드 구분 변수 defining wireframe mode and solid rendering mode using flag variable
static int key = 0;  // 동작 모드와 색상 변경 변수 defining action mode and color mode variable

#define RUN        1
#define JAP        2
#define ROCKET    3
#define YUNA    4
#define EXIT    6

void glInit(void) { // 지엘 초기화 함수  GL initialization function
    glEnable(GL_DEPTH_TEST); // 깊이 테스팅 사용 using depth buffer
    glEnable(GL_NORMALIZE);  // 정규화 normalization
    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    /* According the angle of receiving light, make changes the color of robot */
    GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
    GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
    GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
    GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
    GLfloat position[] = { 400.0,300.0,-700.0,1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 검은색 background color (black)
    glMatrixMode(GL_PROJECTION);   // 모드 설정 configure mode
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 가시 범위 설정 configure view volume
}

void Draw_Color(int i) { // The function that change color
    if (i == RUN) {
        glColor3f(0.0, 1.0, 0.0);
    }
    else if (i == JAP) {
        glColor3f(1.0, 1.0, 0.0);
    }
    else if (i == ROCKET) {
        glColor3f(0.0, 1.0, 1.0);
    }
    else if (i == YUNA) {
        glColor3f(1.0, 0.0, 1.0);
    }
    else if (i == EXIT) {
        glColor3f(0.2, 0.2, 0.2);
    }
}

void Change_Wire_Or_Solid(int i) {          // 솔리드, 와이어 선택 select solid or wire
    if (flag == 1)
        gluQuadricDrawStyle(cyl, GLU_LINE); // 스타일을 와이어로 변경 change to wired robot
}
/*
 로봇 왼팔을 그리는 함수 Function to draw left arm
 */
void DrawL_Arm(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);       // 색 설정 configure color
    cyl = gluNewQuadric();   // 실린더 객체 생성 create cylinder object
    glRotatef(x, a, b, c);  // 파라미터 값만큼 회전 rotate
    glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해) rotate cylinder 90 degree
    glTranslatef(0.25, 0.0, 0.0);    // 왼쪽 어깨 시작점으로 이동 move to the starting point of left shoulder
    glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전 rotate 15 degree for left shoulder
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림 draw cylinder
}


void DrawL_Hand(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.22);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
    glPopMatrix();
}

void DrawL_HandRocket() {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0, 0, R);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}

void DrawR_Arm(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(x, a, b, c);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(-0.25, 0.0, 0.0);
    glRotatef(-15.0, 0.0, 1.0, 0.0);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);

}
/*
 right hand of robot
 */
void DrawR_Hand(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.22);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}

/*
 로봇 오른쪽 로켓트 함수 Function that right hand rocket
 */

void DrawR_HandRocket() {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0, 0, R2);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}
/*
 로봇 몸체를 그리는 함수 Draw body of robot
 */
void DrawBody(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);
    glPopMatrix();
}
/*
 로봇 왼쪽 허벅지를 그리는 함수 left thigh
 */
void DrawL_Legs(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.1, 0.0, 0.42);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);

}
/*
 로봇 왼쪽 종아리를 그리는 함수 Draw left calf
 */
void DrawL_foot(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(y, a, b, c);
    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 50, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
    glPopMatrix();
}
/*
 로봇 오른쪽 허벅지를 그리는 함수 right thigh
 */
void DrawR_Legs(int x, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(-0.1, 0.0, 0.42);
    glRotatef(x, a, b, c);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);

}
/*
 로봇 오른쪽 종아리를 그리는 함수 right calf
 */
void DrawR_foot(int y, int a, int b, int c) {
    glPushMatrix();
    Draw_Color(key);
    cyl = gluNewQuadric();

    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(y, a, b, c);

    Change_Wire_Or_Solid(flag);
    if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 15, 1);
    else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
    glPopMatrix();
}
/*
 로봇 목을 그리는 함수 Draw neck
 */
void Drawneck() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);//색 지정(흰색) white color
    cyl = gluNewQuadric();//실린더 객체 생성 create cylinder object
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -0.045);
    Change_Wire_Or_Solid(flag);
    gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);
    glPopMatrix();
}


// problem with wheels making translate f
void drawCar(){
    glPushMatrix();
        glPushMatrix();                   // body
        glScalef(2,.5,1);
        glColor3d(1.0,1.0,0.0);
        glutSolidCube(.5);
        glPopMatrix();
    
        glTranslatef(0,0,.25);
    
        glPushMatrix();
        glTranslatef(-.4,-.2, 0);
        //glutSolidTorus(.05,.1,8,8);     // wheel
        //glRotatef(45.0, 0, 1, 0);
    
        glTranslatef(.8,0,0);
        glRotatef(0.0 + time4 + 15, 0.0, 0.0, 1);
        glutSolidTorus(.05,.1,8,8);
        glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
        glColor3d(1.0,1.0,0.0);// wheel
        glPopMatrix();
    
        glTranslatef(0,0,-.5);
        glColor3d(1.0,1.0,0.0);
        glPushMatrix();
        glTranslatef(-.4, -.2, 1);
        glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
        glColor3d(1.0,1.0,0.0);
        glutSolidTorus(.05,.1,8,8);       // wheel
    
        glTranslatef(.8,0,1);
        glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
        glColor3d(1.0,1.0,0.0);
        //glutSolidTorus(.05,.1,8,8);       // wheel
        glPopMatrix();
        glPopMatrix();
    
    glPopMatrix();
    
    /* flush drawing routines to the window */
    glFlush();
}
void DrawGround() {
    Draw_Color(flag);//색깔 설정 color
    glTranslatef(0.0, -2.73, 0.0);
    glRotatef(45.0, 0, 1, 0);
    glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1);
    Change_Wire_Or_Solid(flag);
    gluSphere(cyl, 2.5, 30, 90);
}
/*
 로봇 머리를 그리는 함수 Function to draw head of robot
 로봇의 머리에 달려있는 뿔과 horn on the head
 로봇의 눈을 설정하였다. eyes of robot
 */
void DrawHead() {
    glTranslatef(0.0, 0.02, 0.0);//머리 시작점 head starting point
    glPushMatrix();// 처음 저장 좌표 다시 저장
    cyl = gluNewQuadric();
    Change_Wire_Or_Solid(flag);
    Draw_Color(key);//색깔 설정 color
    gluSphere(cyl, 0.20, 30, 10);//머리 그리기 draw head
    /*왼쪽 뿔 그리기 draw right horn */
    glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여) rotate
    glTranslatef(-0.16, 0.0, -0.22);//왼쪽 뿔 시작점 starting point of left horn
    glRotatef(35.0, 0.0, 1.0, 0.0);
    gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
    glPopMatrix();
    glPushMatrix();

    /*오른쪽 뿔 그리기 right horn */
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.16, 0.0, -0.22);
    glRotatef(-35.0, 0.0, 1.0, 0.0);
    gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
    glPopMatrix();
    glPushMatrix();

    /*왼쪽 눈 그리기left eye*/
    glTranslatef(-0.1, 0.1, 0.13);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(cyl, 0.03, 10, 10);

    glPopMatrix();
    glPushMatrix();

    /*오른쪽 눈 그리기right eye */
    glTranslatef(0.1, 0.1, 0.13);
    gluSphere(cyl, 0.03, 10, 10);
    glPopMatrix();
}
/*
 안드로이드 전체 모습을 그리는 함수 Draw the entire robot call each function
 */
void DrawAndroid() {
    DrawBody(0, 0, 0, 0); // call body function
    Drawneck(); // 목함수 호출 call neck function
    DrawHead(); // 머리 호출 call head function
    DrawR_Arm(R_Arm_x, 1, 0, 0);//우측팔뚝 right arm
    if (key == ROCKET) DrawR_HandRocket(); // 로켓모드일때 우측로켓호출 call right rocket function when it is rocket mode
    else DrawR_Hand(R_Arm_y, 1, 0, 0);  //우측팔호출 call right arm funciton
    DrawL_Arm(L_Arm_x, 1, 0, 0);   //좌측팔뚝 left arm
    if (key == ROCKET) DrawL_HandRocket(); // 로켓모드일때 우측로켓호출 call left rocket function when it is rocket mode
    else DrawL_Hand(L_Arm_y, 1, 0, 0);//좌측손호출  call left hand
    DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리 call left leg
    DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발 call left foot
    DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리 call right leg
    DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발    call right foot
}
/*
 로봇이 달리는 것을 표현한 함수. For running
 로봇의 관절이 움직이는 것을 표현했고,
 로봇이 달리면서 상,하,좌,우로 움직이는 모습을 표현했다.
 */
void Run() {
    //sndPlaySound(TEXT("C:\\sample1.wav"), SND_ASYNC | SND_NOSTOP); // if you have sound file you can apply here
    glLoadIdentity();//CTM 초기화
    /*
     기본적인 로봇의 움직임의 가속도는 sin() 함수를 통해 표현하였다
     또한 관절의 제한범위를 생각하여 abs() 함수를 통해 관절의 움직임을 제한하였다.
     */
    L_Arm_x = sin(time) * 80;           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
    R_Arm_x = -L_Arm_x;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
    R_Arm_y = -abs(int(sin(time) * 60 + 50));  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정)
    L_Arm_y = -abs(int(-sin(time) * 60 + 50)); //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정)

    R_Leg_y = abs(int(-sin(time) * 30 - 30));  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    L_Leg_y = abs(int(sin(time) * 30 - 30));   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    R_Leg_x = sin(time) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
    L_Leg_x = -R_Leg_x;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

    ////////////////display////////////////

    cyl = gluNewQuadric(); //실린더 객체 생성 cylinder object
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화 initrialization
    glMatrixMode(GL_MODELVIEW); //모드 설정 mode

    DrawGround();    //지면 호출
    glLoadIdentity();//CTM 초기화

    /*
     로봇이 달리면서 앞,뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
     */
    glRotatef(-230.0, 0, 1, 0);//y축으로 기울임
    glRotatef(abs(int(sin(time) * 16)), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
    glRotatef(sin(time) * 16, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

    /*
     로봇이 달리면서 상,하로 움직이는 것을 표현
     */
    float i = 0;
    i = abs(int(sin(time)*0.08)); //i변수값 설정
    glPushMatrix();// 처음 저장 좌표 다시 저장
    glTranslatef(0.0, i, 0); //변수 i만큼 로봇의 몸체가 Y축기준으로 움직임.

    glTranslatef(0.0, 0.5, 0.0);//최초 로봇의 위치
    DrawAndroid();
    glutSwapBuffers();
}

/*
 로봇이 잽을 날리는 것을 표현한 함수
 */
void Jap() {
    //sndPlaySound(TEXT("C:\\sample3.wav"), SND_ASYNC | SND_NOSTOP);
    glLoadIdentity();//CTM 초기화
  
    L_Arm_x = -90;
    R_Arm_x = -90;
    
    //left hand
    R = 2 * abs(int(-sin(time2)*0.2 - 0.2)) + 0.2;
    R2 = 2 * abs(int(sin(time2)*0.2 - 0.2)) + 0.2;

    ////////////////display////////////////

    cyl = gluNewQuadric(); //실린더 객체 생성
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
    glMatrixMode(GL_MODELVIEW); //모드 설정
    
    drawCar();
    glLoadIdentity();
    
    DrawGround(); //지면 호출
    glLoadIdentity(); //CTM 초기화

    glRotatef(-230.0, 0, 1, 0); //y축기준으로 회전

    glRotatef(sin(time) * 10, 0, 0, 1);//로봇의 좌,우 반동 표현(좌우로 10도 만큼 주기적인 움직임 설정)

    /*
     로봇이 잽을 날리면서 상,하로 움직이는 것을 표현
     */
    float j = 0;
    j = abs(int(sin(time2)*0.085));// j값 설정
    glPushMatrix();// 처음 저장 좌표 다시 저장
    glTranslatef(0.0, j, 0); //변수 j만큼 로봇의 몸체가 Y축기준으로 움직임.
    glTranslatef(0.0, 0.5, 0.0);//최초 위치
    DrawAndroid();
    glutSwapBuffers();
}

/*
 로봇이 퇴장할때 크기 변환을 표현한 함수
 */
void ex()
{
    //sndPlaySound(TEXT("C:\\sample5.wav"), SND_ASYNC | SND_NOSTOP);
    glLoadIdentity(); //CTM 초기화
    /*
     로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
     */
    L_Arm_x = (-40) + sin(time2) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
    R_Arm_x = (-80) - L_Arm_x;      //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
    R_Arm_y = -abs(int(cos(time2) * 10));  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
    L_Arm_y = -abs(int(-cos(time2) * 10));  //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

    R_Leg_y = abs(int(-sin(time) * 30 - 30));  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    L_Leg_y = abs(int(sin(time) * 30 - 30));  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    R_Leg_x = sin(time) * 60;           //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
    L_Leg_x = -R_Leg_x;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

    ////////////////display////////////////

    cyl = gluNewQuadric(); //실린더 객체 생성
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
    glMatrixMode(GL_MODELVIEW); //모드 설정

    glLoadIdentity(); //CTM 초기화
    glRotatef(-180, 0, 1, 0); //y축 기준으로 회전
    glRotatef(time6, 0, 0, 1); //time6 변수만큼 z축기준으로 회전

    glScalef(0.4 / (sin(time3)), 0.4 / (sin(time3)), 0.4 / (sin(time3))); //0.4의 크기에서 sin()를 통한 크기조절을 주기적으로 가함에따라

    glPushMatrix();// 처음 저장 좌표 다시 저장                                                              //멀어지고 가까워지는듯한 느낌을 표현
    glTranslatef(0.0, 0.5, 0.0);//최초 위치
    DrawAndroid();
    glutSwapBuffers();
}
/*
 김연아 선수의 모션을 취하는 함수
 */
void Show()
{
    //sndPlaySound(TEXT("C:\\sample4.wav"), SND_ASYNC | SND_NOSTOP);
    glLoadIdentity(); //CTM 초기화

    /*
     로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
     */
    L_Arm_x = (-40) + sin(time2) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
    R_Arm_x = (-80) - L_Arm_x;       //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
    R_Arm_y = -abs(int(cos(time2) * 10));  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
    L_Arm_y = -abs(int(-cos(time2) * 10)); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

    R_Leg_y = abs(int(-sin(time) * 30 - 30)); //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    L_Leg_y = abs(int(sin(time) * 30 - 30));  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
    R_Leg_x = sin(time) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
    L_Leg_x = -R_Leg_x;             //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

    ////////////////display////////////////

    cyl = gluNewQuadric(); //실린더 객체 생성
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
    glMatrixMode(GL_MODELVIEW); //모드 설정

    DrawGround(); //지면 호출
    glLoadIdentity(); //CTM 초기화
    glRotatef(-230.0, 0, 1, 0); //y축기준으로 회전

    /*
     로봇이 피겨동작시 몸이 틀어지는 것을 표현
     */
    glRotatef(sin(time) * 7, 0, 0, 1); //z축기준으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)
    glRotatef(sin(time) * 7, 0, 1, 0); //y축으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)

    //로봇 몸체 각도 조절
    glTranslatef(0.0, 0.18, 0.0); //y축으로 이동
    glRotatef(80, 1, 0, 0);        //x축 기준으로 회전

    glTranslatef(0.0, 0.5, 0.0);//최초 위치

    glPushMatrix(); // 처음 저장 위치

    DrawBody(0, 0, 0, 0); // 몸통 함수 호출

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    Drawneck(); // 목함수 호출

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    //머리 위치 설정
    glRotatef(-75, 1, 0, 0); //x축기준으로 회전(머리를 위쪽으로 돌리기)
    glTranslatef(0.0, -0.02, 0.0); //y축으로 이동 (머리 시작점)

    DrawHead(); // 머리 호출

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    //우측전체팔 위치 설정


    DrawR_Arm((R_Arm_y + 30), 1, 0, 0);  //우측팔호출
    DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0); //우측팔뚝

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    //좌측전체팔 위치 설정
    glTranslatef(0.0, -0.16, -0.04);//y축,z축으로 이동(좌측팔 시작점)
    glRotatef(40, 0, 0, 1);     //z축 기준으로 회전

    DrawL_Arm((L_Arm_y + 30), 1, 0, 0);   //좌측팔호출
    DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0);  //좌측팔뚝

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    //좌측전체 다리 위치 설정
    glTranslatef(0.0, -0.45, -0.25);//y축,z축으로 이동(좌측다리 시작점)
    glRotatef(-90, 1, 0, 0);  //x축 기준으로 회전

    DrawL_Legs(-30, 1, 0, 0);  //좌측다리
    DrawL_foot(10, 1, 0, 0);  //좌측종아리

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
    glPushMatrix();// 처음 저장 좌표 다시 저장

    //우측전체 다리 위치 설정
    glTranslatef(0.0, -0.5, -0.5);//y축,z축으로 이동(우측다리 시작점)
    glRotatef(-90, 1, 0, 0); //x축 기준으로 회전

    DrawR_Legs(160, 1, 0, 0);  //우측다리
    DrawR_foot(R_Leg_y, 1, 0, 0);  //우측종아리

    glPopMatrix(); // 처음 저장 좌표로 돌아 간다.

    glutSwapBuffers();
}
/*
 로봇이 로켓을 날리는 모습을 표현한 함수
 */
void Rocket() {
    //sndPlaySound(TEXT("C:\\sample2.wav"), SND_ASYNC | SND_NOSTOP);
    glLoadIdentity();

    L_Arm_x = -90;
    R_Arm_x = -90;
    
    //left hand
    R = 2 * abs(int(-sin(time2)*0.2 - 0.2)) + 0.2;
    R2 = 2 * abs(int(sin(time2)*0.2 - 0.2)) + 0.2;


    R_Leg_y = abs(int(-sin(time) * 30 - 30));
    L_Leg_y = abs(int(sin(time) * 30 - 30));
    R_Leg_x = sin(time) * 60;
    L_Leg_x = -R_Leg_x;

    ////////////////display////////////////

    cyl = gluNewQuadric(); //실린더 객체 생성
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
    glMatrixMode(GL_MODELVIEW); //모드 설정

    DrawGround(); //지면 호출

    glLoadIdentity(); //CTM 초기화
    glPushMatrix();// 처음 저장 좌표 다시 저장
    glRotatef(-230.0, 0, 1, 0); //y축 기준으로 회전

    /*
     로봇이 로켓을 쏠 때 상,하,좌,우로 몸을 트는 모습을 설정
     */
    glRotatef(-abs(int(sin(time) * 8)), 1, 0, 0); //x축으로 8도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
    glRotatef(sin(time) * 7, 0, 0, 1);       //z축으로 7도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

    /*
     로봇이 로켓을 날리며 몸을 튕기는 모습을 표현
     */
    float i = 0;
    i = abs(int(sin(time)*0.08)); //i값 설정
    glTranslatef(0.0, i, 0); //변수 i만큼 이동
    glTranslatef(0.0, 0.5, 0.0);//최초 위치
    DrawAndroid();
    glutSwapBuffers();
}

/*
 키보드 콜백 설정 함수
 w를 누르면 wire 모드로, s를 누르면 solid 모드로, q를 누르면 종료를 표현
 */
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
    switch (KeyPressed) {
        case 'w':
            flag = 1;
            break;
        case 's':
            flag = 0;
            break;
        case 'q':
            key = 6;
            break;
    }
}

/*
 key 값에 따라 노래가 흘러나온다.
 노래 재생은 sndPlaySound 함수로 흘러나오게 설정하였다.
 각 key 값의 뜻은 각 장면을 뜻한다.
 별도의 음악파일이 필요하며 경로설정은
 sndPlaySound(TEXT("음악파일경로") 를 입력하면 된다.
 */
void MyDisplay() {
    if (key == RUN) {//로봇이 달릴때
        Run();
        glPopMatrix();
    }
    else if (key == JAP) {//로봇이 잽을 날릴 때
        Jap();
        glPopMatrix();
    }
    else if (key == ROCKET) {//로봇이 로켓을 발사할때
        Rocket();
        glPopMatrix();
    }
    else if (key == YUNA) {//로봇이 김연아 선수의 모션을 취할 때
        Show();
        glPopMatrix();
    }
    else if (key == 5) {//중지가 선택됐을 때
       // sndPlaySound(NULL, SND_ASYNC);
    }
    else if (key == EXIT) {//종료가 선택됐을 때
        ex();
        glPopMatrix();
    }
}
/*
 타이머 함수
 각 장면마다 상태 표현을 다르게 두기 위해 대양한 시간 변수들이 쓰였다.
 */
void MyTimer(int Value) {
    time = time + 0.1;//달릴때 쓰인 타이머 변수
    time2 = time2 + 0.5;//잽을 날릴때 쓰인 타이머 변수
    time3 = time3 + 0.01;//로켓을 날릴때 쓰인 타이머 번수, 종료시 로봇이 뱅글뱅글 돌아가게 하기 위해 쓰인 타이머 변수
    time4 = time4 + 1.0;//김연아 선수 모션을 취할때 쓰인 타이머 변수
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}
/*
 마우스 오른쪽 클릭을 해서 메뉴를 선택하면 실행되는 함수.
 기본적으로 장면을 전환할땐 마우스 콜백을 이용하여 변환하도록 설정하였다.
 */
void MyMainMenu(int entryID) { //메뉴
    key = entryID;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);//초기화
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//디스플레이 모드 설정
    glutInitWindowSize(800, 800);//윈도우 크기 설정
    glutInitWindowPosition(0, 0);//윈도우 초기 위치 설정
    glutCreateWindow("Robot Animation");//윈도우 생성
    glInit(); // 조명 초기화
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);//메뉴추가
    glutAddMenuEntry("Run~", 1);//로봇이 달리는 모션 메뉴 추가
    glutAddMenuEntry("Punch~", 2);//로봇이 잽날리는 모션 메뉴 추가
    glutAddMenuEntry("Fly~", 3);//로봇이 로켓펀치를 날리는 모션 메뉴 추가
    glutAddMenuEntry("Skating~", 4);//로봇이 피겨스케이팅하는 모션 메뉴 추가
    glutAddMenuEntry("Pause", 5);//로봇이 하는 일을 멈추게 하는 메뉴 추가
    glutAddMenuEntry("cloth", 7); // clothing the robot
    glutAddMenuEntry("zoom", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//오른쪽우스클릭시메뉴팝업
    glutKeyboardFunc(MyKeyboard); //키보드 콜백
    glutTimerFunc(40, MyTimer, 1); //타이머 함수
    glutDisplayFunc(MyDisplay); //디스플레이
    glutMainLoop();
    return 0;
}


