//#include "cube.h"
//#include "Shader.h"
//
//
//
////Cube::Cube(vec3 pos)
////{
////	/*Cube::collider = new CubeCollider(&this->position, 1.5f, 1.5f, 1.5f);*/
////}
//
//Shader lightingShader("lighting.vs", "lighting.frag");
//
//GLfloat vertices[] =
//{
//	// Positions            // Normals              // Texture Coords
//	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f, //FRONT
//	0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
//	0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
//	0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
//	-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
//	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
//
//	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f, //BACK
//	0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
//	0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
//	0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
//	-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
//	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
//
//	-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,	//Left
//	-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
//	-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
//	-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
//	-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
//
//	0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f, //RIGHT
//	0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
//	0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
//	0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
//	0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
//	0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
//
//	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f, //Bottom
//	0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
//	0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
//	0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
//
//	-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f, //TOP
//	0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
//	0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
//	0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
//};
//
//vec3 cubePositions[] = {
//	vec3(0.0f,   -0.25f,   0.0f),
//	vec3(2.0f,   0.0f,   0.0f),
//	vec3(-2.0f,  -0.0f,  -0.0f),
//	vec3(-4.0f,  -0.0f,  -0.0f),
//	vec3(4.0f,   -0.0f,  0.0f),
//	//glm::vec3(-1.7f,  3.0f,   -7.5f),	//IF I WANT TO USE MORE CUBES
//	//glm::vec3(1.3f,   -2.0f,  -2.5f),
//	//glm::vec3(1.5f,   2.0f,   -2.5f),
//	//glm::vec3(1.5f,   0.2f,   -1.5f),
//	//glm::vec3(-1.3f,  1.0f,   -1.5f)
//};
//
//unsigned int Cube::setupDrawing(unsigned int listBase)
//{
//	// Setup light VAO
//	GLuint VBO, boxVAO;
//	glGenVertexArrays(1, &boxVAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(boxVAO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//	// Load textures
//	GLuint diffuseMap, specularMap, emissionMap;
//	glGenTextures(1, &diffuseMap);
//	glGenTextures(1, &specularMap);
//	glGenTextures(1, &emissionMap);
//	int width, height;
//	unsigned char *image;
//
//	// Diffuse map
//	image = SOIL_load_image("Images/wood.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	// Specular map
//	image = SOIL_load_image("Images/metal.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, specularMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	// Load textures
//	GLuint cubeTexture = TextureLoading::LoadTexture("Images/wood.png");
//
//	lightingShader.Use();
//	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
//	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);
//}
//
//void Cube::drawScene()
//{
//	//Cube 
//	lightingShader.Use();
//
//	GLint modelLoc2 = glGetUniformLocation(lightingShader.Program, "model");
//	GLint viewLoc2 = glGetUniformLocation(lightingShader.Program, "view");
//	GLint projLoc2 = glGetUniformLocation(lightingShader.Program, "projection");;
//
//	glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, value_ptr(view));
//	glUniformMatrix4fv(projLoc2, 1, GL_FALSE, value_ptr(projection));
//	//// Bind diffuse map
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//	//// Bind specular map
//	//glActiveTexture(GL_TEXTURE1);
//	//glBindTexture(GL_TEXTURE_2D, specularMap);
//
//	glBindVertexArray(boxVAO);
//	mat4 model2(1);
//	model2 = translate(model2, cubePositions[0]);
//	model2 = scale(model2, vec3(0.5f, 0.5f, 0.5f));
//	glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//
//
//	glBindVertexArray(boxVAO);
//	for (GLuint i = 1; i < 5; i++)
//	{
//		model2 = mat4(1);
//		model2 = translate(model2, cubePositions[i]);
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//	}
//	glBindVertexArray(0);
//}