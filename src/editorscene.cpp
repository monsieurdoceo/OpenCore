#include "editorscene.hpp"

EditorScene::EditorScene() 
    : m_shader("../res/shaders/vertex.vs", "../res/shaders/fragment.fs"),
      m_lightSourceShader("../res/shaders/lightVertex.vs", "../res/shaders/lightFragment.fs"),
      m_texture("../res/textures/container2.png", true, false),
	  m_specularTexture("../res/textures/container2_specular.png", true, false)
{	
    m_cubePositions = 
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    m_pointLightPositions = {
	    glm::vec3( 0.7f,  0.2f,  2.0f),
	    glm::vec3( 2.3f, -3.3f, -4.0f),
	    glm::vec3(-4.0f,  2.0f, -12.0f),
	    glm::vec3( 0.0f,  0.0f, -3.0f)
    };
}

void EditorScene::init()
{
    float vertices[] = { 
		// positions          // normals           // texture coords
        	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	
	       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

	// Asign the VAO, VBO and EBO
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);

	// Binding the VBO buffer to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Asign and creating a array pointer to the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);	

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &m_lightCubeVAO);
	glBindVertexArray(m_lightCubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
		 
    m_shader.use();
	m_shader.setInt("material.diffuse", 0);
	m_shader.setInt("material.specular", 1);
    m_shader.setFloat("material.shininess", 32.0f);

    m_shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    m_shader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    m_shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    m_shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    for (unsigned int i = 0; i < m_pointLightPositions.size(); i++)
    {
        std::string pointLight = std::string("pointLights[") + std::to_string(i) + "].";
            
        m_shader.setVec3(pointLight + "position", m_pointLightPositions[i]);
        m_shader.setVec3(pointLight + "ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        m_shader.setVec3(pointLight + "diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        m_shader.setVec3(pointLight + "specular", glm::vec3(1.0f, 1.0f, 1.0f));
            
        m_shader.setFloat(pointLight + "constant", 1.0f);
        m_shader.setFloat(pointLight + "linear", 0.09f);
        m_shader.setFloat(pointLight + "quadratic", 0.032f);
    }
}

void EditorScene::update() { }

void EditorScene::fixedUpdate(float dt) { }

void EditorScene::render()
{
    Window& window = Window::get();
    Camera& camera = window.getCamera();
    const GLFWvidmode* vidMode = window.getVidMode();

    float aspect = (float) vidMode->width / (float) vidMode->height;
	glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), aspect, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    m_shader.use();
    m_shader.setMat4("projection", projection);	
	m_shader.setMat4("view", view);
    m_shader.setVec3("viewPos", camera.getPosition());
		
	m_texture.use(GL_TEXTURE0);
	m_specularTexture.use(GL_TEXTURE1);
		
	// Draw the element
	glBindVertexArray(m_VAO);
    for (unsigned int i = 0; i < m_cubePositions.size(); i++)
    {
        model = glm::mat4(1.0f);        
        model = glm::translate(model, m_cubePositions[i]);

        float angle = (i == 0) ? 20.0f : 20.0f * i;
        model = glm::rotate(model, glm::radians(angle * (float) glfwGetTime()), glm::vec3(1.0f));
        m_shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }   
    glBindVertexArray(0);

	m_lightSourceShader.use();
	m_lightSourceShader.setMat4("projection", projection);
	m_lightSourceShader.setMat4("view", view);

    glBindVertexArray(m_lightCubeVAO);
    for (unsigned int i = 0; i < m_pointLightPositions.size(); i++)
    {
        glm::vec3 lightPos = m_pointLightPositions[i];

	    model = glm::mat4(1.0f);
	    model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        m_lightSourceShader.setMat4("model", model);
	
	    glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}

void EditorScene::erase()
{   
    // Free the ram and useless buffer and shader
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteVertexArrays(1, &m_lightCubeVAO);
	glDeleteBuffers(1, &m_VBO);

	m_shader.remove();
	m_lightSourceShader.remove();
}

