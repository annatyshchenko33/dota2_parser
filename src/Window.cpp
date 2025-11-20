#include "Window.h"
#include <iostream>

Window::Window(int width, int height,const std::string& name)
{
	
	if (!glfwInit())
	{
		std::cerr << "Error" << std::endl;
		window = nullptr;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window error" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
}

Window::~Window()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
	
	glfwTerminate();
}

bool Window::shouldClose() const
{
	return window && glfwWindowShouldClose(window);
}

void Window::clear(float r, float g, float b, float a)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::poolEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	if (window)
	{
		glfwSwapBuffers(window);
	}
}

GLFWwindow* Window::getGLFWwindow() const 
{
	return window;
}