#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Declaração de tipos, funções e classes auxiliares
//*****************************************************************************
class Point;
class Color;
class Pixel;
class Line;
typedef unsigned char byte;
void swap(int&, int&);
void sort3(int*);
void Barycentric(const Point&, const Point&, const Point&, const Point&, float&, float&, float&);


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
void PutPixel(const Pixel& p){
	if(p.pos.x < 0 || p.pos.x >= IMAGE_WIDTH || p.pos.y < 0 || p.pos.y >= IMAGE_HEIGHT) return;

	int pos = p.pos.x*4 + p.pos.y*IMAGE_WIDTH*4;
	FBptr[pos + 0] = p.color.r * 255;
	FBptr[pos + 1] = p.color.g * 255;
	FBptr[pos + 2] = p.color.b * 255;
	FBptr[pos + 3] = p.color.a * 255;
}

void PutPixel(const Point& p, const Color& c){
	if(p.x < 0 || p.x >= IMAGE_WIDTH || p.y < 0 || p.y >= IMAGE_HEIGHT) return;

	int pos = p.x*4 + p.y*IMAGE_WIDTH*4;
	FBptr[pos + 0] = c.r * 255;
	FBptr[pos + 1] = c.g * 255;
	FBptr[pos + 2] = c.b * 255;
	FBptr[pos + 3] = c.a * 255;
}

void PutPixel(int x, int y, float r, float g, float b, float a){
	if(x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT) return;

	int pos = x*4 + y*IMAGE_WIDTH*4;
	FBptr[pos + 0] = r * 255;
	FBptr[pos + 1] = g * 255;
	FBptr[pos + 2] = b * 255;
	FBptr[pos + 3] = a * 255;
}

void DrawLine(const Point& pa, const Point& pb, const Color& start, const Color& end){
	int x0 = pa.x;
	int x1 = pb.x;
	int y0 = pa.y;
	int y1 = pb.y;

	int dx = x1 - x0;
	int dy = y1 - y0;
	Color grad = start;
	Color inc;

	int *drx, *dry;
	int d;
	int incr_e;
	int incr_ne;

	if(abs(dx) < abs(dy)){
		swap(dx, dy);
		swap(x0, y0);
		swap(x1, y1);

		drx = &y0;
		dry = &x0;
	}
	else{
		drx = &x0;
		dry = &y0;
	}

	if(dx < 0){
		x0 *= -1;
		x1 *= -1;
		dx *= -1;
	}
	if(dy < 0){
		y0 *= -1;
		y1 *= -1;
		dy *= -1;
	}

	inc = (end-start)/dx;
	d = 2*dy - dx;
	incr_e = 2*dy;
	incr_ne = 2*(dy - dx);

	PutPixel(abs(*drx), abs(*dry), grad.r, grad.g, grad.b, grad.a);
	while(x0 < x1){
		if(d <= 0){
			d += incr_e;
			x0++;
		}
		else{
			d += incr_ne;
			x0++;
			y0++;
		}
		grad += inc;
		
		PutPixel(abs(*drx), abs(*dry), grad.r, grad.g, grad.b, grad.a);
	}
}

void DrawTriangle(const Point& pa, const Point& pb, const Point& pc, const Color& ca, const Color& cb, const Color& cc){
	DrawLine(pa, pb, ca, cb);
	DrawLine(pb, pc, cb, cc);
	DrawLine(pc, pa, cc, ca);
}

void DrawFillTriangle(const Point& pa, const Point& pb, const Point& pc, const Color& ca, const Color& cb, const Color& cc){
	Line e1(pa, pb);
	Line e2(pb, pc);
	Line e3(pc, pa);
	int in1, in2, in3;

	in1 = e1.value(pc)>0 ? 1 : -1;
	in2 = e2.value(pa)>0 ? 1 : -1;
	in3 = e3.value(pb)>0 ? 1 : -1;

	int listx[3] = {pa.x, pb.x, pc.x};
	int listy[3] = {pa.y, pb.y, pc.y};
	sort3(listx);
	sort3(listy);
	
	float alpha, beta, gama;
	Point aux;
	Color paint;

	for(int vy = listy[0]; vy <= listy[2]; vy++){
		for(int vx = listx[0]; vx <= listx[2]; vx++){
			aux.x = vx;
			aux.y = vy;

			if(in1<0 ? e1.value(aux) >= 0 : e1.value(aux) <= 0) continue;
			if(in2<0 ? e2.value(aux) >= 0 : e2.value(aux) <= 0) continue;
			if(in3<0 ? e3.value(aux) >= 0 : e3.value(aux) <= 0) continue;

			Barycentric(aux, pa, pb, pc, alpha, beta, gama);
			paint = ca*alpha + cb*beta + cc*gama;
			PutPixel(aux, paint);
		}
	}
}


//*****************************************************************************
// Funções auxiliares
//*****************************************************************************
void swap(int& a, int& b){

	int aux;
	aux = a;
	a = b;
	b = aux;
}

void sort3(int *list){

	if(list[0] > list[1]){
		swap(list[0], list[1]);
	}
	if(list[1] > list[2]){
		swap(list[1], list[2]);
	}
	if(list[0] > list[1]){
		swap(list[0], list[1]);
	}
}

// Calcula as coordenadas baricêntricas de um ponto p em
// relação a outros 3 pontos pa, pb, pc dados.
void Barycentric(const Point& p, const Point& pa, const Point& pb, const Point &pc, float &u, float &v, float &w){

	Point v0 = pb - pa;
	Point v1 = pc - pa;
	Point v2 = p  - pa;

	float d00 = v0*v0;
	float d01 = v0*v1;
	float d11 = v1*v1;
	float d20 = v2*v0;
	float d21 = v2*v1;

	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}

#endif // _MYGL_H_

