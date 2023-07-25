#include "Application.h"
#include "Camera.h"

bool firstMouse = false;
float lastX, lastY, deltaTime, lastFrame, timeDiff = 0.0f;
unsigned int counter;
Camera* mainCamera;

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	mainCamera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mainCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Application::processInput()
{
	GLFWwindow* w = window.getGLFWwindow();
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);

	if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		mainCamera->ProcessKeyboard(SPRINT, deltaTime);
	}else
		mainCamera->ProcessKeyboard(WALK, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_V) == GLFW_PRESS) {
		swapInterval = !swapInterval;
		glfwSwapInterval(swapInterval);
	}
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(UP, deltaTime);
}

void Application::init() {
	if (window.init() == -1) {
		std::cerr << "Application : Window.init() Failed." << std::endl;
	}
	scene.init();
	GLFWwindow * w = window.getGLFWwindow();
	glfwSetCursorPosCallback(w, mouse_callback);
	glfwSetScrollCallback(w, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	BlockManager::getInstance();
}

int Application::run() {
	mainCamera = &scene.getMainCamera();
	init();

	// render loop
	// -----------
	while (!window.shouldClose())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		timeDiff += deltaTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0) {
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string	newTitle = "GLCraft - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window.getGLFWwindow(), newTitle.c_str());
			counter = 0;
			timeDiff = 0.0f;
		}
		processInput();
		glClearColor(0.7f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.render();
		window.updateScreen();

	}
	window.terminate();
	return 0;
}