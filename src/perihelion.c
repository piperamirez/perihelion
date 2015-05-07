#include "camera.h"
#include <math.h>
#include <GLUT/glut.h>
//#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define HEIGHT (600)
#define WIDTH (800)
#define RES_PLANET (15)
#define RES_ORBIT (60)

struct Camera camera;

float spotAngle = 360;

GLfloat aMaterial[]       = { 0.000,  0.000,  0.000,  0.000};
GLfloat spotPos[]         = { 0.000,  0.000,  0.000,  1.000};
GLfloat position[]        = { 0.000,  3.000,  0.000,  1.000};
GLfloat spot_direction[]  = {-1.000, -1.000,  0.000};
GLfloat direction[]       = { 0.000, -1.000,  0.000};

GLfloat light1_ambient[]  = { 0.200,  0.200,  0.200,  1.000}; 
GLfloat light1_diffuse[]  = { 0.851,  0.644,  0.125,  1.000}; 
GLfloat light1_specular[] = { 1.000,  1.000,  1.000,  1.000}; 
GLfloat light1_position[] = {-2.000,  2.000,  1.000,  1.000}; 

long int t = 0;
float acceleration = 1.0;
float a = 100;
int i;

int stars[2000][8][3];

int fullscreen = 0;
int drawOrbits = 0;
int drawLabels = 0;

int keys[128];
int mouseX, mouseY;

void drawScene(void);
void drawStars();
void drawOrbit(int, int);
void drawString(float, float, float, char*);
void loadStars();
void exitFullScreen(void);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void init(void);
void idle(void);
void reshape(int, int);

int main(int argc, char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH)-WIDTH)/2, 
		(glutGet(GLUT_SCREEN_HEIGHT)-HEIGHT)/2);
    glutCreateWindow("Perihelion");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
	glEnable(GL_DEPTH_TEST);
	loadStars();
    init();
    glutMainLoop();
    return 0;
}

void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	
	drawStars();

	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular); 
		
	// Draw the sun
	glLightfv(GL_LIGHT0, GL_POSITION, spotPos); 
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glColor3f(1, 1, 0.2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, aMaterial);
		glutSolidSphere(2, 30, 30);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	// Draw Mercury
	glColor3f(0.8, 0.4, 0.0);
	drawOrbit(3, 7);
	glPushMatrix();		
		glRotatef(3, 1, 0, 0);
		glPushMatrix();
			glColor3f(0.8, 0.4, 0.0);
			glRotatef(t * 0.047, 0,1, 0);
			glTranslatef(0, 0, 7);
			drawString(0, 0, 0, "Mercury");
			glutSolidSphere(0.3, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Venus
	glColor3f(0.28, 0.46, 1.0);
	drawOrbit(9, 10);
	glPushMatrix();		
		glRotatef(9,1, 0, 0);
		glPushMatrix();
			glColor3f(0.28, 0.46, 1.0);
			glRotatef(t * 0.035, 0, 1, 0);
			glTranslatef(0, 0, 10);
			drawString(0, 0, 0, "Venus");
			glutSolidSphere(0.7, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw The Earth
	glColor3f(0.15, 0.25, 0.54);
	drawOrbit(8, 13);
		glPushMatrix();		
		glRotatef(8, 1, 0, 0);
		glPushMatrix();
			glColor3f(0.15, 0.25, 0.54);
			glRotatef(t * 0.029, 0, 1, 0);
			glTranslatef(0, 0, 13);
			drawString(0, 0, 0, "Earth");
			glutSolidSphere(0.7, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Mars
	glColor3f(1, 0.0, 0.0);
	drawOrbit(5, 16);
	glPushMatrix();		
		glRotatef(5, 1, 0, 0);
		glPushMatrix();
			glColor3f(1, 0.0, 0.0);
			glRotatef(t * 0.024, 0, 1, 0);
			glTranslatef(0, 0, 16);
			drawString(0, 0, 0, "Mars");
			glutSolidSphere(0.6, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Jupiter
	glColor3f(0.8, 0.58, 0.047);
	drawOrbit(8, 24);
	glPushMatrix();		
		glRotatef(8, 1, 0, 0);
		glPushMatrix();
			glColor3f(0.8, 0.58, 0.047);
			glRotatef(t * 0.013, 0, 1, 0);
			glTranslatef(0, 0, 24);
			drawString(0, 0, 0, "Jupiter");
			glutSolidSphere(1.2, RES_PLANET,RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Saturn
	glColor3f(0.8, 0.58, 0.047);
	drawOrbit(5, 30);
	glPushMatrix();		
		glRotatef(5, 1, 0, 0);
		glPushMatrix();
			glColor3f(0.6, 0.4, 0.030);
			glRotatef(t * 0.009, 0, 1, 0);
			glTranslatef(0, 0, 30);
			glRotatef(90, 1, 0.5, 0);
			glScalef(1, 1, 0.1);
			glutSolidTorus(0.6, 1.8, 5, 50);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.8, 0.58, 0.047);
			glRotatef(t * 0.009, 0, 1, 0);
			glTranslatef(0, 0, 30);
			drawString(0, 0, 0, "Saturn");
			glutSolidSphere(1, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Uranus
	glColor3f(0, 0.1, 1);
	drawOrbit(7, 40);
	glPushMatrix();		
		glRotatef(7, 1, 0, 0);
		glPushMatrix();
			glColor3f(0, 0.1, 1);
			glRotatef(t * 0.006, 0, 1, 0);
			glTranslatef(0, 0, 40);
			glRotatef(3, 1, 0.5, 0);
			glScalef(1, 1, 0.1);
			glutSolidTorus(0.1, 1, 5, 50);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0, 0.6, 0.8);
			glRotatef(t * 0.006, 0, 1, 0);
			glTranslatef(0, 0, 40);
			drawString(0, 0, 0, "Uranus");
			glutSolidSphere(0.7, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Draw Neptune
	glColor3f(0.0, 0.89, 0.93);
	drawOrbit(8, 48);
	glPushMatrix();		
		glRotatef(8, 1, 0, 0);
		glPushMatrix();
			glColor3f(0.0, 0.89, 0.93);
			glRotatef(t * 0.005, 0, 1, 0);
			glTranslatef(0, 0, 48);
			drawString(0, 0, 0, "Neptune");
			glutSolidSphere(0.7, RES_PLANET, RES_PLANET);
		glPopMatrix();
	glPopMatrix();
	
	// Almost forgot, let's draw the Moon!
	glPushMatrix();
		glRotatef(8,1,0,0);
		glPushMatrix();
			glColor3f(0.7,0.8,0.8);
			glRotatef(t*0.029,0,1,0);
			glTranslatef(0,0,13);
			glPushMatrix();
				glRotatef(t*0.348,0,1,0);
				glTranslatef(0,0,1.3);
				glutSolidSphere(0.1,RES_PLANET,10);
			glPopMatrix();
   		glPopMatrix();
	glPopMatrix();
	
	//Sorry Pluto, you're not a planet anymore :(
	
	if (a < -1000) {
		a = 100;
	}
		
	glutSwapBuffers();
	
}

void loadStars() {
	int i, j, x, y, z;
	FILE *in = fopen("data/stars.dat","r");
	for (i = 0; i < 2000; i++) {
		for (j = 0; j < 8; j++) {
			fscanf(in, "%d %d %d", &x, &y, &z);
			stars[i][j][0]=x;
			stars[i][j][1]=y;
			stars[i][j][2]=z;
		}
	}
	fclose(in);
}

void drawStars() {
	int i, j;
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 8; j++) {
			glVertex3f(
				stars[i][j][0], 
				stars[i][j][1], 
				stars[i][j][2]);
		}
	}
	glEnd();
}

void exitFullScreen(void) {
	glutReshapeWindow(WIDTH, HEIGHT);
	glutPositionWindow(
		(glutGet(GLUT_SCREEN_WIDTH)-WIDTH)/2, 
		(glutGet(GLUT_SCREEN_HEIGHT)-HEIGHT)/2);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initCamera(&camera);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
}

void keyDown(unsigned char key, int x, int y) {
    keys[key] = 1;
	switch (key) {
		case 'o':
			acceleration += 0.1;
			break;
		case 'l':
			acceleration -= 0.1;
			break;
		case 'k':
			drawOrbits = !drawOrbits;
			break;
		case 'n':
			drawLabels = !drawLabels;
			break;
		case 'f':
			fullscreen = !fullscreen;
			if (fullscreen) {
				glutFullScreen();
			}
			else {
				exitFullScreen();
			}
			break;
		case 27:
			if (fullscreen) {
				exitFullScreen();
				fullscreen = !fullscreen;
				break;
			}
			else {
				exit(0);
				break;
			}
	}
}

void keyUp(unsigned char key, int x, int y) {
    keys[key] = 0;
}

void drawOrbit(int angle, int radio) {
	if (drawOrbits) {
		glPushMatrix();		
			glRotatef(angle, 1, 0, 0);
			glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glutSolidTorus(0.04, radio, 10, RES_ORBIT);
			glPopMatrix();
		glPopMatrix();
	}
}

void drawString(float x, float y, float z, char *string) {
	int i;
	int len = strlen(string);
	if (drawLabels) {
		glDisable(GL_LIGHTING);
		glRasterPos3f(x, y + 1.5, z);
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		}
		glEnable(GL_LIGHTING);
	}
}

void idle(void) {
	t += acceleration;
    updateCamara(&camera, keys, mouseX, mouseY);
	glutPostRedisplay();
}

void reshape(int w, int h) {
    reshapeCamara(&camera, w, h);
	if(h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 1, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
