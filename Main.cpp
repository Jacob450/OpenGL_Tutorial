#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>



#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------



int main() {


	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Vertices coordinates / color values    // texture coordinates
	GLfloat vertices[] = {
   -0.5f, -0.5f, 0.00f,      1.0f, 0.0f, 0.0f,   0.0f, 0.0f,// Lower Left Corner
   -0.5f,  0.5f, 0.00f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Lower Right Corner
	0.5f,  0.5f, 0.00f,      0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // upper Corner
	0.5f, -0.5f, 0.00f,      1.0f, 1.0f, 1.0f,   1.0f, 0.0f// inner left
	

	};

	GLuint indeces[]{
		0, 2, 1, // first triangle
		0, 3, 2 // second triangle
	};

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLTutorial", NULL, NULL);

	//check if window is null
	if (window == NULL) {
		std::cout << "Failed to create window";
		glfwTerminate();
		return -1;
	}
	//set the current window
	glfwMakeContextCurrent(window);

	//load glad and specify viewport of opengl in the window 
	gladLoadGL();
	glViewport(0, 0, 800, 800);




	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indeces, sizeof(indeces));
	//links VBO to Vao so that opengl knows how to read the VBO and use it in the shader
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	// assigns a value to the uniform (scale) from the vertex shader 
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");




	//texture  
	Texture context("C:\\Users\\Jacob\\Downloads\\context.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	context.texUnit(shaderProgram, "tex0", 0);




	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	//loop so the window stays open
	while (!glfwWindowShouldClose(window)) {
		glad_glClearColor(0.07f, 0.013f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell opengl which shader program to use
		shaderProgram.Activate();
		//update the value of our uniform (scale) from our shader 
		glUniform1f(uniID, 0.5f);
		context.Bind();
		//Bind the VAO so opengl knows to use it
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		//proccess window events
		glfwPollEvents();

		
	}

	//delete all the object we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	context.Delete();
	

	//destroy window when done
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}