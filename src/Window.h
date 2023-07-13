#pragma once
#include "../third_parties/glad/glad.h"
#include "../third_parties/GLFW/include/glfw3.h"
#include <iostream>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Application;

class Window
{
public:
	Window(Application& app): application(app) {}
	Window(const Window&) = delete;
	Window& operator=(Window const&) = delete;

    int init();
    void updateScreen() const;

    void terminate() const { glfwTerminate(); };

    void swapBuffers() const { glfwSwapBuffers(window); }

    void pollEvents() const { glfwPollEvents(); }

    bool shouldClose() const { return glfwWindowShouldClose(window); }

    void Update();

private:
	const Application& application;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

    GLFWwindow* window;

    void processInput(GLFWwindow* window);
};

