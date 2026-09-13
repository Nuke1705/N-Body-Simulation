#include "window.hpp"
#include <iostream>

using namespace std;

Engine::Window::Window(int width, int height, const char* name)
{
if (!glfwInit()){
        cout<< "error initialising glfw" << endl;
        return;
    }
    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(width , height, name, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        cout<< "error: window failed creation" << endl;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        cout<< "error" << endl; 
    cout << glGetString(GL_VERSION) << endl;
}

Engine::Window::~Window()
{
    glfwTerminate();
}

bool Engine::Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
    
}

void Engine::Window::pollEvents()
{
    glfwPollEvents();
}

void Engine::Window::swapBuffers()
{
    glfwSwapBuffers(m_window);

}

GLFWwindow *Engine::Window::getNativeWindow()
{
    return m_window;
}
