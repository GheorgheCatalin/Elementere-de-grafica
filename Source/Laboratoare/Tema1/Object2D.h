#pragma once

#include <string>
#include <vector>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateBalloon(std::string name, glm::vec3 center, glm::vec3 color);

	Mesh* CreateDisk(std::string name, glm::vec3 center, glm::vec3 color);

	Mesh* CreateString(std::string name, glm::vec3 top, glm::vec3 color);

	Mesh* CreateBow(std::string name, glm::vec3 bot);

	Mesh* CreateArrow(std::string name, glm::vec3 head);

	Mesh* CreateShuriken(std::string name, glm::vec3 center);
}