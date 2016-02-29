#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include"glm\glm.hpp"
#include"GL\glew.h"
#include"GL\freeglut.h"
#include"shader_setup.h"

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

using glm::vec2;
typedef vec2 point2;

const int number_of_points = 50000;


void init(){
	point2 points[number_of_points];
	// A triangle in the plane z= 0
	point2 vertices[3] = { point2(-1.0, -1.0), point2(0.0, 1.0), point2(1.0, -1.0) };
	// An arbitrary initial point inside the triangle
	points[0] = point2(0.25, 0.5);
	// compute and store NumPoints-1 new points
	for (int k = 1; k < number_of_points; k++) {
		int j = rand() % 3; // pick a vertex at random
		// Compute the point halfway between selected 
		// vertex and previous point 
		points[k] = ( points[k-1] + vertices[j] ) / 2.0f;
	}

	// Load shaders and use the resulting shader program 
	GLuint program = InitShader( "shaders/vshader.glsl", "shaders/fshader.glsl" );
	glUseProgram( program );


	GLuint abuffer;

	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation( program, "vPosition" ); 
	glEnableVertexAttribArray( loc );
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background


}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, number_of_points);
	glFlush();
}

int main(int argc, char **argv) {
	srand(0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);

	glutInitContextVersion(3, 2); 
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Sierpinsky Gasket");

	glewInit();
	init();
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
