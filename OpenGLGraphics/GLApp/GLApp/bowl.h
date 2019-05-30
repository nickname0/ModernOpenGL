#ifndef SPHERE_H
#define SPHERE_H

#include <fstream>

#include "vertex.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using namespace glm;

class Sphere
{
private:
	int sizeX;
	int sizeY;
	VertexWtihNormal *sphereVerticesNor;  //121
	unsigned int *sphereIndices; //660

	int stacks; //10
	int slices; //10
	float radius;

	void CreateSpherewithNormal();
public:
	Sphere();
	~Sphere();

	VertexWtihNormal * GetVerData(int &);
	unsigned int * GetTriData(int &);
};


#endif