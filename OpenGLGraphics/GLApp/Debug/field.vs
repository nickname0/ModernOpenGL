#version 330 core

#define FIELD 0

layout(location=0) in vec4 fieldCoords;
layout(location=1) in vec2 fieldTexCoords;

uniform mat4 modelViewMat;
uniform mat4 projMat;
uniform uint object;

out vec2 texCoordsExport;
out vec3 normalExport;

vec4 coords;

void main(void)
{
      if (object == FIELD)
    {
		coords = fieldCoords;
		texCoordsExport = fieldTexCoords;
	}
	gl_Position = projMat * modelViewMat * coords;
}