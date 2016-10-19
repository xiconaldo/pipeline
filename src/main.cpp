#include "main.h"
#include "objLoader.h"
#include "../include/glm/gtx/transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <cmath>
#include <vector>

objLoader object;
std::vector<glm::vec4> vertices;
std::vector<glm::vec4> transf_vertices;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	clearScreen();

	//////////////////
	// MODEL MATRIX //
	//////////////////
	
	glm::vec3 trans_param;
	glm::vec3 rot_param;
	static float angle = 0;
	float sin_angle, cos_angle;
	glm::vec3 scale_factors(1.0f);
	
	glm::mat4 m_model;
	glm::mat4 rot_mat;
	glm::mat4 trans_mat;
	glm::mat4 scale_mat;
	
	trans_mat[3] = glm::vec4(trans_param, 1.0f);
	
	sin_angle = sin(angle * M_PI / 180);
	cos_angle = cos(angle * M_PI / 180);

	rot_param.y = 1.0f;
	angle += 0.1f;

	if(rot_param.x == 1.0f){
		rot_mat[1].y = cos_angle;
		rot_mat[1].z = sin_angle;
		rot_mat[2].y = -sin_angle;
		rot_mat[2].z = cos_angle;
	}
	else if(rot_param.y == 1.0f){
		rot_mat[0].x = cos_angle;
		rot_mat[0].z = -sin_angle;
		rot_mat[2].x = sin_angle;
		rot_mat[2].z = cos_angle;
	}
	else if(rot_param.z == 1.0f){
		rot_mat[0].x = cos_angle;
		rot_mat[0].y = sin_angle;
		rot_mat[1].x = -sin_angle;
		rot_mat[1].y = cos_angle;
	}

	scale_mat[0].x = scale_factors.x;
	scale_mat[1].y = scale_factors.y;
	scale_mat[2].z = scale_factors.z;

	m_model = trans_mat * rot_mat * scale_mat;


	/////////////////
	// VIEW MATRIX //
	/////////////////
	
	glm::mat4 m_view;
	glm::mat4 T;
	glm::mat4 B;

	glm::vec3 pos(0.0f, 0.0f, 2.15f);
	//glm::vec3 pos(0.0f, 0.0f, 4.0f);
	glm::vec3 lookAt(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	glm::vec3 xc;
	glm::vec3 yc;
	glm::vec3 zc;

	zc = glm::normalize(pos - lookAt);
	xc = glm::normalize(glm::cross(up, zc));
	yc = glm::normalize(glm::cross(zc, xc));

	B[0] = glm::vec4(xc, 0.0f);
	B[1] = glm::vec4(yc, 0.0f);
	B[2] = glm::vec4(zc, 0.0f);
	B[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	T[3] = glm::vec4(-pos, 1.0f);

	m_view = glm::transpose(B) * T;

	///////////////////////
	// PROJECTION MATRIX //
	///////////////////////
	
	glm::mat4 m_proj;
	float d = 2.0f;

	m_proj[2].w = -1/d;
	m_proj[3].z = d;


	glm::mat4 m_model_view_proj = m_proj * m_view * m_model;


	////////////////////
	// HOMOGENIZATION //
	////////////////////

	for(int i = 0; i < vertices.size(); i++){
		transf_vertices[i] = m_model_view_proj * vertices[i];
		transf_vertices[i] /= transf_vertices[i].w;
	}


	///////////////////
	// SCREEN MATRIX //
	///////////////////
	
	glm::mat4 m_screen;
	glm::mat4 inv_y;
	glm::mat4 screen_trans;
	glm::mat4 screen_scale;

	inv_y[1].y = -1;
	screen_trans[3] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	screen_scale[0].x = (IMAGE_WIDTH-1) * 0.5f;
	screen_scale[1].y = (IMAGE_HEIGHT-1) * 0.5f;

	m_screen = screen_scale * screen_trans * inv_y;


	///////////////////////
	// APPLYING MATRICES //
	///////////////////////

	for(int i = 0; i < transf_vertices.size(); i++){
		transf_vertices[i] = glm::round(m_screen * transf_vertices[i]);
	}


	/////////////
	// DRAWING //
	/////////////
	
	//object.faceList->vertex_index
	Point a, b, c;
	int *vertex;

	for(int i = 0; i < object.faceCount; i++){

		vertex = object.faceList[i]->vertex_index;

		a = Point(transf_vertices[vertex[0]].x, transf_vertices[vertex[0]].y);
		b = Point(transf_vertices[vertex[1]].x, transf_vertices[vertex[1]].y);
		c = Point(transf_vertices[vertex[2]].x, transf_vertices[vertex[2]].y);

		DrawTriangle(a, b, c);
	}

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();


	// Carregando objeto a ser desenhado
	object.load("../data/monkey_head2.obj");
	for(int i = 0; i < object.vertexCount; i++){
		vertices.push_back(glm::vec4(object.vertexList[i]->e[0], object.vertexList[i]->e[1], object.vertexList[i]->e[2], 1.0f));
	}
	transf_vertices.resize(vertices.size());
	

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

