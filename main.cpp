/**
* Author: Samvid Jhaveri
* Date: Fall 2016
* Partner: I work alone #LONE-RANGER
* Course: Interactive Computer Graphics
*
*
*Summary of File:
*	This is the first question in the assignement.
*		This will load texure on the 2 different places of the screen.
*/
#include "glsupport.h"
#include <glut.h>
#include <iostream>

using namespace std;

GLint program;
GLuint vertPostionVBO;
GLuint positionAttribute;

GLuint vertTexCoordVBO;
GLuint texCoordAttribute;

GLuint timeUniform;
GLuint positionUniform;
float textureOffset = 0.0;

GLuint smurfTexture;

/**
* void display(void)
*
* Paraeters: Nothing
* Retun Value: Nothing
*
* Summary of the pogram:
*	This function wil do all the rendering on the screen. So this is like the update function.
*	Binds all the buffers and draw as per the specification.
*/
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);


	glUniform1f(timeUniform, textureOffset);

	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, vertPostionVBO);

	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
	glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordAttribute);
	glBindTexture(GL_TEXTURE_2D, smurfTexture);

	glUniform2f(positionUniform, -0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUniform2f(positionUniform, 0.5, -0.5);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(positionAttribute);
	glDisableVertexAttribArray(texCoordAttribute);

	glutSwapBuffers();
}

/**
*
* void keyboard(unsigned char key, int x, int y)
*
* Paraeters: Unsigned char: key, int: x and y
* Retun Value: Nothing
*
* Summary of the pogram:
*	This program takes the input from the keyboard and that is specified in the init function and move around the image as the button is presed
*/
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		textureOffset += 0.02;
		break;
	case 'd':
		textureOffset -= 0.02;
		break;
	}
}

/**
*
* void mouse(int button, int state, int x, int y) {
*
* Paraeters: int: button, state, x, y
* Retun Value: Nothing
*
* Summary of the pogram:
*	This program takes input from the mouse button.
*	The first If part is responsible to change the texture.
*	The another part is responsible for the repossitioning of the texture.
*/
void mouse(int button, int state, int x, int y) {
	float newPositionX = (float)x / 250.0f - 1.0f;
	float newPositionY = (1.0 - (float)y / 250.0);
	glUniform2f(positionUniform, newPositionX, newPositionY);
}

/**
*
* void mouseMove(int x, int y) {
*
* Paraeters: int: x, y
* Retun Value: Nothing
*
* Summary of the pogram:
*	This program takes input from the mouse movement.
*	It will reposition the texture as the mose positions.
*/
void mouseMove(int x, int y) {
	float newPositionX = (float)x / 250.0f - 1.0f;
	float newPositionY = (1.0 - (float)y / 250.0);
	glUniform2f(positionUniform, newPositionX, newPositionY);
}

/**
* void init(void)
*
* Paraeters: Nothing
* Retun Value: Nothing
*
* Summary of the pogram:
*	This part is reponsible of all the initalization of the program.
*	Coordinates of triangles and texture are initiated here.
*	All the attributes are also initiated here and joined with the program.
*/
void init() {
	glClearColor(0.2, 0.2, 0.2, 0.0);
	program = glCreateProgram();
	readAndCompileShader(program, "vertex.glsl", "fragment.glsl");

	smurfTexture = loadGLTexture("Smurf1.png");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUseProgram(program);
	positionAttribute = glGetAttribLocation(program, "position");
	texCoordAttribute = glGetAttribLocation(program, "texCoord");
	timeUniform = glGetUniformLocation(program, "time");
	positionUniform = glGetUniformLocation(program, "modelPosition");

	glGenBuffers(1, &vertPostionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertPostionVBO);

	GLfloat sqVert[12] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,

		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f
	};

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), sqVert, GL_STATIC_DRAW);

	glGenBuffers(1, &vertTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
	GLfloat sqTexCoords[12] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), sqTexCoords, GL_STATIC_DRAW);

}

/**
* void reshape(int w, int h)
*
* Paraeters: int: w, h
* Retun Value: Nothing
*
* Summary of the pogram:
*	This funciton will reshape the window if the size changes of the viewPort.
*/
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

/**
* void idle(void))
*
* Paraeters: Nothing
* Retun Value: Nothing
*
* Summary of the pogram:
*	This will display the things when the window is idle
*/
void idle(void) {
	glutPostRedisplay();
}

/**
* int main(int argc, char **argv)
*
* Paraeters: int: argc char: (Double Pointer)argv
* Retun Value: int
*
* Summary of the pogram:
*	Entry point of the program. Draws the window and binds every function in the program.
*/
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CS - 6533");

	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	init();
	glutMainLoop();
	return 0;
}