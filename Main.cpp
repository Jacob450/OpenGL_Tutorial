#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




int main() {
	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Vertices coordinates              / color values
	GLfloat vertices[] = {
   -0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f, 0.8f, 0.3f, 0.02f,// Lower Left Corner
	0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f, 0.8f, 0.3f, 0.02f, // Lower Right Corner
	0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.3f, // upper Corner
   -0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f, 0.9f, 0.45f, 0.17f,// inner left
	0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f, 0.9f, 0.45f, 0.17f, // inner right
	0.0f, -0.5f * float(sqrt(3)) / 3,      0.0f, 0.8f, 0.3f, 0.02f // inner right

	};

	GLuint indeces[]{
		0, 3, 5, // Lower Left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1  // upper right triangle
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



	//loop so the window stays open
	while (!glfwWindowShouldClose(window)) {
		glad_glClearColor(0.07f, 0.013f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell opengl which shader program to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		//Bind the VAO so opengl knows to use it
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		//proccess window events
		glfwPollEvents();
	}

	//delete all the object we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	

	//destroy window when done
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}