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


/*
	Triangle Generated	
*/


const int NumTimesToSubdivide = 7;
const int NumTriangles = 6561; // 3^5 triangles generated
const int NumVertices = 3 * NumTriangles;
vec2 points[NumVertices];
int Index = 0;

void triangle(const vec2& a, const vec2& b, const vec2& c) {
	points[Index++] = a;
	points[Index++] = b;
	points[Index++] = c;
}


void divide_triangle(const vec2& a, const vec2& b, const vec2& c, int count) {
	if (count > 0) {
		//compute midpoints of sides
		vec2 v0 = (a + b) / 2.0f;
		vec2 v1 = (a + c) / 2.0f;
		vec2 v2 = (b + c) / 2.0f;
		//subdivide all but middle triangle
		divide_triangle(a, v0, v1, count - 1);
		divide_triangle(c, v1, v2, count - 1);
		divide_triangle(b, v2, v0, count - 1);
	}
	else {
		triangle(a, b, c); // draw triangle at end of recursion
	}
}

void init() {
	vec2 vertices[3] = {
		vec2(-1.0, -1.0), vec2(0.0, 1.0), vec2(1.0, -1.0)
	};
	// Subdivide the original triangle
	divide_triangle(vertices[0], vertices[1], vertices[2],
		NumTimesToSubdivide);
	// Load shaders and use the resulting shader program
	GLuint program = InitShader("shaders/vshader.glsl", "shaders/fshader.glsl");
	glUseProgram(program);
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points,
		GL_STATIC_DRAW);
	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, NumTriangles);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Sierpinski Gasket");
	glewInit();
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


/*
	/Triangle Generated
*/

/*
	Point Generated
*/

//const int number_of_points = 100000;
//
//
//
//void init(){
//	point2 points[number_of_points];
//	// A triangle in the plane z= 0
//	point2 vertices[3] = { point2(-1.0, -1.0), point2(0.0, 1.0), point2(1.0, -1.0) };
//	// An arbitrary initial point inside the triangle
//	points[0] = point2(0.25, 0.5);
//	// compute and store NumPoints-1 new points
//	for (int k = 1; k < number_of_points; k++) {
//		int j = rand() % 3; // pick a vertex at random
//		// Compute the point halfway between selected 
//		// vertex and previous point 
//		points[k] = ( points[k-1] + vertices[j] ) / 2.0f;
//	}
//
//	// Load shaders and use the resulting shader program 
//	GLuint program = InitShader( "shaders/vshader.glsl", "shaders/fshader.glsl" );
//	glUseProgram( program );
//
//
//	GLuint abuffer;
//
//	glGenVertexArrays(1, &abuffer);
//	glBindVertexArray(abuffer);
//
//	GLuint buffer;
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//
//	// Initialize the vertex position attribute from the vertex shader
//	GLuint loc = glGetAttribLocation( program, "vPosition" ); 
//	glEnableVertexAttribArray( loc );
//	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
//
//
//}
//
//void display() {
//	
//	glClear(GL_COLOR_BUFFER_BIT);
//	glDrawArrays(GL_POINTS, 0, number_of_points);
//	glFlush();
//}
//
//int main(int argc, char **argv) {
//	srand(0);
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA);
//	glutInitWindowSize(512, 512);
//	glutInitWindowPosition(0, 0);
//
//	glutInitContextVersion(3, 2); 
//	glutInitContextProfile(GLUT_CORE_PROFILE);
//
//	glutCreateWindow("Sierpinsky Gasket");
//
//	glewInit();
//	init();
//	glutDisplayFunc(display);
//
//	glutMainLoop();
//	return 0;
//
//}

/*
	/Point Generated
*/