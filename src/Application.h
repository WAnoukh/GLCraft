#pragma once

#include "Window.h"
#include "../third_parties/GLFW/include/glfw3.h"

#include <iostream>

class Application
{
public:
	Application(): window(*this) {
	}

	int run() {
		init();

		// render loop
		// -----------
		while (!window.shouldClose())
		{
			window.Update();
		}
		window.terminate();
		return 0;
	}

private:
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	Window window;

	void init() {
		if (window.init() == -1) {
			std::cerr << "Application : Window.init() Failed." << std::endl;
		}
	}
};

