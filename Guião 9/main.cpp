#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>

#define _PI_ 3.14159

float alfa = 0.0f, beta = 0.0f, radius = 10.0f;
float camX, camY, camZ;

GLuint vertexCount, vertices;
int timebase = 0, frame = 0;

GLfloat dark[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
float red[] = { 0.8, 0.2, 0.2, 1.0 };


float pos[4] = {1.0, 1.0, 1.0, 0.0};

int npoints;
GLuint buffer[2];


void sphericalToCartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

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

void cilindroVBO(float height, float radius, int sides) {

    int i=0;
    int n=0;
    float l1 = 0;
    float l2 = 0;
    npoints = 4*sides*3*3;
	float delta = 2.0f * _PI_ / sides;

    float *vertexB = NULL;
    vertexB=(float*)malloc(npoints*sizeof(float));
    float *normalB = NULL;
    normalB=(float*)malloc(npoints*sizeof(float));

    //iniciar buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for(;sides>0;sides--)
    {
        l1=l2;
        l2+=delta;

        //Base Superior
        vertexB[i++]=0; vertexB[i++] = height; vertexB[i++]=0;
        vertexB[i++]=sin(l1); vertexB[i++]=height; vertexB[i++]=cos(l1);
        vertexB[i++]=sin(l2); vertexB[i++]=height; vertexB[i++]=cos(l2);

        normalB[n++]=0; normalB[n++]=1; normalB[n++]=0;
        normalB[n++]=0; normalB[n++]=1; normalB[n++]=0;
        normalB[n++]=0; normalB[n++]=1; normalB[n++]=0;

        //Base Inferior
        vertexB[i++]=0; vertexB[i++]=0; vertexB[i++]=0;
        vertexB[i++]=sin(l2); vertexB[i++]=0; vertexB[i++]=cos(l2);
        vertexB[i++]=sin(l1); vertexB[i++]=0; vertexB[i++]=cos(l1);

        normalB[n++]=0; normalB[n++]=-1; normalB[n++]=0;
        normalB[n++]=0; normalB[n++]=-1; normalB[n++]=0;
        normalB[n++]=0; normalB[n++]=-1; normalB[n++]=0;

        //Dois triângulos para os lados
        vertexB[i++]=sin(l1);vertexB[i++]=height;vertexB[i++]=cos(l1);
        vertexB[i++]=sin(l1);vertexB[i++]=0;vertexB[i++]=cos(l1);
        vertexB[i++]=sin(l2);vertexB[i++]=0;vertexB[i++]=cos(l2);

        normalB[n++]=sin(l1);normalB[n++]=0;normalB[n++]=cos(l1);
        normalB[n++]=sin(l1);normalB[n++]=0;normalB[n++]=cos(l1);
        normalB[n++]=sin(l2);normalB[n++]=0;normalB[n++]=cos(l2);

        vertexB[i++]=sin(l1);vertexB[i++]=height;vertexB[i++]=cos(l1);
        vertexB[i++]=sin(l2);vertexB[i++]=0;vertexB[i++]=cos(l2);
        vertexB[i++]=sin(l2);vertexB[i++]=height;vertexB[i++]=cos(l2);

        normalB[n++]=sin(l1);normalB[n++]=0;normalB[n++]=cos(l1);
        normalB[n++]=sin(l2);normalB[n++]=0;normalB[n++]=cos(l2);
        normalB[n++]=sin(l2);normalB[n++]=0;normalB[n++]=cos(l2);
    }


    //Aqui dizemos qual é GLuint que vamos usar e quandos buffers tem
    glGenBuffers(2, buffer);

    // Informamos qual vai ser o buffer que vamos usar para guardar a VBO
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);

    //Temos 2 campos importantes (2º e 3º), no 2º metemos a memória necessária para guardar todas as coordenadas, e no 3º informamos o array que tem as coordenadas
    glBufferData(GL_ARRAY_BUFFER, npoints*sizeof(float), vertexB, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, npoints*sizeof(float), normalB,GL_STATIC_DRAW);


    free(vertexB);
    free(normalB);

}

void drawVBO(){

    //Indicar para cada buffer qual a sua utilização e composição
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glNormalPointer(GL_FLOAT,0,0);

    glDrawArrays(GL_TRIANGLES, 0, npoints);
}


void renderScene(void) {

	float pos[4] = {1.0, 1.0, 1.0, 0.0};
	float fps;
	int time;
	char s[64];

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT0,GL_POSITION, pos);


    float m1[] = { 0.2, 0.2, 0.2, 1.0 };
    float m2[] = { 0.8, 0.8, 0.8, 1.0 };
    float m3[] = { 0.8, 0.2, 0.2, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m2);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

	drawVBO();

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0; 
		sprintf(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	} 

// End of frame
	glutSwapBuffers();
}



void processKeys(int key, int xx, int yy) 
{
	switch(key) {
	
		case GLUT_KEY_RIGHT: 
						alfa -=0.1; break;

		case GLUT_KEY_LEFT: 
						alfa += 0.1; break;

		case GLUT_KEY_UP : 
						beta += 0.1f;
						if (beta > 1.5f)
							beta = 1.5f;
						break;

		case GLUT_KEY_DOWN: 
						beta -= 0.1f; 
						if (beta < -1.5f)
							beta = -1.5f;
						break;

		case GLUT_KEY_PAGE_DOWN : radius -= 0.1f; 
			if (radius < 0.1f)
				radius = 0.1f;
			break;

		case GLUT_KEY_PAGE_UP: radius += 0.1f; break;

	}
	sphericalToCartesian();

}



void initGL() {

// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// init
	sphericalToCartesian();
	glEnableClientState(GL_VERTEX_ARRAY);

    cilindroVBO(2,1,16);
}


int main(int argc, char **argv) {

// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		
// callback registration
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// keyboard callback registration
	glutSpecialFunc(processKeys);

#ifndef __APPLE__	
// init GLEW
	glewInit();
#endif

    // alguns settings para OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f,0.0f,0.0f,0.0f);


	initGL();

	//luzes
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	glutMainLoop();
	
	return 1;
}

