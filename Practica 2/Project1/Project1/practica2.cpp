//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>//matematicas
#include<vector>//estructuras de datos
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>//libreria matematica para graficos por computadora vec3 = 3x1 mat3 = 4x4
//uniform sirve para que shader reciva el dato que no recibe por 
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>//punteros
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
//clamp interpola el color
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes (para las rotaciones)
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
//se declaran los dos pares de shaders
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//Se agregan los archivos de los shaders
static const char* vShaderROJO = "shaders/shaderROJO.vert";
static const char* fShaderROJO = "shaders/shaderROJO.frag";
static const char* vShaderVERDE = "shaders/shaderVERDE.vert";
static const char* fShaderVERDE = "shaders/shaderVERDE.frag";
static const char* vShaderAZUL = "shaders/shaderAZUL.vert";
static const char* fShaderAZUL = "shaders/shaderAZUL.frag";
static const char* vShaderCAFE = "shaders/shaderCAFE.vert";
static const char* fShaderCAFE = "shaders/shaderCAFE.frag";
static const char* vShaderVERDEOSCURO = "shaders/shaderVERDEOSCURO.vert";
static const char* fShaderVERDEOSCURO = "shaders/shaderVERDEOSCURO.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067 //(para el reporte)

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	//agrega a la lista los mesh
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

//cubo y piramide con color interpolado
//figuras con colores
//se agregan las letras del reporte anterior
void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		//J-------------------------------------------------------------
		-0.68f,0.85f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.17f,0.85f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.17f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.68f,0.85f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.17f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.68f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.34f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.34f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.51f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.34f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.51f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.51f,0.68f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.34f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.34f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.68f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.68f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.34f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.68f,0.34f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.68f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.85f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.85f,0.51f,0.0f,					1.0f,	0.0f,	1.0f,

		-0.68f,0.17f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.68f,0.51f,0.0f,					1.0f,	0.0f,	1.0f,
		-0.85f,0.51f,0.0f,					1.0f,	0.0f,	1.0f,

		//C-------------------------------------------------------------
		0.17f,0.85f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.85f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.68f, 0.0f,					1.0f,	1.0f,	0.0f,

		0.17f,0.85f,0.0f,					1.0f,	1.0f,	0.0f,
		0.17f,0.68f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.68f, 0.0f,					1.0f,	1.0f,	0.0f,

		0.17f,0.34f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.34f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.17f, 0.0f,					1.0f,	1.0f,	0.0f,

		0.17f,0.34f,0.0f,					1.0f,	1.0f,	0.0f,
		0.17f,0.17f,0.0f,					1.0f,	1.0f,	0.0f,
		0.68f,0.17f, 0.0f,					1.0f,	1.0f,	0.0f,

		0.17f,0.68f,0.0f,					1.0f,	1.0f,	0.0f,
		0.34f,0.68f,0.0f,					1.0f,	1.0f,	0.0f,
		0.17f,0.34f, 0.0f,					1.0f,	1.0f,	0.0f,

		0.34f,0.34f,0.0f,					1.0f,	1.0f,	0.0f,
		0.34f,0.68f,0.0f,					1.0f,	1.0f,	0.0f,
		0.17f,0.34f, 0.0f,					1.0f,	1.0f,	0.0f,

		//M-------------------------------------------------------------
		-0.34f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		-0.34f,-0.85f,0.0f,					0.5f,	0.25f,	0.75f,
		-0.17f,-0.85f, 0.0f,				0.5f,	0.25f,	0.75f,

		-0.34f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		-0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		-0.17f,-0.85f, 0.0f,				0.5f,	0.25f,	0.75f,

		0.34f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.34f,-0.85f,0.0f,					0.5f,	0.25f,	0.75f,
		0.17f,-0.85f, 0.0f,					0.5f,	0.25f,	0.75f,

		0.34f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.17f,-0.85f, 0.0f,					0.5f,	0.25f,	0.75f,

		-0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.40f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.68f, 0.0f,					0.5f,	0.25f,	0.75f,

		-0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		-0.28f,-0.34f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.68f, 0.0f,					0.5f,	0.25f,	0.75f,

		0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.40f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.68f, 0.0f,					0.5f,	0.25f,	0.75f,

		0.17f,-0.17f,0.0f,					0.5f,	0.25f,	0.75f,
		0.28f,-0.34f,0.0f,					0.5f,	0.25f,	0.75f,
		0.0f,-0.68f, 0.0f,					0.5f,	0.25f,	0.75f,


	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 396);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);//indice 0 cubo y piramide (clamp)

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);//indice 1 figuras y letras

	//se crean los shaders nuevos
	//color rojo
	Shader* shader3 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader3->CreateFromFiles(vShaderROJO, fShaderColor);
	shaderList.push_back(*shader3);//indice 0 cubo y piramide (clamp)
	//color verde
	Shader* shader4 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader4->CreateFromFiles(vShaderVERDE, fShaderVERDE);
	shaderList.push_back(*shader4);//indice 0 cubo y piramide (clamp)
	//color azul
	Shader* shader5 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader5->CreateFromFiles(vShaderAZUL, fShaderAZUL);
	shaderList.push_back(*shader5);//indice 0 cubo y piramide (clamp)
	//color cafe
	Shader* shader6 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader6->CreateFromFiles(vShaderCAFE, fShaderCAFE);
	shaderList.push_back(*shader6);//indice 0 cubo y piramide (clamp)
	//color verde oscuro
	Shader* shader7 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader7->CreateFromFiles(vShaderVERDEOSCURO, fShaderVERDEOSCURO);
	shaderList.push_back(*shader7);//indice 0 cubo y piramide (clamp)
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//para el cubo y piramide importa el orde para la asignacion del shader
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//-----------------------------------------se declaran siempre fuera del while----------------------------------------------
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//																rango de visualizacion 
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//										angulo de vista			aspect radio ancho entre alto (nuca se mueve)			cerca y lejos
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	//-----------------------------------------se declaran siempre fuera del while----------------------------------------------

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//puede tener mas parametros
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		/*
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//sirven para que el shader reciva los datos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//indices, draw element, recibe 2 variables
		meshColorList[0]->RenderMeshColor();
		*/

		
		//piramides
		//piramide azul (techo)
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, -3.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 1.2f, 1.0f));
		//casi siempre se traslada - se rota - se escala
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//para dibujar otro cubo se debe trasladar
		//la matris identidad hace que el cubo sea independiente del otro
		
		//piramides verdes oscuras ------------------------------------------
		//Se pone el shader verde oscuro para las 2 piramides
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		//piramides verdes oscuras 1 (arbolito)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.67f, -0.52f, -2.85f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//piramides verdes oscuras 2 (arbolito)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.67f, -0.52f, -2.85f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[0]->RenderMesh();
		//piramides verdes oscuras ------------------------------------------

		//cubos
		//cubo rojo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.53f, -3.0f));
		model = glm::scale(model, glm::vec3(2.27f, 2.2f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//cubos verdes ------------------------------------------
		//Se pone el shader verde para los 3 cubos
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		//cubo verde 1 (ventana)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -2.75f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//cubo verde 2 (ventana)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, -2.75f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMesh();

		//cubo verde 3 (puerta)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.08f, -2.75f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMesh();
		//cubos verdes ------------------------------------------

		//cubos cafes ------------------------------------------
		//Se pone el shader cafe para los 3 cubos
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		
		//cubo cafe 1 (tonco)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.7f, -1.32f, -3.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//cubo cafe 2 (tonco)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.7f, -1.32f, -3.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMesh();
		//cubos cafes ------------------------------------------
		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
// Escala cuando es 0 a 1 se hace pequeño y mayor a 1 se hace grande
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/