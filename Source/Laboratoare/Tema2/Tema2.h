#pragma once

//#include <Component/Transform/Transform.h>
#include <stdlib.h> 
#include <time.h>
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera2.h"
#include <queue> 
#include <Laboratoare/Laborator3/Transform2D.h>
#include <Laboratoare/Laborator3/Object2D.h>

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	//void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3& color, int isSphere);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	Laborator::Camera2* camera;
	glm::vec3 lightPosition;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;

	float sphereX, sphereY, sphereZ, cstY, cameraDistance;
	float platformY, spawnZ;
	int nbPlatforms, redCounter, deformation;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget, jump, fall;
	float counter, speed, platformMax, scale, speedCounter, highSpeed, fuel, deformationCounter;
	std::vector<float> platformSize;
	std::vector<float> platformZ, platformX;
	glm::vec3 red, blue, orange, yellow, purple, green;
	std::vector<glm::vec3> platformType;
	glm::mat3 modelMatrix2, modelMatrix3;
};
