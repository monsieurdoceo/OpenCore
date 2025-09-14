#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "texture.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window);
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	const float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
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

	// Creating a shader
	Shader shader("../res/shaders/vertex.vs", "../res/shaders/fragment.fs");

	float vertices[] = {
    		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     	    	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     	 	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	       	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	       	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
       		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

   		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	// Asign and creating a array pointer to the color
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);	

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Creating textures 
	Texture texture1("../res/textures/wall.jpg", false, false);
	Texture texture2("../res/textures/awesomeface.png", true, true);
	
	shader.use();

	// Asign textures to the GPU to draw
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
   		glm::vec3( 2.0f,  5.0f, -15.0f), 
    		glm::vec3(-1.5f, -2.2f, -2.5f),  
    		glm::vec3(-3.8f, -2.0f, -12.3f),  
    		glm::vec3( 2.4f, -0.4f, -3.5f),  
    		glm::vec3(-1.7f,  3.0f, -7.5f),  
    		glm::vec3( 1.3f, -2.0f, -2.5f),  
    		glm::vec3( 1.5f,  2.0f, -2.5f), 
    		glm::vec3( 1.5f,  0.2f, -1.5f), 
    		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 projection = glm::mat4(1.0f); 
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	int projectionLoc = glGetUniformLocation(shader.getID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

	// Run till the window close
	while (!glfwWindowShouldClose(window))
	{
		// calculate Deltatime
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Register Input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Asign the texture order
		texture1.use(GL_TEXTURE0);
		texture2.use(GL_TEXTURE1);	

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		int viewLoc = glGetUniformLocation(shader.getID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	
		// Draw the element
		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.f * i;
			if (i % 3 == 0)
			{
				angle = glfwGetTime() * 25.0f;
			}

			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, &model[0][0]);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Get all events and register them on the window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free the ram and useless buffer and shader
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader.remove();

	glfwTerminate();
	return 0;
}

