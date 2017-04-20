#pragma once
#include <glew\GL\glew.h>
#include <glfw\glfw3.h>
#include <iostream>
#include "Time.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
class Window
{
public:
	Window(const int width, const int height, const char* title, bool depeth = true);
	~Window();
	inline int getWidth() const { return m_width; };
	inline int getHeight()const { return m_height; };
	inline bool isClosed()const { return m_isclosed; };
	void update();
	void clear();
	bool isKeyPressed(unsigned int keycode)const;
	bool isMouseButtonPressed(unsigned int keycode)const;
	void getMousePos(double& x, double& y)const { x = mx; y = my; };
	void Window::disableCursor()const;
private:
	GLFWwindow* m_window;
	int m_width, m_height;
	const char* m_title;
	static bool m_Keys[MAX_KEYS];
	static bool m_MouseButtons[MAX_BUTTONS];
	static double mx, my;
	static bool m_isclosed;

private:

	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void window_close_callback(GLFWwindow* window);
};