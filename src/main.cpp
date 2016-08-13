#include "main.h"
#include <cmath>

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	int radious = 250;
	int rada = 40;
	int frac = 50;
	Color cyan(0, 1.0f, 1.0f, 1.0f);
	Color red(1.0f, 0, 0, 1.0f);
	Color green(0.0f, 1, 0, 1);
	Color purple(1,0,1,1);
	Color blue(0,0,1,1);

	Color white(1,1,1,1);
	for(int i = 0; i < frac; i++){
		//DrawLine(Point(256, 256), Point(256+radious*cos(2*M_PI*i/frac), 256+radious*sin(2*M_PI*i/frac)), cyan, red);
		//DrawLine(Point(256+rada*cos(2*M_PI*i/frac), 256+rada*sin(2*M_PI*i/frac)), Point(256+radious*cos(2*M_PI*i/frac), 256+radious*sin(2*M_PI*i/frac)), purple, green);
	}

	//PutPixel(Point(511, 511), Color(1,1,1,1));
	//PutPixel(Point(570, 500), Color(1,1,1,1));

	/*
	PutPixel(381, 106, 0.0f, 1.0f, 1.0f, 1.0f);
	PutPixel(317, 148, 1.0f, 0.0f, 1.0f, 1.0f);
	PutPixel(456, 315, 1.0f, 1.0f, 0.0f, 1.0f);
	PutPixel(56 , 209, 0.5f, 0.5f, 0.5f, 1.0f);
	PutPixel(218, 97 , 1.0f, 1.0f, 1.0f, 1.0f);
	*/

	//DrawFillTriangle(Point(500, 174), Point(300, 100), Point(139, 490), white, white, white);
	//DrawFillTriangle(Point(256, 10), Point(15, 240), Point(390, 480), white, white, white);
	//DrawFillTriangle(Point(0, 40), Point(40, 0), Point(500, 300), white, white, white);

	//DrawFillTriangle(Point(500, 174), Point(300, 100), Point(139, 490), red, green, blue);
	//DrawFillTriangle(Point(256, 10), Point(15, 240), Point(390, 480), red, green, blue);
	//DrawFillTriangle(Point(0, 40), Point(40, 0), Point(500, 300), red, green, blue);

	//DrawFillTriangle(Point(550, 174), Point(400, 100), Point(139, 490), Color(0.4f,0,0.7f,1.0f), Color(0,1.0f,0.5f,1.0f), Color(0.9f,0.34f,0.0f,1.0f));
	//Pixel pixel(20, 200, 255, 0, 0, 255);
	//PutPixel(10, 500);
	//DrawLine(0, 0, 10, 500);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

