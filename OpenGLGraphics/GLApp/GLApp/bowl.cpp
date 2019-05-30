#include <fstream>

#include "vertex.h"
#include "bowl.h"

Sphere::Sphere()
{
	stacks = 10;
	slices = 10;
	radius = 6.0f;

	sphereVerticesNor = (VertexWtihNormal *)malloc(sizeof(VertexWtihNormal) * 121);
	sphereIndices = (unsigned int *)malloc(sizeof(unsigned int) * 660);
	CreateSpherewithNormal();
}

Sphere::~Sphere()
{
	free(sphereVerticesNor);
	free(sphereIndices);
}

void Sphere::CreateSpherewithNormal(void)
{
	int count;
	count = 0;
	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			sphereVerticesNor[count].coords = vec4(x * radius, y * radius + 6.0, z * radius, 1.0);
			sphereVerticesNor[count].normals = vec3(x, y, z); ///Sphere normals

			count++;
		}
	}

	count = 0;
	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i + slices;
		count++;

		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + 1;
		count++;
	}

	count = 0;
}

VertexWtihNormal * Sphere::GetVerData(int &verNum)
{
	verNum = 121;
	return sphereVerticesNor;
}

unsigned int * Sphere::GetTriData(int &triNum)
{
	triNum = 660;
	return sphereIndices;
}