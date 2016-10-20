#include "main.h"
//#include "objLoader.h"

#include "scene.h"

/*objLoader object;
std::vector<glm::vec4> vertices;
std::vector<glm::vec4> transf_vertices;*/

Scene *scene;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	clearScreen();

	static float angle = 0;
	angle += 0.1f;
	
	scene->addRotation(angle, 0, 1, 0);
	scene->addRotation(30, 1, 0, 0);
	scene->addTransl(0, 0, 1.0f);

	scene->setView(0.0f, 0.0f, 2.15f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);
	scene->setProj(2.0f);
	scene->setScreen(IMAGE_WIDTH, IMAGE_HEIGHT);

	scene->draw();
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	scene = new Scene;
	//scene->load("../data/monkey_head2.obj");
	//scene->load("../data/ico.obj");
	//scene->load("../data/cilynder.obj");
	//scene->load("../data/cube.obj");
	scene->load("../data/torus.obj");
	

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

