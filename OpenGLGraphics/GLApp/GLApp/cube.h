//#pragma once
//
//#include <fstream>
//#include <cmath>
//#include "vertex.h"
//#include "Textures.h"
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "SOIL2/SOIL2.h"
//
//#include "main.cpp"
//
//#define TURNING_SPEED 30.0
//#define ACCEL 0.000001
//#define MAX_ACCEL 0.25
//
//using namespace glm;
//extern float moveSpeed;
//
//class Cube
//{
//private:
//	vec3 heading = vec3(0.0f, 0.0f, -1.0f);
//public:
//	vec3 jPosition = vec3(xJack, yJack, zJack);
//	vec3 startingHeading = heading;
//	float rotationAngle = 0.0f;
//	Cube(vec3 pos);
//	~Cube();
//
//	//////////////////////////////
//	//////////////////////////////
//	//////////////////////////////
//
//	//Physics attributes
//	GLfloat drag = 0.2f; //Friction 
//	GLfloat mass = 1.5f; 
//	vec3 bowlVelo = vec3(0.0f, 0.0f, 0.0f);
//	GLfloat ang = 180.0f;
//	float Radius = 1.0f;
//	GLfloat timeDifference;
//	GLfloat timeDif;
//	GLfloat lastFrame = 0.0f;
//	bool bollCollision = 0;
//	vec3 force = vec3(0.0f, 0.0f, 0.0f);
//	bool right = 0;
//	bool left = 0;
//	bool space = 0;
//
//	//////////////////////////////
//	//////////////////////////////
//	//////////////////////////////
//
//	unsigned int setupDrawing(unsigned int listBase);
//	void drawScene(Shader lightingShader)
//	{
//
//		mat4 view2(1);
//		mat4 projection2(1);
//
//		// Setup light VAO
//		GLuint VBO, boxVAO;
//		glGenVertexArrays(1, &boxVAO);
//		glGenBuffers(1, &VBO);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		glBindVertexArray(boxVAO);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//		glBindVertexArray(0);
//
//
//		lightingShader.Use();
//		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
//		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);
//
//		//Cube 
//		lightingShader.Use();
//
//		GLint modelLoc2 = glGetUniformLocation(lightingShader.Program, "model");
//		GLint viewLoc2 = glGetUniformLocation(lightingShader.Program, "view");
//		GLint projLoc2 = glGetUniformLocation(lightingShader.Program, "projection");;
//
//		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, value_ptr(view2));
//		glUniformMatrix4fv(projLoc2, 1, GL_FALSE, value_ptr(projection2));
//		//// Bind diffuse map
//		//glActiveTexture(GL_TEXTURE0);
//		//glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//		//// Bind specular map
//		//glActiveTexture(GL_TEXTURE1);
//		//glBindTexture(GL_TEXTURE_2D, specularMap);
//
//		glBindVertexArray(boxVAO);
//		mat4 model2(1);
//		model2 = translate(model2, vec3(xJack,yJack,zJack));
//		model2 = scale(model2, vec3(0.5f, 0.5f, 0.5f));
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//
//		glBindVertexArray(boxVAO);
//		model2 = mat4(1);
//		model2 = translate(model2, vec3(xBowl1,yBowl1,zBowl1));
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glBindVertexArray(boxVAO);
//		model2 = mat4(1);
//		model2 = translate(model2, vec3(xBowl2, yBowl2, zBowl2));
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glBindVertexArray(boxVAO);
//		model2 = mat4(1);
//		model2 = translate(model2, vec3(xBowl3, yBowl3, zBowl3));
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glBindVertexArray(boxVAO);
//		model2 = mat4(1);
//		model2 = translate(model2, vec3(xBowl4, yBowl4, zBowl4));
//		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//	}
//
//	GLuint textures;
//	void loadTextures()
//	{// Load textures
//		GLuint diffuseMap, specularMap, emissionMap;
//		glGenTextures(1, &diffuseMap);
//		glGenTextures(1, &specularMap);
//		glGenTextures(1, &emissionMap);
//		int width, height;
//		unsigned char *image;
//
//		// Diffuse map
//		image = SOIL_load_image("Images/wood.png", &width, &height, 0, SOIL_LOAD_RGB);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		SOIL_free_image_data(image);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//		// Specular map
//		image = SOIL_load_image("Images/metal.png", &width, &height, 0, SOIL_LOAD_RGB);
//		glBindTexture(GL_TEXTURE_2D, specularMap);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		SOIL_free_image_data(image);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		// Load textures
//		GLuint cubeTexture = TextureLoading::LoadTexture("Images/wood.png");
//	}
//
//	void updateVel()
//	{
//		GLfloat currentFrame = glfwGetTime();
//		timeDif = currentFrame - lastFrame;
//		timeDifference = timeDif;
//		lastFrame = currentFrame;
//
//		if (keys[GLFW_KEY_LEFT])
//			{
//				this->left = 1;
//				this->ang -= 25 *(timeDifference * 20);
//				this->left = 0;
//			}
//		if (keys[GLFW_KEY_RIGHT])
//		{
//			this->right = 1;
//			this->ang += 25 * (timeDifference * 20);
//			this->right = 0;
//		}
//	}
//	void start();
//	
//	//void collides(Collider * other);
//};
//
//
////Normal way of doing cubes
////
////glBindVertexArray(boxVAO);
////mat4 model2(1);
////model2 = translate(model2, cubePositions[0]);
////model2 = scale(model2, vec3(0.5f, 0.5f, 0.5f));
//////model2 = rotate(model2, (GLfloat)glfwGetTime()*-5.0f, vec3(0.0f, 1.0f, 0.0f));
////glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
////glDrawArrays(GL_TRIANGLES, 0, 36);
////glBindVertexArray(0);
////
////
////
////glBindVertexArray(boxVAO);
////for (GLuint i = 1; i < 5; i++)
////{
////	model2 = mat4(1);
////	model2 = translate(model2, cubePositions[i]);
////	glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
////	
////	glDrawArrays(GL_TRIANGLES, 0, 36);
////}
////glBindVertexArray(0);
