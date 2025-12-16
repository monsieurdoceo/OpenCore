#include "window.hpp"

Window* Window::m_instance = nullptr;

void Window::changeScene(int index)
{
    if (index >= 0 && index < m_scenes.size())
    {
        m_currentSceneIndex = index;
        getCurrentScene().init();
    }
    else std::cerr << "ERROR: Invalid scene index: " << index << std::endl;
}

Scene& Window::getCurrentScene()
{
    if (m_currentSceneIndex == -1 || m_currentSceneIndex >= m_scenes.size()) throw std::out_of_range("Attempted to access scene with invalid index.");

    return *m_scenes[m_currentSceneIndex];
}

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
    // Clear the screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_currentSceneIndex != -1) getCurrentScene().render();
    	
	// Get all events and register them on the window + reset inputs frames
	glfwSwapBuffers(m_window);
	m_inputSystem->endFrame();
}

void Window::update()
{
    glfwPollEvents(); 
    if (m_currentSceneIndex != -1) getCurrentScene().update();
}

void Window::fixedUpdate(float dt)
{
    processInput(dt);
    if (m_currentSceneIndex != -1) getCurrentScene().fixedUpdate(dt);
}

void Window::erase()
{
    if (m_currentSceneIndex != -1) getCurrentScene().erase();

    glfwDestroyWindow(m_window);
	glfwTerminate();
}

