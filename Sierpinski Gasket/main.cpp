#include<stdlib.h>
#include"glm\glm.hpp"
#include"GL\freeglut.h"
#include"GL\glew.h"

using glm::dvec2;
typedef dvec2 point2;

	int main(int argc, char **argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("Eimple OpenGL Example");
		glewInit();
		glutDisplayFunc(display);
		init();
		glutMainLoop();
	}



	void init(){
		const int number_of_points = 5000;
		point2 points[number_of_points];
		// A triangle in the plane z= 0
		point2 vertices[3] = { point2(-1.0, -1.0), point2(0.0, 1.0), point2(1.0, -1.0) };
		// An arbitrary initial point inside the triangle
		points[0] = point2(0.25, 0.50);
		// compute and store NumPoints-1 new points
		for (int k = 1; k < number_of_points; k++) {
			int j = rand() % 3; // pick a vertex at random
			// Compute the point halfway between selected 
			// vertex and previous point 
			points[k] = ( points[k-1] + vertices[j] ) / 2.0;
		}

		
	}

	void display() {}