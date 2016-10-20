#ifndef SCENE_H
#define SCENE_H

#include "../include/glm/gtx/transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "objLoader.h"
#include "mygl.h"

#include <cmath>
#include <vector>
#include <string>

class Scene{
public:
	Scene();
	void load(char file[]);
	void draw();
	void setView(float posX, float posY, float posZ,
			float lookAtX, float lookAtY, float lookAtZ,
			float upX, float upY, float upZ);
	void setProj(float d);
	void setScreen(int width, int height);
	void addRotation(float angle, int x, int y, int z);
	void addTransl(float x, float y, float z);
	void addScale(float x, float y, float z);

private:
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	glm::mat4 m_screen;

	objLoader *object;
	std::vector<glm::vec4> vertices;
};


#endif