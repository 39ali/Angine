#define GLEW_STATIC
#include<glew\GL\glew.h>

#include<glfw\glfw3.h>

#include<iostream>



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* m_win = glfwCreateWindow(800, 600, "yoo", nullptr, nullptr);
	if (m_win == nullptr)
	{
		std::cout << "didn't create window" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(m_win);

	glewExperimental = GL_TRUE;
	if (glewInit() != 0)
	{
		std::cout << "glew init error" << std::endl;
		return -1;
	}
	int m_width, m_height;

	glfwGetFramebufferSize(m_win, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);

	glfwSetKeyCallback(m_win, key_callback);


	while (!glfwWindowShouldClose(m_win))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(m_win);
	}

	glfwTerminate();

	return 0;
}


