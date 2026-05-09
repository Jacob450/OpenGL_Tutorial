#include"EBO.h"


EBO::EBO(GLuint* indeces, GLsizeiptr size) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//Indroduce the vertices into the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}

