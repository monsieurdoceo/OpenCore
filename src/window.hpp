#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "inputsystem.hpp"
#include "scene.hpp"

class Window
{
private:
    static Window* m_instance;

    std::vector<std::unique_ptr<Scene>> m_scenes;
    int m_currentSceneIndex = -1;

    std::string m_title;
    GLFWmonitor* m_monitor;
    const GLFWvidmode* m_vidMode;
    GLFWwindow* m_window;

    InputSystem* m_inputSystem;
    Camera m_mainCamera;

    Window();

    void init(); 
    void registerCallbacks();
    void processInput(float dt);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
    static void window_focus_callback(GLFWwindow* window, int focused) { glfwSetInputMode(window, GLFW_CURSOR, focused ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }

public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    virtual ~Window();

    static Window& get()
    {
        if (m_instance == nullptr) m_instance = new Window();

        return *m_instance;
    }

    template<typename T, typename... Args>
    void addScene(Args... args) { m_scenes.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)); }
    void changeScene(int index);
    Scene& getCurrentScene();

    void render();
    void update();
    void fixedUpdate(float dt);
    void erase();

    GLFWwindow* getWindow() { return m_window; }
    const GLFWvidmode* getVidMode() const { return m_vidMode; }
    InputSystem* getInputSystem() { return m_inputSystem; }
    Camera& getCamera() { return m_mainCamera; }
};

#endif
