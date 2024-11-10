#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#include "GL/glew.h"

#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../lib/glfw/glfw3.h"

#include "../project/Buffer.h"
#include "../project/Shader.h"
#include "../project/World.h"
#include "../project/Camera.h"
#include "../project/Mesh.h"
#include "../project/Model.h"
#include "../project/State.h"
#include "../project/Texture.h"
#include "../project/Material.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

std::string GetStringFromFile(const std::string& fileName)
{
	std::ifstream stream(fileName.c_str(), std::ios_base::binary);
	if (!stream)
	{
		std::cerr << "ERROR: Could not open file " << fileName << std::endl;
		return "";
	}
	std::stringstream sstream;
	sstream << stream.rdbuf();
	std::string fileContents = sstream.str();
	return fileContents;
}

bool Initialize()
{ 
	if (glewInit() != GLEW_OK) // Returns 0 if suceess, must be called after setting openGL context - glfwMakeContextCurrent(win)
	{
		printf("Failed to initialize glew");
		return false;
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Enable scissor test
	glEnable(GL_SCISSOR_TEST);

	// Create shader object with the vertex and fragment shaders
	std::string vertexShaderPath = "data/vertex.glsl";
	std::string fragmentShaderPath = "data/fragment.glsl";
	Shader shader = Shader(GetStringFromFile(vertexShaderPath), GetStringFromFile(fragmentShaderPath));
	State::defaultShader = std::make_shared<Shader>(shader);
	State::defaultShader->Use();
	return true;
}

std::vector<Vertex> CreateVertices(const std::vector<glm::vec3>& positions)
{
	std::vector<Vertex> result;
	glm::vec3 color(1.0f, 1.0f, 1.0f); // White color for all vertices
	glm::vec2 texCoords[4] = { {0, 0}, {0, 1}, {1, 1}, {1, 0} };

	for (int i = 0; i < positions.size(); ++i) 
	{
		result.emplace_back(positions[i], color, texCoords[i % 4]);
	}
	return result;
}

int main() {

	// Init glfw
	if (!glfwInit()) 
	{
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// Create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) 
	{
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// Used to define the rectangular region where rendered fileContents will be displayed
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Used to define a sub-section of the screen that should be rendered - for UI?
	glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); 

	if (!Initialize())
	{
		return -1;
	}

	glfwSetWindowTitle(win, "3D Programming Assignment #3");

	// These are used to simplify vertex creation code
	std::vector<glm::vec3> baseVertices = 
	{
		{-0.5f, -0.5f, 0.0f}, // Bottom-left front  - 0
		{-0.5f,  0.5f, 0.0f}, // Top-left front     - 1
		{ 0.5f,  0.5f, 0.0f}, // Top-right front    - 2
		{ 0.5f, -0.5f, 0.0f}, // Bottom-right front - 3

		{-0.5f, -0.5f, -1.0f}, // Bottom-left back  - 4
		{-0.5f,  0.5f, -1.0f}, // Top-left back     - 5
		{ 0.5f,  0.5f, -1.0f}, // Top-right back    - 6
		{ 0.5f, -0.5f, -1.0f}  // Bottom-right back - 7
	};
	
	// Vertices using the vector above
	std::vector<Vertex> verticesSides = CreateVertices({
		baseVertices[0], baseVertices[1], baseVertices[2], baseVertices[3], // Side Front
		baseVertices[3], baseVertices[2], baseVertices[6], baseVertices[7], // Side Right
		baseVertices[5], baseVertices[4], baseVertices[7], baseVertices[6], // Side Back
		baseVertices[4], baseVertices[5], baseVertices[1], baseVertices[0]  // Side Left
	});

	std::vector<Vertex> verticesTop = CreateVertices({
		baseVertices[1], baseVertices[5], baseVertices[6], baseVertices[2], // Top
		baseVertices[0], baseVertices[4], baseVertices[7], baseVertices[3]  // Bottom
	});

	// Indices for side and top/bottom faces
	std::vector<uint16_t> indicesSides = 
	{
		0, 2, 1,
		0, 3, 2,      // Side Front

		4, 6, 5,
		4, 7, 6,      // Side Right

		8, 10, 9,
		8, 11, 10,   // Side Back

		12, 14, 13,
		12, 15, 14 // Side Left
	};

	std::vector<uint16_t> indicesTop = 
	{
		0, 2, 1, 
		0, 3, 2,     // Top

		4, 6, 5,
		4, 7, 6      // Bottom
	};

	// Texture
	SharedPtr<Texture> textureBoxSide = Texture::Load("data/front.png");
	SharedPtr<Texture> textureBoxTop = Texture::Load("data/top.png");

	// Material
	SharedPtr<Material> materialBoxSide = std::make_shared<Material>(textureBoxSide, nullptr);
	SharedPtr<Material> materialBoxTop = std::make_shared<Material>(textureBoxTop, nullptr);


	// Create buffers
	std::shared_ptr<Buffer> bufferSides = std::make_shared<Buffer>(verticesSides, indicesSides);
	std::shared_ptr<Buffer> bufferTop = std::make_shared<Buffer>(verticesTop, indicesTop);

	// Create shader object with the vertex and fragment shaders
	std::string vertexShaderPath = "data/vertex.glsl";
	std::string fragmentShaderPath = "data/fragment.glsl";
	Shader shader = Shader(GetStringFromFile(vertexShaderPath), GetStringFromFile(fragmentShaderPath));
	SharedPtr<Shader> shaderPtr = std::make_shared<Shader>(shader);

	// Create the world
	World* world = new World();


	// Create the mesh
	SharedPtr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->AddBuffer(bufferSides, *materialBoxSide);
	mesh->AddBuffer(bufferTop, *materialBoxTop);

	SharedPtr<Model> model = std::make_shared<Model>(mesh);
	model->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	model->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	world->AddEntity(model);

	// Setup Camera
	SharedPtr<Camera> camera = std::make_shared<Camera>();
	camera->SetPosition(glm::vec3(0.0f, 0.5f, 3.0f));
	camera->SetRotation(glm::vec3(-20.0f, 0.0f, 0.0f));
	camera->SetProjection(glm::perspective(glm::radians(60.0f), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.1f, 100.0f));
	camera->SetViewport(glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	camera->SetClearColor(glm::vec3(0.8f));
	world->AddEntity(camera);


	// Main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE)) 
	{
		// Get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		world->Tick(deltaTime);
		world->Draw();

		// Refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}