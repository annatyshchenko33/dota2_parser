#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Window {

public:
	Window(int width, int height, const std::string& name);
	~Window();

	bool shouldClose() const;
	void clear(float r, float g, float b, float a);
	void poolEvents();
	void swapBuffers();
	GLFWwindow* getGLFWwindow() const;
private:
	GLFWwindow* window;
};