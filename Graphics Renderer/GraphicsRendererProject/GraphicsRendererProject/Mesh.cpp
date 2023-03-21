#include "Mesh.h"

Mesh::~Mesh()
{
	if (loadedProperly)
	{
		//deletes vao and vbo
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}

void Mesh::UploadMesh(std::vector<Vertex>& vertices)
{
	vCount = vertices.size(); //sets vCount for rendering / future use

	//generates buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//sets buffer data for vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vCount, vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//binds vao and vbo + sets up attributes for the vertices
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	Vertex::SetUpAttributes();
	glBindVertexArray(0);
}

void Mesh::CreatePyramid()
{
	std::vector<Vertex> vertices
	{
	//	position			colour			normal		uv
	//south
		{{-0.5, 0, -0.5},	{0.5, 0.25, 0},	{0, 1, -1},	{0, 0 }},
		{{0, 1, 0      },	{0.5, 0.25, 0},	{0, 1, -1},	{0.5,1}},
		{{0.5, 0, -0.5 },	{0.5, 0.25, 0},	{0, 1, -1},	{1, 0 }},
	//north
		{{0.5, 0, 0.5 },	{0.5, 0.25, 0},	{0, 1, 1},	{0, 0 }},
		{{0, 1, 0     },	{0.5, 0.25, 0},	{0, 1, 1},	{0.5,1}},
		{{-0.5, 0, 0.5},	{0.5, 0.25, 0},	{0, 1, 1},	{1, 0 }},

	//base
		{{-0.5, 0, -0.5},	{0.5, 0.25, 0},	{0, -1, 0},	{0, 0 }},
		{{-0.5, 0, 0.5 },	{0.5, 0.25, 0},	{0, -1, 0},	{0, 1 }},
		{{0.5, 0, -0.5 },	{0.5, 0.25, 0},	{0, -1, 0},	{1, 0 }},
		{{-0.5, 0, 0.5 },	{0.5, 0.25, 0},	{0, -1, 0},	{0, 1 }},
		{{0.5, 0, -0.5 },	{0.5, 0.25, 0},	{0, -1, 0},	{1, 0 }},
		{{0.5, 0, 0.5  },	{0.5, 0.25, 0},	{0, -1, 0},	{1, 1 }},
	//west
		{{-0.5, 0, 0.5 },	{0.5, 0.30, 0},	{-1, 1, 0},	{0, 0 }},
		{{0, 1, 0      },	{0.5, 0.30, 0},	{-1, 1, 0},	{0.5,1}},
		{{-0.5, 0, -0.5},	{0.5, 0.30, 0},	{-1, 1, 0},	{1, 0 }},
	//east
		{{0.5, 0, -0.5},	{0.5, 0.30, 0},	{1, 1, 0},	{0, 0 }},
		{{0, 1, 0     },	{0.5, 0.30, 0},	{1, 1, 0},	{0.5,1}},
		{{0.5, 0, 0.5},		{0.5, 0.30, 0},	{1, 1, 0},	{1, 0 }},
	};
	UploadMesh(vertices);
}

void Mesh::Bind()
{
	glBindVertexArray(vao);
}

void Mesh::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, vCount);
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
}