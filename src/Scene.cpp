#include "Scene.h"
#include "../third_parties/glm/glm.hpp"
#include "../third_parties/glm/gtc/matrix_transform.hpp"
#include "../third_parties/glm/gtc/type_ptr.hpp"
#include "Application.h"


void Scene::init() {
	blockTexture = loadTexture("src/Rendering/Textures/GLCraft_Atlas.png");
	blockShader = new Shader("src/Rendering/Shaders/Block.vert", "src/Rendering/Shaders/Block.frag");
	float* geometry = nullptr;
	VAO_Length = world.getGeometry(geometry);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* VAO_Length, geometry, GL_STATIC_DRAW);
	
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	blockShader->use();
	blockShader->setInt("material.diffuse", 0);
}

void Scene::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, blockTexture);

	// render container
	//blockShader->use();
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glm::mat4 projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)application.getScreenWidth() / (float)application.getScreenHeight(), 0.1f, 1000.0f);
	glm::mat4 view = mainCamera.GetViewMatrix();
	blockShader->setMat4("projection", projection);
	blockShader->setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	blockShader->setMat4("model", model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, VAO_Length);

};

