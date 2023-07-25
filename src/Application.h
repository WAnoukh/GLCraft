#pragma once
#include "../third_parties/glad/glad.h"
#include "../third_parties/GLFW/include/glfw3.h"
#include "Window.h"
#include "Scene.h"
#include <iostream>


class Application
{
public:
	Application(): window(*this),scene(*this) {}

	int run();

	unsigned int getScreenWidth() const { return SCR_WIDTH; };
	unsigned int getScreenHeight() const { return SCR_HEIGHT; };

private:
	const unsigned int SCR_WIDTH = 1800;
	const unsigned int SCR_HEIGHT = 1500;
	int swapInterval = 0;
	Window window;
	Scene scene;

	void init();
	void processInput();
};

