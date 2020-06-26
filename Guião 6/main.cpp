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

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;
float hRatio =2* (30.0f/256.0f);
int th,tw;

vector<float> vertexB;
GLuint buffers[1];


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
            case 0 : glColor3f(0,0,0); break;
            case 1 : glColor3f(0,0,0.5); break;
            case 2 : glColor3f(0,0.5,0); break;
            case 3 : glColor3f(0,0,0.5); break;
            case 4 : glColor3f(0,0.50,0); break;
        }
        glDrawArrays(GL_TRIANGLE_STRIP, tw * i * 2, tw * 2);
    }
}

void init() {
    unsigned int t;
    unsigned char *imageData;
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
        y = hRatio*(float)*(imageData+(tw*j)+i+1);
        vertexB.push_back(x);
        vertexB.push_back(y);
        vertexB.push_back(z);

        z = zStart + (float)j;
        x = xNow;
        y = hRatio*(float)*(imageData+(tw*j)+i);
        vertexB.push_back(x);
        vertexB.push_back(y);
        vertexB.push_back(z);
        }
    }

// 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}



void renderScene(void) {
	float pos[4] = {-1.0, 1.0, 1.0, 0.0};
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,0.0,0.0,0.0, 0.0f,1.0f,0.0f);
    drawTerrain();
	glutSwapBuffers();
}


void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
    glutPostRedisplay();
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
	glutPostRedisplay();
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Guião 6");
	//glewInit();

// Required callback registry 
	glutDisplayFunc(renderScene);
	//glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

    ilInit();
	init();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

