#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "time.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Time time);
void processInput(GLFWwindow* window, Time time)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, time.getDeltaTime());
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffSet = xpos - lastX;
	float yoffSet = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffSet *= sensitivity;
	yoffSet *= sensitivity;

	camera.processMouseMovement(xoffSet, yoffSet);
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenCore", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Init GLad and create a context to the window
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Creating a shader
	Shader shader("../res/shaders/vertex.vs", "../res/shaders/fragment.fs");
	Shader lightSourceShader("../res/shaders/lightVertex.vs", "../res/shaders/lightFragment.fs");

	float vertices[] = {
    		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

    		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);	

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
		
	Time time;	

	// Run till the window close
	while (!glfwWindowShouldClose(window))
	{
		// Update Time
		time.update();

		// Register Input
		processInput(window, time);

		// Clear the screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("lightPos", lightPos);
		shader.setVec3("viewPos", camera.getPosition());

		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 view = camera.getViewMatrix();	
		shader.setMat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);
		
		// Draw the element
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightSourceShader.use();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);
		lightSourceShader.setVec3("lightPos", lightPos);

		lightPos.x = 2.0f * sin(glfwGetTime());
		lightPos.y = sin(glfwGetTime() / 3.0f);
		lightPos.z = 1.5f * cos(glfwGetTime());

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightSourceShader.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Get all events and register them on the window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free the ram and useless buffer and shader
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	shader.remove();
	lightSourceShader.remove();

	glfwTerminate();
	return 0;
}

