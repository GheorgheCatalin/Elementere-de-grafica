#include "Object2D.h"

#include <Core/Engine.h>

using namespace std;

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color,  bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateBalloon(std::string name, glm::vec3 center, glm::vec3 color)
{
	
	int N = 70;
	vector<VertexFormat> vertices;
	vector<GLushort> indices;
	Mesh* balloon = new Mesh(name);

	vertices.emplace_back(center, color);
	for (int i = 0; i < N; i++)
	{
		vertices.emplace_back(center + glm::vec3(cos(2 * M_PI * i / N), 1.3 * sin(2 * M_PI * i / N), 0), color);
		indices.push_back(i);
	}
	indices.push_back(N);
	indices.push_back(1);

	indices.push_back(N + 1);
	vertices.emplace_back(center + glm::vec3(-0.2, -1.4, 0), color);
	indices.push_back(N + 2);
	vertices.emplace_back(center + glm::vec3(0.2, -1.4, 0), color);


	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh* Object2D::CreateDisk(std::string name, glm::vec3 center, glm::vec3 color)
{
	int N = 70;
	vector<VertexFormat> vertices;
	vector<GLushort> indices;
	Mesh* disk = new Mesh(name);

	vertices.emplace_back(center, color);
	for (int i = 0; i < N; i++)
	{
		vertices.emplace_back(center + glm::vec3(cos(2 * M_PI * i / N), sin(2 * M_PI * i / N), 0), color);
		indices.push_back(i);
	}
	indices.push_back(N);
	indices.push_back(1);

	disk->SetDrawMode(GL_TRIANGLE_FAN);
	disk->InitFromData(vertices, indices);
	return disk;
}

Mesh* Object2D::CreateString(std::string name, glm::vec3 top, glm::vec3 color)
{
	Mesh* string = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(top, color),
		VertexFormat(top + glm::vec3(-0.25, -0.4 , 0), color),
		VertexFormat(top + glm::vec3(0.15, -0.65, 0), color),
		VertexFormat(top + glm::vec3(-0.25, -1, 0), color),
		VertexFormat(top + glm::vec3(0.2, -1.3, 0), color)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4};

	string->SetDrawMode(GL_LINE_STRIP);
	string->InitFromData(vertices, indices);
	return string;
}

Mesh* Object2D::CreateBow(std::string name, glm::vec3 middle)
{
	int N = 70, i;
	Mesh* string = new Mesh(name);
	vector<VertexFormat> vertices;
	vector<GLushort> indices;
	float arg;
	// Upper bow
	for (i = 0; i <= N/2; i++)
	{
		vertices.emplace_back(middle + glm::vec3(cos(M_PI * i / N ), 2 * sin(M_PI * i / N ), 0), glm::vec3(0.36, 0.22, 0));
		indices.push_back(i);
	}
	// Bowstring
	indices.push_back(N / 2);
	vertices.emplace_back(middle + glm::vec3(cos(M_PI * i / N ), 2 * sin(M_PI  * i / N ), 0), glm::vec3(0.2, 0.2, 0.2));
	indices.push_back(N / 2 + 1);
	vertices.emplace_back(middle + glm::vec3(0, -2, 0), glm::vec3(0.2, 0.2, 0.2));
	// Lower bow
	for (int i = N/2 + 2; i <= N + 1 ; i++)
	{

		vertices.emplace_back(middle + glm::vec3(-cos(M_PI * i / N), -2 * sin(M_PI * i / N), 0), glm::vec3(0.36, 0.22, 0));
		indices.push_back(i);
	}

	string->SetDrawMode(GL_LINE_STRIP);
	string->InitFromData(vertices, indices);
	return string;
}

Mesh* Object2D::CreateArrow(std::string name, glm::vec3 head)
{
	Mesh* arrow = new Mesh(name);
	std::vector<VertexFormat> vertices;
	vertices.emplace_back(head, glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(head + glm::vec3(-1.2, 0.5, 0), glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(head + glm::vec3(-1.2, -0.5, 0), glm::vec3(0.7, 0.7, 0.7));

	std::vector<unsigned short> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	vertices.emplace_back(head + glm::vec3(-6, -0.1, 0), glm::vec3(0.7, 0.3, 0));
	vertices.emplace_back(head + glm::vec3(-1.2, 0.1, 0), glm::vec3(0.7, 0.3, 0));
	vertices.emplace_back(head + glm::vec3(-1.2, -0.1, 0), glm::vec3(0.7, 0.3, 0));
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);
	vertices.emplace_back(head + glm::vec3(-6, 0.1, 0), glm::vec3(0.7, 0.3, 0));
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(6);

	vertices.emplace_back(head + glm::vec3(-6, 0.1, 0), glm::vec3(0.8, 0.8, 0.8));
	vertices.emplace_back(head + glm::vec3(-5.5, 0.1, 0), glm::vec3(0.8, 0.8, 0.8));
	vertices.emplace_back(head + glm::vec3(-6, 0.3, 0), glm::vec3(0.8, 0.8, 0.8));
	indices.push_back(7);
	indices.push_back(8);
	indices.push_back(9);

	vertices.emplace_back(head + glm::vec3(-6, -0.1, 0), glm::vec3(0.8, 0.8, 0.8));
	vertices.emplace_back(head + glm::vec3(-5.5, -0.1, 0), glm::vec3(0.8, 0.8, 0.8));
	vertices.emplace_back(head + glm::vec3(-6, -0.3, 0), glm::vec3(0.8, 0.8, 0.8));
	indices.push_back(11);
	indices.push_back(12);
	indices.push_back(10);

	arrow->InitFromData(vertices, indices);
	return arrow;
}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 center)
{
	Mesh* arrow = new Mesh(name);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	vertices.emplace_back(center, glm::vec3(0.3, 0.3, 0.3));
	vertices.emplace_back(center + glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(center + glm::vec3(1, 1, 0), glm::vec3(0.7, 0.7, 0.7));	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	vertices.emplace_back(center + glm::vec3(0, -1, 0), glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(center + glm::vec3(1, -1, 0), glm::vec3(0.7, 0.7, 0.7));
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	vertices.emplace_back(center + glm::vec3(0, 1, 0), glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(center + glm::vec3(-1, 1, 0), glm::vec3(0.7, 0.7, 0.7));
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(6);

	vertices.emplace_back(center + glm::vec3(-1, -1, 0), glm::vec3(0.7, 0.7, 0.7));
	vertices.emplace_back(center + glm::vec3(-1, 0, 0), glm::vec3(0.7, 0.7, 0.7));
	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(8);

	arrow->InitFromData(vertices, indices);
	return arrow;
}