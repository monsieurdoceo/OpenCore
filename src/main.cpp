#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "inputsystem.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void window_focus_callback(GLFWwindow* window, int focused);
void window_focus_callback(GLFWwindow* window, int focused)
{
	glfwSetInputMode(window, GLFW_CURSOR, focused ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

int main()
{
	// Initialising glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Creating a window
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenCore", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Init GLad and create a context to the window
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	InputSystem* inputSystem = InputSystem::getInstance();
	Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(window, InputSystem::mousePosCallback);
	glfwSetMouseButtonCallback(window, InputSystem::mouseButtonCallback);
	glfwSetScrollCallback(window, InputSystem::mouseScrollCallback);
	glfwSetKeyCallback(window, InputSystem::keyCallback);

	glfwSetWindowFocusCallback(window, window_focus_callback);	

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
	Time time;	

	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

	// Run till the window close
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// Update Time
		time.update();

		// Clear the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setVec3("viewPos", camera.getPosition());
		shader.setVec3("light.position", lightPos);

		shader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader.setFloat("material.shininess", 32.0f);
		
		float aspect = (float) mode->width / (float) mode->height;
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), aspect, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 view = camera.getViewMatrix();	
		shader.setMat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);

		texture.use(GL_TEXTURE0);
		specularTexture.use(GL_TEXTURE1);
		
		// Draw the element
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightSourceShader.use();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);
	
		lightPos.x = 2.0f * sin(glfwGetTime());
		lightPos.y = sin(glfwGetTime() / 3.0f);
		lightPos.z = 1.5f * cos(glfwGetTime());

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightSourceShader.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		if (inputSystem->isKeyPressed(GLFW_KEY_SPACE))
		{
			glfwSetWindowShouldClose(window, true);
		}

		// Get all events and register them on the window + reset inputs frames
		glfwSwapBuffers(window);
		inputSystem->endFrame();
	}

	// Free the ram and useless buffer and shader
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	shader.remove();
	lightSourceShader.remove();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

