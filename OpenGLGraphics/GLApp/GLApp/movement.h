//#pragma once
//
//#include <vector>
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//using namespace std;
//using namespace glm;
//
//enum Cube_Movement
//{
//	FORWARDC,
//	LEFTC,
//	RIGHTC
//};
//
//const GLfloat ACCELERATION = 1.0f;
//const GLfloat SENSIVITY = 0.25f;
//
//class Cube
//{
//public:
//	//Cube(vec3 position = vec3(0.0f, 0.0f, 0.0f), ) 
//	//add movementSpeed
//
//	void ProccessKey(Cube_Movement direction, GLfloat deltaTime)
//	{
//		GLfloat velocity = this->accel * deltaTime;
//
//		if (FORWARD == direction)
//		{
//			this->position += this->front * velocity;
//		}
//		if (LEFT == direction)
//		{
//			this->position -= this->right * velocity;
//		}
//		if (RIGHT == direction)
//		{
//			this->position += this->right * velocity;
//		}
//	}
//
//	vec3 GetPos()
//	{
//		return this->position;
//	}
//
//private:
//	//Cube attributes
//
//	vec3 position,front,right;
//	
//	//Cube options
//	GLfloat accel;
//	GLfloat keySensitivity;
//
//	//void updateCubeVectors()
//	//{
//	//	vec3 front;
//	//	this->front = normalize(front);
//	//	this->right = normalize(cross(this->front, this->left));
//	//	//this->left = normalize(cross(this->right, this->front));
//	//}
//	
//
//
//
//};