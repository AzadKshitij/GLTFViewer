#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/ElementBuffer.h>


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   Texture Cord.
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


const int width = 800;
const int height = 800;

int main()
{
	std::cout << "Working" << std::endl;
	
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800

	glViewport(0, 0, width, height);
	
	Shader shaderProgram("./resource/Shaders/default.vert", "./resource/Shaders/default.frag");
	

	// Vertex Buffer Object // Vertex Array Object
	VertexArray VAO;
	VAO.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));

	ElementBuffer EBO(indices, sizeof(indices));

	//VAO.LinkVertexBufferObject(VBO, 0);
	VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();


	GLuint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Textures

	int imgWidth, imgHeight, colorChnl;
	unsigned char* imageData = stbi_load("./resource/Images/tex1.jpg", &imgWidth, &imgHeight, &colorChnl, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0ID = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0ID, 0);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();

		glUniform1f(scaleID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		VAO.Bind();
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	
	glDeleteTextures(1, &texture);

	shaderProgram.Delete();

	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderprogram);*/


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

