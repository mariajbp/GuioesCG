#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include </usr/local/Cellar/devil/1.8.0_1/include/IL/il.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

float camX = 0, camY = 1.7, camZ = 4, lookX=0,lookY=camY,lookZ=0;
int startX, tracking = 0;

int alpha = 0;
float hRatio =2* (30.0f/256.0f);
int th,tw;

unsigned char *imageData;
vector<float> vertexB;
GLuint buffers[1];
vector<float> vecTreesX;
vector<float> vecTreesY;

int updateNo=0;

float speed=0.5;
void drawPolar2Cartesian(float a, float b, float rad){
    float x = rad * cos(b) * sin(a);
    float y = rad * sin(b);
    float z = rad * cos(b) * cos(a);
    glTranslatef(x,y,z);
}
void drawGuiao5();
static float hf(float x, float z);

float rng(){
    return ((tw-1)/2)*sin(rand());
}
bool isInside(float x, float y){
    return pow(x,2)+pow(y,2)<= 2500;
}
void makeTree(float x, float y){
    glTranslatef(x,hf(x+tw/2,y+th/2),y);
    glRotatef(90,-1,0,0);

    float height = 4;
    glColor3f(0.5, 0.35, 0.05);
    glutSolidCone(1, height, 5, 1);
    glColor3f(0, 1, 0);
    glTranslatef(0,0, height/2);
    glutSolidCone(3, height*3, 7, 1);
}

void changeSize(int w, int h) {
	if(h == 0) h = 1;
	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

static float h(int x, int z){
    return hRatio**(imageData+tw*z+x);
}



void drawTerrain() {
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(5);
    float *vertex = &vertexB[0];
    glEnableClientState(GL_VERTEX_ARRAY);
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexB.size()*sizeof(float), vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);

   for(int i=0; i<(tw-1);i++) {
        switch (i%5){
            case 0 : glColor3f(0,0.5,0); break;
            case 1 : glColor3f(0,0.3,0); break;
            case 2 : glColor3f(0,0.2,0); break;
            case 3 : glColor3f(0,0.3,0); break;
            case 4 : glColor3f(0,0.5,0); break;
        }
        glDrawArrays(GL_TRIANGLE_STRIP, tw * i * 2, tw * 2);
    }

    glDeleteBuffers(1,buffers);
}

void init() {
    unsigned int t;
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)"terreno.jpg");
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);

    if (th+tw!=512) cout<<"Width: "<<tw<<"Height: "<<th<<endl;

// imageData is a LINEAR array with the pixel values
    imageData = ilGetData();
    float yy;
    float xStart= -((float)tw)/2;
    float zStart= -((float)th)/2;

    float x = xStart;
    float y=0;
    float z=zStart;
// 	Build the vertex arrays
    for(int i=0;i<tw-1;i++) {
        float xNow=xStart+i;
        float xNext=xStart+i+1;

        for (int j = 0; j < th; j++) {
        z = zStart + (float)j;
        x = xNext;
        y = (float)h(i+1,j);
        vertexB.push_back(x);
        vertexB.push_back(y);
        vertexB.push_back(z);

        z = zStart + (float)j;
        x = xNow;
        y = (float)h(i,j);
        vertexB.push_back(x);
        vertexB.push_back(y);
        vertexB.push_back(z);
        }
    }

// 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void drawGuiao5() {
    //torus rosa
    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0,1.1,0);
    glutSolidTorus(1,3,30,50);

    glPushMatrix();
    glRotatef(-2*updateNo,0,1,0);
    //8 teapots azuis
    glColor3f(0.0f, 0.0f, 1.0f);
    float alpha = 2* M_PI/8;
    float alphaDeg = 360/8;

    for (int i=0;i<8;i++) {
        glPushMatrix();
        drawPolar2Cartesian(alpha * i, 0, 15);
        glRotatef(-90+alphaDeg*i,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();

    glRotatef(2*updateNo,0,1,0);


    //teapot vermelho
    alpha = 2* M_PI/16;
    alphaDeg = 360/16;
    glColor3f(1.0f, 0.0f, 0.0f);
    for(int i=0;i<16;i++){
        glPushMatrix();
        drawPolar2Cartesian(alpha * i, 0, 35);
        glRotatef(alphaDeg*i,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();

    }
    glPopMatrix();
    glPopMatrix();

    if(vecTreesX.size()==0){
        for(int i=0;i<1000;i++){
            float rand1 =rng();
            float rand2 =rng();
            while(isInside(rand1, rand2)){rand1 =rng();rand2 =rng();}
            vecTreesX.push_back(rand1);
            vecTreesY.push_back(rand2);
            ;
        }
    }

    for(int i=0;i<1000;i++){
        glPushMatrix();
        makeTree(vecTreesX[i], vecTreesY[i]);
        glPopMatrix();
    }

}

float hf(float x, float z) {
    if (x>256||z>256) return 30;
    int x1=floor(x);
    int x2=ceil(x);
    int z1= floor(z);
    int z2= ceil(z);
    float fz = z - z1;
    float fx = x - x1;
    float h_x1_z  = h(x1,z1) * (1-fz) + h(x1,z2) * fz;
    float h_x2_z  = h(x2,z1) * (1-fz) + h(x2,z2) * fz;
    return ( h_x1_z * (1 - fx) + h_x2_z * fx);
}

void drawAxis(){
    glBegin(GL_LINES);
    // X axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void renderScene(void) {
    cout<<hf(camX+(tw/2),camZ+(th/2))<<endl;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
	        lookX,lookY,lookZ,
	        0.0f,1.0f,0.0f);
	//drawAxis();
    drawTerrain();
    drawGuiao5();
	glutSwapBuffers();
}

void setCameraY(){
    camY = 1.7+hf(camX+(tw/2),camZ+(th/2));
    lookY =camY;
}

void processKeyboard(unsigned char key,int x, int y) {
    float dX = lookX - camX;
    float dZ = lookZ - camZ;
    float upY = 1;
    float rX,rZ;
    switch (key) {
        case 'w': camX+=dX*speed; camZ+=dZ*speed;lookX+=dX*speed;lookZ+=dZ*speed;setCameraY(); break;
        case 's': camX-=dX*speed; camZ-=dZ*speed;lookX-=dX*speed;lookZ-=dZ*speed;setCameraY();break;
        case 'd': rZ = dX ;rX = - dZ*upY;camX+=rX*speed;camZ+=rZ*speed;lookX+=rX*speed;lookZ+=rZ*speed;setCameraY();break;
        case 'a': rZ = dX ;rX = - dZ*upY;camX-=rX*speed;camZ-=rZ*speed;lookX-=rX*speed;lookZ-=rZ*speed;setCameraY();break;
    }
    glutPostRedisplay();
}
void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
		}
		tracking = 0;
	}
    glutPostRedisplay();
}

void processMouseMotion(int xx, int yy) {

	int deltaX;
	int alphaAux;

	if (!tracking)
		return;

	deltaX = xx - startX;

	if (tracking == 1) {
		alphaAux = alpha + deltaX;
    }

	lookX = camX + sin(-alphaAux * 3.14 / 180.0);
	lookZ = camZ + cos(-alphaAux * 3.14 / 180.0);
	lookY = camY;
	glutPostRedisplay();
}
void idle(){
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    if(timeSinceStart%3==0){
        updateNo++;
        glutPostRedisplay();
    }

}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Guião 7");
	//glewInit();


// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(processKeyboard);

    ilInit();
	init();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

