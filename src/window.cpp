#include "window.hpp"

void Window::init()
{
    // Initialising glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Window::registerCallbacks()
{
    glfwSetCursorPosCallback(m_window, InputSystem::mousePosCallback);
	glfwSetMouseButtonCallback(m_window, InputSystem::mouseButtonCallback);
	glfwSetScrollCallback(m_window, InputSystem::mouseScrollCallback);
	glfwSetKeyCallback(m_window, InputSystem::keyCallback);

	glfwSetWindowFocusCallback(m_window, window_focus_callback);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::processInput(float dt)
{
    // Set up the camera movement (mouse and keyboard)
	m_mainCamera.processMouseMovement(m_inputSystem->getMouseDirectionX(), m_inputSystem->getMouseDirectionY());
	if (m_inputSystem->isKeyPressed(GLFW_KEY_W)) m_mainCamera.processKeyboard(FORWARD, dt);
	if (m_inputSystem->isKeyPressed(GLFW_KEY_S)) m_mainCamera.processKeyboard(BACKWARD, dt);
	if (m_inputSystem->isKeyPressed(GLFW_KEY_A)) m_mainCamera.processKeyboard(LEFT, dt);
	if (m_inputSystem->isKeyPressed(GLFW_KEY_D)) m_mainCamera.processKeyboard(RIGHT, dt);

	// Close the window
	if (m_inputSystem->isKeyPressed(GLFW_KEY_SPACE)) glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

Window::Window()
{
    init();

    // Creating a window
	m_monitor = glfwGetPrimaryMonitor();
	m_vidMode = glfwGetVideoMode(m_monitor);

	m_window = glfwCreateWindow(m_vidMode->width, m_vidMode->height, "OpenCore", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Init GLad and create a context to the window
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

    glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	m_inputSystem = InputSystem::getInstance();
	m_mainCamera = Camera(glm::vec3(0.0f, 1.0f, 3.0f));

	glEnable(GL_DEPTH_TEST);
    registerCallbacks();
}

Window::~Window()
{
    erase();
}

void Window::render()
{
     // Creating a shader
	Shader shader("../res/shaders/vertex.vs", "../res/shaders/fragment.fs");
	Shader lightSourceShader("../res/shaders/lightVertex.vs", "../res/shaders/lightFragment.fs");

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

	// Creating a VBO[Vertex Buffer Object], a VAO[Vertex Array Object] and a EBO[Element Buffer Object]
	unsigned int VBO, VAO;
	// Asign the VAO, VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	// Binding the VBO buffer to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Asign and creating a array pointer to the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);	

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
		
	Texture texture = Texture("../res/textures/container2.png", true, false);
	Texture specularTexture = Texture("../res/textures/container2_specular.png", true, false);

    glm::vec3 cubePositions[] = 
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

    glm::vec3 pointLightPositions[] = {
	    glm::vec3( 0.7f,  0.2f,  2.0f),
	    glm::vec3( 2.3f, -3.3f, -4.0f),
	    glm::vec3(-4.0f,  2.0f, -12.0f),
	    glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    // Clear the screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

	shader.use();
	shader.setVec3("viewPos", m_mainCamera.getPosition());

    shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    for (unsigned int i = 0; i < 4; i++)
    {
        std::string pointLight = std::string("pointLights[") + std::to_string(i) + "].";
            
        shader.setVec3(pointLight + "position", pointLightPositions[i]);
        shader.setVec3(pointLight + "ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3(pointLight + "diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3(pointLight + "specular", glm::vec3(1.0f, 1.0f, 1.0f));
            
        shader.setFloat(pointLight + "constant", 1.0f);
        shader.setFloat(pointLight + "linear", 0.09f);
        shader.setFloat(pointLight + "quadratic", 0.032f);
    }

	shader.setFloat("material.shininess", 32.0f);
		
    float aspect = (float) m_vidMode->width / (float) m_vidMode->height;
	glm::mat4 projection = glm::perspective(glm::radians(m_mainCamera.getZoom()), aspect, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

	glm::mat4 view = m_mainCamera.getViewMatrix();	
	shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
		
	texture.use(GL_TEXTURE0);
	specularTexture.use(GL_TEXTURE1);
		
	// Draw the element
	glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 8; i++)
    {
        model = glm::mat4(1.0f);
        glm::vec3 cubePosition = cubePositions[i];        
        model = glm::translate(model, cubePosition);

        float angle = (i == 0) ? 20.0f : 20.0f * i;
        model = glm::rotate(model, glm::radians(angle * (float) glfwGetTime()), glm::vec3(1.0f));
        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

	lightSourceShader.use();
	lightSourceShader.setMat4("projection", projection);
	lightSourceShader.setMat4("view", view);

    glBindVertexArray(lightCubeVAO);
    for (unsigned int i = 0; i < 4; i++)
    {
        glm::vec3 lightPos = pointLightPositions[i];

	    model = glm::mat4(1.0f);
	    model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightSourceShader.setMat4("model", model);
	
	    glDrawArrays(GL_TRIANGLES, 0, 36);
    }
	
	// Get all events and register them on the window + reset inputs frames
	glfwSwapBuffers(m_window);
	m_inputSystem->endFrame();
}

void Window::update()
{
    glfwPollEvents(); 
}

void Window::fixedUpdate(float dt)
{
    processInput(dt);
}

void Window::erase()
{
    glfwDestroyWindow(m_window);
	glfwTerminate();
}

