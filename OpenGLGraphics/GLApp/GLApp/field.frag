#version 330 core

#define FIELD 0

in vec2 texCoordsExport;
in vec3 normalExport;
in vec2 UV;

uniform sampler2D grassTex;
uniform uint object;

out vec4 colorsOut;

vec4 fieldTexColor;

void main()
{
   fieldTexColor = texture(grassTex, texCoordsExport);
   if (object == FIELD) colorsOut = vec4(1,0,1,1);
   colorsOut = vec4(1,0,1,1);
}