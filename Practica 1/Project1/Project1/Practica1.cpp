#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <time.h> //tiempo
#include <cstdlib> //numero aleatorio
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
float r, g, b = 0.0f;

//variable para guardar y manejar el tiempo
time_t contador;
double resta, tiempoguardado;

//primera para crear un VAO, un VBO y un shader
//VAO datos de los vertices
//VBO lmacena en memoria
//shader recive los datos del VBO
GLuint VAO, VBO, shader;

//Vertex Shader (obligatorio que exista)
//recibir color, salida Vcolor
//solo para la practica 01 estaran los datos del vertex y fragment shader para posteriores en archivos externos
//pimer linea vercion de shader, GLSL porque es multiplataforma
//segunda linea variable de entrada siempre vec3
//gl position al dato lo convierte en coordenadas x,y,z
//el ultimo valor siempre es 1
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color (no es obligatorio pero se usa el 99% de las veces)
//mas basico (1 variable de entrada y de salida)
//recibe r,g,b,a (cambia entre 0 y 1)
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.0f,0.0f,1.0f);	 			\n\
}";

void CrearTriangulo()
{
	GLfloat vertices[] = {
		//9 valores flotantes para convertir en vertices
		//J-------------------------------------------------------------
		-0.68f,0.85f,0.0f,
		-0.17f,0.85f,0.0f,
		-0.17f,0.68f,0.0f,

		-0.68f,0.85f,0.0f,
		-0.17f,0.68f,0.0f,
		-0.68f,0.68f,0.0f,

		-0.34f,0.68f,0.0f,
		-0.34f,0.34f,0.0f,
		-0.51f,0.34f,0.0f,

		-0.34f,0.68f,0.0f,
		-0.51f,0.34f,0.0f,
		-0.51f,0.68f,0.0f,

		-0.34f,0.34f,0.0f,
		-0.34f,0.17f,0.0f,
		-0.68f,0.34f,0.0f,

		-0.68f,0.17f,0.0f,
		-0.34f,0.17f,0.0f,
		-0.68f,0.34f,0.0f,

		-0.68f,0.17f,0.0f,
		-0.85f,0.17f,0.0f,
		-0.85f,0.51f,0.0f,

		-0.68f,0.17f,0.0f,
		-0.68f,0.51f,0.0f,
		-0.85f,0.51f,0.0f,

		//C-------------------------------------------------------------
		0.17f,0.85f,0.0f,
		0.68f,0.85f,0.0f,
		0.68f,0.68f, 0.0f,

		0.17f,0.85f,0.0f,
		0.17f,0.68f,0.0f,
		0.68f,0.68f, 0.0f,

		0.17f,0.34f,0.0f,
		0.68f,0.34f,0.0f,
		0.68f,0.17f, 0.0f,

		0.17f,0.34f,0.0f,
		0.17f,0.17f,0.0f,
		0.68f,0.17f, 0.0f,

		0.17f,0.68f,0.0f,
		0.34f,0.68f,0.0f,
		0.17f,0.34f, 0.0f,

		0.34f,0.34f,0.0f,
		0.34f,0.68f,0.0f,
		0.17f,0.34f, 0.0f,

		//M-------------------------------------------------------------
		-0.34f,-0.17f,0.0f,
		-0.34f,-0.85f,0.0f,
		-0.17f,-0.85f, 0.0f,

		-0.34f,-0.17f,0.0f,
		-0.17f,-0.17f,0.0f,
		-0.17f,-0.85f, 0.0f,

		0.34f,-0.17f,0.0f,
		0.34f,-0.85f,0.0f,
		0.17f,-0.85f, 0.0f,

		0.34f,-0.17f,0.0f,
		0.17f,-0.17f,0.0f,
		0.17f,-0.85f, 0.0f,

		-0.17f,-0.17f,0.0f,
		0.0f,-0.40f,0.0f,
		0.0f,-0.68f, 0.0f,

		-0.17f,-0.17f,0.0f,
		-0.28f,-0.34f,0.0f,
		0.0f,-0.68f, 0.0f,

		0.17f,-0.17f,0.0f,
		0.0f,-0.40f,0.0f,
		0.0f,-0.68f, 0.0f,

		0.17f,-0.17f,0.0f,
		0.28f,-0.34f,0.0f,
		0.0f,-0.68f, 0.0f,

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//se convierten los 9 flotantes en 9 vertices (GL_STATIC_DRAW cambia cuando se usa pixel shader y geometry shader)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		//se ajusta como se ajustaran los certices para mandarlos al 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
														//datos por renglon	//si tengo mas datos se le dice que omita X cantidad por renglon
		//se mandan los 3 datos al shder en la variable de tipo in
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		//se liga al buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//las 4 lineas vienen en conjunto y el numero del indicador
}

//se siguen los pasos para poder utilizar el shader en el gpu
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) 

{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

//se siguen los pasos para poder utilizar el shader en el gpu (posteriormente se iran agregando datos) y estaran en la chase shader (shader .h y .cpp)
void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa (vacio)
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	//se valida el codigo
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}

int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1 Hola Mundo", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();

	//semilla para generar los numeros
	srand(time(NULL));

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//recibe el tiempo actual y resta el del contador con el tiempo anterior guardado
		contador = time(NULL);
		resta = contador - tiempoguardado;

		//cambio de variables
		if (resta >= 2) {
			//genera numeros aleatorios entre el 0 y el 1 para cada componente del RGB
			r = (float)rand() / RAND_MAX;
			g = (float)rand() / RAND_MAX;
			b = (float)rand() / RAND_MAX;
			//resetea el tiempo guardado al tiempo actual
			tiempoguardado = contador;
		}

		//Limpiar la ventana
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//se le pasa el shader compilado al programa
		glUseProgram(shader);

		//se le pasan los datos
		glBindVertexArray(VAO);
		//se indica que se dibujaran triangulos
		glDrawArrays(GL_TRIANGLES,0,66);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}