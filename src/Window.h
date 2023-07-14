#pragma once
#include "../third_parties/glad/glad.h"
#include "../third_parties/GLFW/include/glfw3.h"
#include <iostream>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Application;

class Window
{
public:
	Window(Application& app): application(app) {}
	Window(const Window&) = delete;
	Window& operator=(Window const&) = delete;

	GLFWwindow * getGLFWwindow() { return window; };

    int init();
    void updateScreen() const;
    void terminate() const { glfwTerminate(); };
    bool shouldClose() const { return glfwWindowShouldClose(window); }

   

private:
	const Application& application;

    GLFWwindow* window;
};

