// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <math.h>

#include <iostream>

#include "Vertice.h"
#include "Shader.h"

using namespace std;

GLfloat red = 0.0f, green = 0.0f, blue = 0.0f;

vector<Vertice> triangulo;
GLuint posicionID;
GLuint vertexArrayID;
GLuint bufferID;

Shader *shader;

//Aqui esta bien para cambiar los valores de las variables de mi programa
void actualizar() {

}

void dibujar() {
	//Enlazar el shader
	shader->enlazarShader();
	//Especificar el vertex array
	glBindVertexArray(vertexArrayID);
	//Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());
	//Soltar el vertex array
	glBindVertexArray(0);
	//Soltar el shader
	shader->desenlazarShader();
}

int main()
{
	//Declaracion de la ventana
	GLFWwindow *window;

	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 720;

	//Inicializacion de GLFW
	if (!glfwInit()) {
		//Si no se inicio bien, terminar la ejecucion
		exit(EXIT_FAILURE);
	}

	//Iniciar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verificar si se creo bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecucion
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como conexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;

	//Inicializar triangulo
	Vertice v1 = { vec3(-1.0f, -0.5f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v2 = { vec3(0.0f, 0.5f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v3 = { vec3(1.0f, -0.5f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");

	//Desenlazar el shader
	shader->desenlazarShader();

	//Crear un vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Crear un vertex buffer
	glGenBuffers(1, &bufferID);
	//De aqui en adelante se trabaja con este buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Llenar el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice)*triangulo.size(), triangulo.data(), GL_STATIC_DRAW);

	//Habilitar el atributo
	glEnableVertexAttribArray(posicionID);

	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);

	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {		
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

