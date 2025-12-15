#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "inputsystem.hpp"

class Window
{
private:
    std::string m_title;
    GLFWmonitor* m_monitor;
    const GLFWvidmode* m_vidMode;
    GLFWwindow* m_window;

    InputSystem* m_inputSystem;
    Camera m_mainCamera;

    void init();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
    static void window_focus_callback(GLFWwindow* window, int focused) { glfwSetInputMode(window, GLFW_CURSOR, focused ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }
 
    void registerCallbacks();
    void processInput(float dt);

public:
    Window();
    ~Window();

    void render();
    void update();
    void fixedUpdate(float dt);
    void erase();

    GLFWwindow* getWindow() { return m_window; }
    InputSystem* getInputSystem() { return m_inputSystem; }
    Camera& getCamera() { return m_mainCamera; }
};

#endif
