#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

const unsigned int width = 800;
const unsigned int height = 800;


int main() {


	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Vertices coordinates / color values    // texture coordinates
	GLfloat vertices[] = {
   -0.5f,  0.0f,  0.5f,      0.83f, 0.70f, 0.44f,   0.0f, 0.0f,
   -0.5f,  0.0f, -0.5f,      0.83f, 0.70f, 0.44f,   5.0f, 0.0f,
	0.5f,  0.0f, -0.5f,      0.83f, 0.70f, 0.44f,   0.0f, 0.0f, 
	0.5f,  0.0f,  0.5f,      0.83f, 0.70f, 0.44f,   5.0f, 0.0f,
	0.0f,  0.8f,  0.0f,      0.92f, 0.86f, 0.76f,   2.5f, 5.0f
	

	};

	GLuint indeces[]{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	//create window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLTutorial", NULL, NULL);

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
	glViewport(0, 0, width, height);




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
	Texture texture("C:\\Users\\Jacob\\Downloads\\RicknMorty.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);


	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	//enable depth testing
	glEnable(GL_DEPTH_TEST);

	//loop so the window stays open
	while (!glfwWindowShouldClose(window)) {
		glad_glClearColor(0.07f, 0.013f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Tell opengl which shader program to use
		shaderProgram.Activate();

		//simple timer
		double crntTime = glfwGetTime();
		if(crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		//initializes matrices to identity 
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		//assignes different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), float(width / height), 0.1f, 100.0f);

		//inputs matriecs into the shader program
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		//update the value of our uniform (scale) from our shader 
		glUniform1f(uniID, 0.5f);
		texture.Bind();
		//Bind the VAO so opengl knows to use it
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indeces)/sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		//proccess window events
		glfwPollEvents();

		
	}

	//delete all the object we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	texture.Delete();
	

	//destroy window when done
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}