#version 330 core
//La primera linea es la version

//Atributo de entrada
layout(location = 0) in vec3 posicion;

//Funcion main
void main() {
	//La posicion de salida del vertice se guarda en gl_Position (vec4)
	gl_Position.xyz = posicion;
	gl_Position.w = 1.0;
}