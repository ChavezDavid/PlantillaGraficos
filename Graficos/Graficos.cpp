// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
using namespace std;

GLfloat red = 0.0f, green = 0.0f, blue = 0.0f;

//Aqui esta bien para cambiar los valores de las variables de mi programa
void actualizar() {
	/*if(red !=1) red += 0.001;
	if(green !=1 && red >= 1) green += 0.001;
	if(blue !=1 && red >= 1 && green >= 1) blue += 0.001;
	*/
}

void dibujar() {
	glBegin(GL_TRIANGLES);//Inicia la rutina con un modo de dibujo

	//Primer triangulo
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	//Segundo triangulo
	glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glEnd();//Finaliza la rutina
}

int main()
{
	//Declaracion de la ventana
	GLFWwindow *window;

	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

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

