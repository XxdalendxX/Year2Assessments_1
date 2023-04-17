#pragma once
#include "Maths.h"
#include "Graphics.h"
#include "Vertex.h"
#include "Text.h"

class Mesh
{
public:
	//Constructor for the Mesh to be left empty.
	Mesh() {};
	//Clears and destroys the mesh object
	~Mesh();

	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh& other) = delete;

	//Creates a square based pyramid mesh
	void CreatePyramid();
	//initialises an imported mesh
	void InitialiseFromFile(const char* filename);
	
	//Generates and binds the vbo and the vao
	void UploadMesh(std::vector<Vertex>& vertices);

	//Generates and binds the vbo and the vao
	void UploadMesh(unsigned int vertexCount, const Vertex* vertecies, unsigned int indexCount = 0, unsigned int* indicies = nullptr);

	//Binds vao
	void Bind();
	//Renders mesh
	void Render();
	//Unbinds vao
	void Unbind();

protected:

	unsigned int vbo; //VertexBufferID
	unsigned int vao; //VertexArrayID (connective tissue not data)
	unsigned int ibo; //Index Buffer Object

	int vCount; //Vertex count
	int iCount; //Index count

	bool loadedProperly = false; //Checks if mesh has loaded without problems
};