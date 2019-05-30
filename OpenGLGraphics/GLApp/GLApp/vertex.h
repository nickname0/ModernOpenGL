#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex1
{
   glm::vec4 coords;
   glm::vec2 texCoords;
};

struct VertexWtihNormal
{
	glm::vec4 coords;
	glm::vec3 normals;
	//glm::vec2 texCoords;
};

#endif
