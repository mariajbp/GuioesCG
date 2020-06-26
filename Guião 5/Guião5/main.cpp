#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
int mouseKey, mouseX, mouseY;
vector<float> vecTreesX;
vector<float> vecTreesY;

int updateNo=0;

void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void drawPolar2Cartesian(float a, float b, float rad){
    float x = rad * cos(b) * sin(a);
    float y = rad * sin(b);
    float z = rad * cos(b) * cos(a);
    glTranslatef(x,y,z);
}




void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0) h = 1;
	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}
float rng(){
    return 100*sin(rand());
}
bool isInside(float x, float y){
    return pow(x,2)+pow(y,2)<= 2500;
}
void makeTree(float x, float y){
    glTranslatef(x,0,y);
    glRotatef(90,-1,0,0);

        float height = 4;
        //glTranslatef(0,0, height/2);
        glColor3f(0.5, 0.35, 0.05);
        glutSolidCone(1, height, 5, 1);
        glColor3f(0, 1, 0);
        glTranslatef(0,0, height/2);
        glutSolidCone(3, height*3, 7, 1);




}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0,0.0f, 1.0f, 0.0f);

	//plano verde
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

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






    glBegin(GL_LINES);
    // X axis
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}







void processMouse(int button, int state,int x, int y){
  if(state==GLUT_DOWN){mouseX = x; mouseY = y; mouseKey=button;} else mouseKey=-1;
}
void processMotion(int x, int y){
    if((x!=mouseX||y!=mouseY)&& mouseKey==GLUT_LEFT_BUTTON){

        float xRatio = mouseX - x;
        float yRatio = mouseY - y;
        alfa += 0.01 * xRatio;
        beta += 0.01 * yRatio;
        mouseX = x;
        mouseY = y;
    }
    if((x!=mouseX||y!=mouseY)&& mouseKey==GLUT_RIGHT_BUTTON){

        float yRatio = mouseY - y;
        radius+= yRatio;
        mouseX = x;
        mouseY = y;
    }

    spherical2Cartesian();
    glutPostRedisplay();

}
void idle(){
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    if(timeSinceStart%3==0){
        updateNo++;
        glutPostRedisplay();
    }

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("3D scenario");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(idle);
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMotion);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
