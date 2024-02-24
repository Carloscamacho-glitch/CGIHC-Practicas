#include <stdio.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600; //pixeles de la ventana
float r, g, b = 0.0f;
int cont;

int main()
{
	//Inicialización de GLFW -- si no se configuro ben o faltan archivos
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	// Se le dice el api de dibujo a glfw
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//sirve para que glfw trabaje mas eficiente
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA (contenedor) NULL - modo ventana y que no sea pantalla completa y para que sea simultaneo en mas de 1 monitor
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1 Ejercicio 1", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer - asignacion de espacio de video
	int BufferWidth, BufferHeight;
	//se puede redimencionar la ventana en ejecucion
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto -- poner la ventana creada como la ventana activa
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones -- similar a glaw, pero con diferencias (no se pueden usar al mismo tiempo)
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport -- le dice donde acomotarce y se adapta a x,x pixeles de acuerdo al bufer de memoria
	//por lo que si se redimenciona no se ajustara a la ventana
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	//entra en cada ciclo de reloj mientras no se le mande un comando de cerrar
	while (!glfwWindowShouldClose(mainWindow))
	{//todo lo del while se realiza en cada ciclo de reloj
		
		//Recibir eventos del usuario (teclado, mouse, joystick)
		glfwPollEvents();

		//cambio de variables
		cont++;
		if (cont <= 100) {
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
		}else if (cont >= 100 && cont <= 200) {
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
		}else if (cont >= 200 && cont <= 300) {
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
		}
		if (cont == 300) {
			cont = 1;
		}

		//Limpiar la ventana (asignamos el color de la ventana (fondo)) -- el ultimo valor es a de alpha (canal)
		//solamnte en texturizado e iluminacion cambia el valor
		glClearColor(r,g,b,1.0f);
		//glfw maneja un buffer doble, porlo que se cambian los dos
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
		//No escribir nada despuyes porque no lo va a mostrar------------------------------------------------------------------------------

	}


	return 0;
}