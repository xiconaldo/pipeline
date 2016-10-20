#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <cstdlib>

//*****************************************************************************
// Declaração de tipos, funções e classes auxiliares
//*****************************************************************************
class Point;
class Color;
class Pixel;
class Line;
typedef unsigned char byte;
//void swap(int&, int&);
//void sort3(int*);
//void Barycentric(const Point&, const Point&, const Point&, const Point&, float&, float&, float&);


//*****************************************************************************
// Definição das classes auxiliares
//*****************************************************************************

// Representa um ponto com coordenadas x e y e as operações
// que podem ser realizadas com seus componentes
class Point{
public:
	Point(){}
	Point(int x, int y):
		x(x), y(y)
	{}

	Point operator-(const Point& op) const{
		return Point(x-op.x, y-op.y);
	}

	float operator*(const Point& op) const{
		return x*op.y + y*op.x;
	}

	int x;
	int y;
};

// Representa uma cor no sistema RGBA e operações comoponente a
// componente relaizadas com elas.
class Color{
public:
	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f):
		r(r), g(g), b(b), a(a)
	{}

	Color operator+(const Color& op) const{
		return Color(r+op.r, g+op.g, b+op.b, a+op.a);
	}

	Color operator-(const Color& op) const{
		return Color(r-op.r, g-op.g, b-op.b, a-op.a);
	}

	Color operator-() const{
		return Color(-r, -g, -b, -a);
	}

	Color operator*(float mul) const{
		return Color(r*mul, g*mul, b*mul, a*mul);
	}

	Color operator/(float div) const{
		return Color(r/div, g/div, b/div, a/div);
	}

	Color operator+=(const Color& op){
		r += op.r;
		g += op.g;
		b += op.b;
		a += op.a;
		return *this;
	}

	Color operator=(const Color& op){
		r = op.r;
		g = op.g;
		b = op.b;
		a = op.a;
		return *this;
	}

	float r;
	float g;
	float b;
	float a;
};

// Representa um pixel, que contém uma posição e uma cor
class Pixel{
public:
	Pixel(int x, int y, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) :
		pos(x,y), color(r, g, b, a)
	{

	}

	Point pos;
	Color color;
};

// Representa uma Lineação de reta, através de seus coeficinetes.
// Para construir a reta, são necessários 2 pontos.
class Line{
public:
	Line(Point p1, Point p2){
		a = float(p2.y-p1.y)/(p2.x-p1.x);
		b = p1.y - a*p1.x;
	}

	// Avalia se um ponto está sobre a reta ou de que lado da reta
	// ele encontra-se. Retorna 0 no primeiro caso e números de sinais
	// opostos para cada um dos lados.
	float value(Point p){
		return a*p.x + b - p.y;
	}

	float a;
	float b;
};

//*****************************************************************************
// Funções gráficas
//*****************************************************************************
void PutPixel(const Pixel& p);

void PutPixel(const Point& p, const Color& c);

void PutPixel(int x, int y, float r, float g, float b, float a);

void DrawLine(const Point& pa, const Point& pb, const Color& start, const Color& end);

void DrawTriangle(const Point& pa, const Point& pb, const Point& pc, const Color& ca = Color(), const Color& cb = Color(), const Color& cc = Color());

void DrawFillTriangle(const Point& pa, const Point& pb, const Point& pc, const Color& ca = Color(), const Color& cb = Color(), const Color& cc = Color());


//*****************************************************************************
// Funções auxiliares
//*****************************************************************************
void swap(int& a, int& b);

void sort3(int *list);

// Calcula as coordenadas baricêntricas de um ponto p em
// relação a outros 3 pontos pa, pb, pc dados.
void Barycentric(const Point& p, const Point& pa, const Point& pb, const Point &pc, float &u, float &v, float &w);

#endif // _MYGL_H_

