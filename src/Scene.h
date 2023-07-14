#pragma once
#include "World.h"
#include "../third_parties/glad/glad.h"
#include "Rendering/TextureLoader.h"
#include "Rendering/shader_s.h"
#include "Camera.h"

class Application;

class Scene
{
public:
	Camera& getMainCamera() { return mainCamera; };

	Scene(Application& app):application(app), mainCamera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

	void init();
	
	void render();

private:
	Application& application;
	World world;
	unsigned int blockTexture;
	Shader* blockShader;
	unsigned int VBO, VAO;
	size_t VAO_Length;
	Camera mainCamera;
};

