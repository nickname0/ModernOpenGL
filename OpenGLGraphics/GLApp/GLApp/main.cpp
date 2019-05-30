#include <iostream>
#include <cmath>
#include <string>
#include <vector>

//GLEW
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
//GLFW
#include <GLFW/glfw3.h>

//SOIL
#include "SOIL2/SOIL2.h"

//GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
//#include <glm/gtx/rotate_vector.inl>
#include <glm/gtx/rotate_vector.hpp>

//other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Textures.h"
#include "vertex.h"
#include "getbmp.h"
#include "CubeColliders.h"
#include "shader2.h"

#define TURNING_SPEED 90.0

using namespace std;
using namespace glm;

//static VertexWtihNormal *sphereVerticesNor = NULL;
//static unsigned int *sphereIndices = NULL;
//static Sphere testSphere;

const GLint WIDTH = 1200, HEIGHT = 960;
int SCREEN_WIDTH, SCREEN_HEIGHT;
static mat4 model1 = mat4(1.0);
static mat4 model2 = mat4(1.0);

static unsigned int object;
//Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement(); //Include Camera.H
void update();
void printInteraction(void);

//Camera
Camera camera(vec3(0.0f, 2.0f, 6.0f));
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool firstMouse = true;
bool keys[1024];

unsigned int grassTexLoc, objectLoc;
static BitMapFile *images[1];

//Position of the light source
vec3 lightPos(.0f, 0.0f, 5.0f);

//heading
int toggle = 0;
vec3 heading = vec3(0.0f, 0.0f, -1.0f);
vec3 sHeading = heading;
int pressed = 0;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

GLfloat skyboxVertices[] = {
	// Positions
	-1.0f,  1.0f, -1.0f, // FRONT
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f, //LEFT
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f, //Right
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f, //back
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f, //TOP
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,


	-1.0f, -1.0f, -1.0f, //Bottom
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};


GLfloat vertices[] =
{
	// Positions            // Normals              // Texture Coords
	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f, //FRONT
	0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f, //BACK
	0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,	//Left
	-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f, //RIGHT
	0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f, //Bottom
	0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f, //TOP
	0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
};
#pragma region Stuff 1
// Positions all containers
vec3 cubePositions[] = {
	vec3(0.0f,   -0.25f,   0.0f),
	vec3(2.0f,   0.0f,   0.0f),
	vec3(-2.0f,  -0.0f,  -0.0f),
	vec3(-4.0f,  -0.0f,  -0.0f),
	vec3(4.0f,   -0.0f,  0.0f),
	//glm::vec3(-1.7f,  3.0f,   -7.5f),	//IF I WANT TO USE MORE CUBES
	//glm::vec3(1.3f,   -2.0f,  -2.5f),
	//glm::vec3(1.5f,   2.0f,   -2.5f),
	//glm::vec3(1.5f,   0.2f,   -1.5f),
	//glm::vec3(-1.3f,  1.0f,   -1.5f)
};

GLfloat xJack = 0.0f;		//Jack's position
GLfloat yJack = -0.25f;
GLfloat zJack = 0.0f;
GLfloat xBowl1 = 2.0f;			//Bowl's position
GLfloat yBowl1 = 0.0f;		
GLfloat zBowl1 = 0.0f;		
GLfloat xBowl2 = -2.0f;			//Bowl's position
GLfloat yBowl2 = 0.0f;			
GLfloat zBowl2 = 0.0f;			
GLfloat xBowl3 = 4.0f;			//Bowl's position
GLfloat yBowl3 = 0.0f;			
GLfloat zBowl3 = 0.0f;			
GLfloat xBowl4 = -4.0f;			//Bowl's position
GLfloat yBowl4 = 0.0f;			
GLfloat zBowl4 = 0.0f;

GLfloat xDirJ, zDirJ, xDirB1, zDirB1, xDirB2, zDirB2, xDirB3, zDirB3, xDirB4, zDirB4;
bool collideJack = false;
bool collideBowl1 = false;
bool collideBowl2 = false;
bool collideBowl3 = false;
bool collideBowl4 = false;

static unsigned int
programId,
vertexShaderId,
fragmentShaderId;

vec3 jackPos =vec3(xJack, yJack, zJack);
vec3 bowlPos1 =vec3(xBowl1, yBowl1, zBowl1);
vec3 bowlPos2 =vec3(xBowl2, yBowl2, zBowl2);
vec3 bowlPos3 =vec3(xBowl3, yBowl3, zBowl3);
vec3 bowlPos4 =vec3(xBowl4, yBowl4, zBowl4);


//Physics
const float decrease = 0.1f;
float increase = 0.5f;
float maxSpeed = 5.0f;
float moveSpeed = 0.0f;
float radius = 90.0f;
int toggles = 0;

unsigned int texture[1];

float rotationAngle = 0.0f;

//Main function
int main()
{
	// Init GLFW
	//makeCube();
	glfwInit();

	// Set GLFW options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", nullptr, nullptr);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	printInteraction();

	if (nullptr == window)
	{
		cout << "FAILED to create GLFW window " << endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	//Set the required callback function
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	//glfwSetScrollCallback(window, ScrollCallback);

	//GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	//Initialize GLEW to setup the OpenGL function pointers
	if (GLEW_OK != glewInit())
	{
		cout << "Failed to initialize GLEW" << endl;

		return -1;
	}
	//Viewport Dimension
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
#pragma endregion
	glEnable(GL_DEPTH_TEST);
	// Setup and compile our shaders
	Shader modelShader("modelLoading.vs", "modelLoading.frag");
	Shader skyboxShader("skybox.vs", "skybox.frag");
	Shader lightingShader("lighting.vs", "lighting.frag");

	// Load models
	Model ourModel("Models/Bench/bench.3ds");
	Model ourModel2("Models/House/house.obj");
	Model ourModel3("Models/Field/field.3DS");

	// Setup light VAO
	GLuint boxVBO, boxVAO;
	glGenVertexArrays(1, &boxVAO);
	glGenBuffers(1, &boxVBO);

	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(boxVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Load textures
	GLuint diffuseMap, specularMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	int width, height;
	unsigned char *image;

	// Diffuse map
	image = SOIL_load_image("Images/wood.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	// Specular map
	image = SOIL_load_image("Images/metal.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Setup skybox VAO
	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glBindVertexArray(0);

	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("Images/skybox3/front.tga"); // THIS IS THE CORRECT ORDER
	faces.push_back("Images/skybox3/back.tga");
	faces.push_back("Images/skybox3/top.tga");
	faces.push_back("Images/skybox3/bottom.tga");
	faces.push_back("Images/skybox3/right.tga");
	faces.push_back("Images/skybox3/left.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	mat4 projection = perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);//100 or1000

	objectLoc = glGetUniformLocation(programId, "object");

	images[0] = getbmp("Images/grass.bmp");

	// Bind grass image.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, images[0]->sizeX, images[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, images[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	grassTexLoc = glGetUniformLocation(programId, "grassTex");
	glUniform1i(grassTexLoc, 0);
	#pragma region stuff2
	//Game Loop
	while (!glfwWindowShouldClose(window))
	{
		
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//update bowl speed

		//check for events/input. (key pressed, mouse moved etc.)
		glfwPollEvents();
		DoMovement();//Include Camera.h
		update();
		//handle game logic

		//render
		//clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//LIGHTINING
		lightingShader.Use();
		//GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
		GLint lightDirLoc = glGetUniformLocation(lightingShader.Program, "light.direction");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(lightDirLoc, -0.2f, -2.0f, -1.3f);
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), .3f, 0.3f, .3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 1.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
		
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		mat4 model(1);
		mat4 view(1);
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(0);
#pragma endregion
#pragma region cube
		//Cube 
		lightingShader.Use();

		GLint modelLoc2 = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc2 = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc2 = glGetUniformLocation(lightingShader.Program, "projection");

		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc2, 1, GL_FALSE, value_ptr(projection));

		glBindVertexArray(boxVAO);
		mat4 model2(1);
		model2 = translate(model2, jackPos);
		model2 = scale(model2, vec3(0.5f, 0.5f, 0.5f));
		//model2 = rotate(model2, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	
		glBindVertexArray(boxVAO);
		model2 = mat4(1);
		model2 = translate(model2, bowlPos1);
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glBindVertexArray(boxVAO);
		model2 = mat4(1);
		model2 = translate(model2, bowlPos2);
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glBindVertexArray(boxVAO);
		model2 = mat4(1);
		model2 = translate(model2, bowlPos3);
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glBindVertexArray(boxVAO);
		model2 = mat4(1);
		model2 = translate(model2, bowlPos4);
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
#pragma endregion

		//model Shader
		modelShader.Use();


		mat4 model01(1);
		model01 = translate(model01, vec3(-25.0, -1.0f, -25.0f)); // Translate it down a bit so it's at the center of
		model01 = scale(model01, vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so sca
																//model01 = rotate(model01, 90.0f, vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model01));
		ourModel2.Draw(modelShader);

		view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, value_ptr(view));


		// Draw the loaded model
		//Bench
		model1 = mat4(1);
		model1 = translate(model1,vec3(-15.0f,-.55f,1.0f)); // Translate it down a bit so it's at the center of the scene
		model1 = scale(model1, vec3(0.0002f, 0.0002f, 0.0002f));	// It's a bit too big for our scene, so scale it down
		model1 = rotate(model1,90.0f,vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model1));
		ourModel.Draw(modelShader);

		model1 = mat4(1);
		model1 = translate(model1, vec3(15.0f, -.55f, 1.0f)); // Translate it down a bit so it's at the center of the scene
		model1 = scale(model1, vec3(0.0002f, 0.0002f, 0.0002f));	// It's a bit too big for our scene, so scale it down
		model1 = rotate(model1, -90.0f, vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model1));
		ourModel.Draw(modelShader);

		model1 = mat4(1);
		model1 = translate(model1, vec3(18.0f, -.55f, -10.0f));
		model1 = scale(model1, vec3(0.0002f, 0.0002f, 0.0002f));
		model1 = rotate(model1, 55.0f, vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model1));
		ourModel.Draw(modelShader);

		model1 = mat4(1);
		model1 = translate(model1, vec3(-18.0f, -.55f, -10.0f));
		model1 = scale(model1, vec3(0.0002f, 0.0002f, 0.0002f));
		model1 = rotate(model1, -55.0f, vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model1));
		ourModel.Draw(modelShader);

//Field
mat4 model111(1.0f);
model111 = translate(model111, vec3(0.0f, -0.66f, -50.0f)); // Translate it down a bit so it's at the center of the scene
model111 = scale(model111, vec3(1.002f, 1.002f, 1.002f));	// It's a bit too big for our scene, so scale it down
model111 = rotate(model111, -55.0f, vec3(1.0f, .0f, 0.0f)); // 30 close to perfect
glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, value_ptr(model111));
ourModel3.Draw(modelShader);


#pragma region Field + Skybox

//Draw SkyBox last one
glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
skyboxShader.Use();
view = mat4(mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix

glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, value_ptr(view));
glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));

// skybox cube
glBindVertexArray(skyboxVAO);
glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
glDrawArrays(GL_TRIANGLES, 0, 36);
glBindVertexArray(0);
glDepthFunc(GL_LESS); // Set depth function back to default

//swap the screen buffer
glfwSwapBuffers(window);
	}
#pragma endregion
	glDeleteVertexArrays(1, &boxVAO);
	glDeleteBuffers(1, &boxVBO);
	//terminate GLFW, clearing any resources allocated by GLFW
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void update()
{

	float turningSpeed = TURNING_SPEED * (deltaTime / 100.0f);
	//moveSpeed = (increase + decrease) *deltaTime / 2;
	//if (keys[GLFW_KEY_DOWN])
	//{
	//	moveSpeed += 0.001f * 0.2/ 2;
	//	zJack -= moveSpeed;
	//}
	/*if (keys[GLFW_KEY_0])
	{
		moveSpeed
	}*/
	if (keys[GLFW_KEY_UP] && pressed == 0)
	{
		moveSpeed = 0.2f;
		/*moveSpeed += 0.01f * (deltaTime / 2);*/
		zJack * moveSpeed;
		toggle = 2;
		pressed = 1;
		//jackPos += vec3(0.0f, 0.0f, -1.0f) * moveSpeed;
		cout << moveSpeed << endl;
		cout << pressed << endl;
		//increase += -0.5f;
		/*moveSpeed = maxSpeed;*/
		//moveSpeed += 0.01f * 2;
		//zJack += moveSpeed;
	}
	if (pressed == 1)
	{
		bowlPos1 = vec3(0.0f, 0.0f, 0.0f);
		cout << pressed << endl;
	}
	if (keys[GLFW_KEY_UP] && pressed == 2)
	{
		moveSpeed = 0.2f;
	/*moveSpeed += 0.01f * (deltaTime / 2);*/
		zBowl1 * moveSpeed;
	//toggle = 2;
		pressed = 2;
		cout << pressed << endl;
	}
		/*cout << moveSpeed << endl;	
	if (keys[GLFW_KEY_DOWN])
	{

	}*/
	if (toggle == 2) {
		jackPos += vec3(0.0f, 0.0f, -1.0f) * moveSpeed;
	}
	if (keys[GLFW_KEY_LEFT])
	{
		toggles = 1;

		//heading = rotate(sHeading, radians(rotationAngle), vec3(0.0, 1.0, 0.0));
		cout << toggle << endl;
	}
	if (toggle == 2 && toggles == 1)
	{
		zJack * moveSpeed;
		jackPos += vec3(0.0f + (rotationAngle), 0.0f,0.0f) * moveSpeed;
	}
	//increase -= decrease * deltaTime / 1000;
	
	if (moveSpeed > 0.15 && toggles== 1)
	{
		rotationAngle += (turningSpeed) /deltaTime;
	}

	if (moveSpeed> 0)
	{
		moveSpeed -= 0.4 * deltaTime/2;
	}
	if (moveSpeed < 0)
	{
		moveSpeed = 0;
	}
	
	//cout << moveSpeed << endl;
	//glutPostRedisplay();
}
//Moves the cubes position based on the input

void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Camera Control - WASD + Mouse." << endl;
	cout << "Left/Right keys to change angel." << endl;
	cout << "Up/Space to release the ball." << endl;
	cout << "Esc to exit the program." << endl;

}
// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
