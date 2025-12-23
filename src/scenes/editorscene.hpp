#ifndef EDITORSCENE_HPP
#define EDITORSCENE_HPP

#include "scene.hpp"
#include "../renderer/shader.hpp"
#include "../renderer/camera.hpp"
#include "../renderer/window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class EditorScene : public Scene
{
private:
    Shader m_shader;
    Shader m_lightSourceShader;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_lightCubeVAO;

    std::vector<glm::vec3> m_cubePositions;
    std::vector<glm::vec3> m_pointLightPositions;

public:
    EditorScene();

    void init() override;
    void render() override;
    void update() override;
    void fixedUpdate(float dt) override;
    void erase() override;
};

#endif
