/*  CS 551 Assignment 1 skeleton */
/*  Brian Clarke  */
/*
keyboard controls:
s/S:	Positive/negative shoulder rotation
e/E:	Positive/negative elbow rotation
O/C:	Open/Close the hand -- YOU GET TO IMPLEMENT THIS

x/X:	Positive/negative X-axis shift of the model
y/Y:	Positive/negative Y-axis shift of the model
UP/DOWN ARROWS:	(zoom) Z-axis shift of the model

LEFT/RIGHT ARROWS:	Y-axis rotations
PAGE UP/DOWN:	X-axis rotations
ESC:	exit
*/

#include "stdafx.h"


#include<stdio.h>
//#include<GL/gl.h>
//#include<GL/glu.h>
//#include<GL/glut.h>
#include "glut.h"

#define ESC 27

static GLfloat red[] = { 1, 0, 0 }, green[] = { 0, 1, 0 }, blue[] = { 0,0,1 }, orange[] = { 255,165,0 };
static int shoulder = 0, elbow = 0, finger1=0, finger2=0;
static int xrot = 0, yrot = 0, zrot = 0;
static GLfloat xshift = -1.0, yshift = 0.0, zoom = -3.0;

/* some basic GL initialization */
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

/* The display callback */
void draw_stuff()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(xshift, yshift, zoom);
	glRotatef((GLfloat)xrot, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)yrot, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)zrot, 0.0, 0.0, 1.0);

	glColor3fv(red);
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3fv(green);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	/*"hand" code...*/
	glColor3fv(blue);
	glTranslatef(1.0, 0.1,0.0);
	glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3fv(orange);
	glTranslatef(-1.0, -0.225, 0.0);
	glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

/* the window-reshape callback */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

/* The basic keyboard controls, callback for glutKeyboardFunc() */
void kb(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
			shoulder = (shoulder + 5) % 360;
		
		
		glutPostRedisplay();
		break;
	case 'S':
			shoulder = (shoulder - 5) % 360;
		
		
		glutPostRedisplay();
		break;
	case 'e':
		if(elbow != 150)
		{
			elbow = (elbow + 5) % 360;
		}
		
		glutPostRedisplay();
		break;
	case 'E':
		if (elbow != -150) {

			elbow = (elbow - 5) % 360;
		}
		glutPostRedisplay();
		break;
	case 'C':
		if (finger1 != 0 || finger2 != 0)
		{
			finger1 = finger1 -5 ;
			finger2 = finger2 + 10;
		}
		
		glutPostRedisplay();
		break;
	case 'O':
		if (finger1 < 90 && finger2 != -180) {
			finger1 = finger1+5;
			finger2 = finger2 - 10;
			
		glutPostRedisplay();
		}
		
		else {
			finger1 = finger1 + 0;
			finger2 = finger2 - 0;
			
		}

	
		
	
		break;
	case 'x':
		xshift += .25;
		glutPostRedisplay();
		break;
	case 'X':
		xshift -= .25;
		glutPostRedisplay();
		break;
	case 'y':
		yshift += .25;
		glutPostRedisplay();
		break;
	case 'Y':
		yshift -= .25;
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		xrot = yrot = zrot = shoulder = elbow = 0;
		xshift = -1.0;
		yshift = 0.0;
		zoom = -3.0;
		glutPostRedisplay();
		break;
	case 'z':
		zrot = (zrot - 1) % 360;
		glutPostRedisplay();
		break;
	case 'Z':
		zrot = (zrot + 1) % 360;
		glutPostRedisplay();
		break;
	case ESC:
		return;
		break;
	default:
		break;
	}
}

/* The "special" keyboard controls, callback for glutSpecialFunc() */
void skb(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		zoom += 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		zoom -= 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		yrot = (yrot - 1) % 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		yrot = (yrot + 1) % 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_UP:
		xrot = (xrot - 1) % 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		xrot = (xrot + 1) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 300);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("foo");
	init();
	glutDisplayFunc(draw_stuff);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kb);
	glutSpecialFunc(skb);
	glutMainLoop();
	return 0;
}

