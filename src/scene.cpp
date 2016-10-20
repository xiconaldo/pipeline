#include "scene.h"
#include <iostream>

Scene::Scene(){
	object = new objLoader;
}

// Carrega vértices da cena (do objeto)
void Scene::load(char file[]){

	object->load(file);
	for(int i = 0; i < object->vertexCount; i++){
		vertices.push_back(glm::vec4(object->vertexList[i]->e[0], object->vertexList[i]->e[1], object->vertexList[i]->e[2], 1.0f));
	}
}

// Desenha a cena inteira, fazendo os vértices passarem por todo
// o pipeline gráfico
void Scene::draw(){

	std::vector<glm::vec4> transf_vertices(vertices.size());

	glm::mat4 m_model_view_proj = m_proj * m_view * m_model;

	for(int i = 0; i < vertices.size(); i++){
		transf_vertices[i] = m_model_view_proj * vertices[i];
		if(transf_vertices[i].w == 0) transf_vertices[i].w += 0.0001f;
		transf_vertices[i] /= transf_vertices[i].w;
		transf_vertices[i] = glm::round(m_screen * transf_vertices[i]);
	}

	Point a, b, c;
	int *vertex;

	for(int i = 0; i < object->faceCount; i++){

		vertex = object->faceList[i]->vertex_index;

		a = Point(transf_vertices[vertex[0]].x, transf_vertices[vertex[0]].y);
		b = Point(transf_vertices[vertex[1]].x, transf_vertices[vertex[1]].y);
		c = Point(transf_vertices[vertex[2]].x, transf_vertices[vertex[2]].y);

		DrawTriangle(a, b, c);
	}

	m_model = glm::mat4();
	m_view = glm::mat4();
	m_proj = glm::mat4();
	m_screen = glm::mat4();
}

// Adiciona (multiplica) uma matriz de rotação à matriz model
void Scene::addRotation(float angle, int x, int y, int z){

	glm::mat4 rot_mat;
	
	float sin_angle = sin(angle * M_PI / 180);
	float cos_angle = cos(angle * M_PI / 180);

	if(x){
		rot_mat[1].y = cos_angle;
		rot_mat[1].z = sin_angle;
		rot_mat[2].y = -sin_angle;
		rot_mat[2].z = cos_angle;
	}
	else if(y){
		rot_mat[0].x = cos_angle;
		rot_mat[0].z = -sin_angle;
		rot_mat[2].x = sin_angle;
		rot_mat[2].z = cos_angle;
	}
	else if(z){
		rot_mat[0].x = cos_angle;
		rot_mat[0].y = sin_angle;
		rot_mat[1].x = -sin_angle;
		rot_mat[1].y = cos_angle;
	}

	m_model = rot_mat * m_model;

}

// Adiciona (multiplica) uma matriz de translação à matriz model
void Scene::addTransl(float x, float y, float z){

	glm::mat4 trans_mat;
	trans_mat[3] = glm::vec4(glm::vec3(x, y, z), 1.0f);
	m_model = trans_mat * m_model;
}

// Aplica uma escala à matriz model
void Scene::addScale(float x, float y, float z){

	glm::mat4 scale_mat;

	scale_mat[0].x = x;
	scale_mat[1].y = y;
	scale_mat[2].z = z;

	m_model = scale_mat * m_model;	
}

// Configura a matriz view de acordo com os parâmretros passados
void Scene::setView(float posX, float posY, float posZ,
			   float lookAtX, float lookAtY, float lookAtZ,
			   float upX, float upY, float upZ)
{

	glm::mat4 T;
	glm::mat4 B;

	glm::vec3 pos(posX, posY, posZ);
	glm::vec3 lookAt(lookAtX, lookAtY, lookAtZ);
	glm::vec3 up(upX, upY, upZ);

	glm::vec3 zc = glm::normalize(pos - lookAt);
	glm::vec3 xc = glm::normalize(glm::cross(up, zc));
	glm::vec3 yc = glm::normalize(glm::cross(zc, xc));

	B[0] = glm::vec4(xc, 0.0f);
	B[1] = glm::vec4(yc, 0.0f);
	B[2] = glm::vec4(zc, 0.0f);
	B[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	T[3] = glm::vec4(-pos, 1.0f);

	m_view = glm::transpose(B) * T;
}

// Configura a matriz projection de acordo com os parâmretros passados
void Scene::setProj(float d){

	m_proj = glm::mat4(1.0f);
	m_proj[2].w = -1/d;
	m_proj[3].z = d;
}

// Configura a matriz de tela de acordo com os parâmretros passados
void Scene::setScreen(int width, int height){

	glm::mat4 inv_y;
	glm::mat4 screen_trans;
	glm::mat4 screen_scale;

	inv_y[1].y = -1;
	screen_trans[3] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	screen_scale[0].x = (width-1) * 0.5f;
	screen_scale[1].y = (height-1) * 0.5f;

	m_screen = screen_scale * screen_trans * inv_y;
}