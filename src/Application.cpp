#include "Application.h"
#include "Camera.h"

bool firstMouse = false;
float lastX, lastY, deltaTime, lastFrame;
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

	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(RIGHT, deltaTime);
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
		processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.render();
		window.updateScreen();

	}
	window.terminate();
	return 0;
}