#include "Mesh.h"
#include "Assimp.h"

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

void Mesh::UploadMesh(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned int* indicies)
{
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vao
	glBindVertexArray(vao);

	//bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as position
	Vertex::SetUpAttributes();

	//bind indicies if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

		iCount = indexCount;
	}
	else
	{
		iCount = indexCount;
	}

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Mesh::CreatePyramid()
{
	std::vector<Vertex> vertices
	{
	//	position			colour			normal		uv
	//south
		{{-15, 0, -15},{0.5, 0.25, 0},	{0, 1, -1},	{0, 0 }},
		{{-10, 10, -10},{0.5, 0.25, 0},	{0, 1, -1},	{0.5,1}},
		{{-5, 0, -15 },{0.5, 0.25, 0},	{0, 1, -1},	{1, 0 }},
	//north
		{{-5, 0, -5 },{0.5, 0.25, 0},	{0, 1, 1},	{0, 0 }},
		{{-10, 10, -10},{0.5, 0.25, 0},	{0, 1, 1},	{0.5,1}},
		{{-15, 0, -5},{0.5, 0.25, 0},	{0, 1, 1},	{1, 0 }},

	//base
		{{-15, 0, -15},{0.5, 0.25, 0},	{0, -1, 0},	{0, 0 }},
		{{-15, 0, -5 },{0.5, 0.25, 0},	{0, -1, 0},	{0, 1 }},
		{{-5, 0, -15 },{0.5, 0.25, 0},	{0, -1, 0},	{1, 0 }},
		{{-15, 0, -5 },{0.5, 0.25, 0},	{0, -1, 0},	{0, 1 }},
		{{-5, 0, -15 },{0.5, 0.25, 0},	{0, -1, 0},	{1, 0 }},
		{{-5, 0, -5  },{0.5, 0.25, 0},	{0, -1, 0},	{1, 1 }},
	//west
		{{-15, 0, -5 },{0.5, 0.30, 0},	{-1, 1, 0},	{0, 0 }},
		{{-10, 10, -10},{0.5, 0.30, 0},	{-1, 1, 0},	{0.5,1}},
		{{-15, 0, -15},{0.5, 0.30, 0},	{-1, 1, 0},	{1, 0 }},
	//east
		{{-5, 0, -15},{0.5, 0.30, 0},	{1, 1, 0},	{0, 0 }},
		{{-10, 10, -10},{0.5, 0.30, 0},	{1, 1, 0},	{0.5,1}},
		{{-5, 0, -5 },{0.5, 0.30, 0},	{1, 1, 0},	{1, 0 }},
	};
	UploadMesh(vertices);
}

void Mesh::InitialiseFromFile(const char* filename)
{
	//will read the verticies from the model
	const aiScene* scene = aiImportFile(filename, 0);

	//just use the first mesh we find for now
	aiMesh* mesh = scene->mMeshes[0];

	//extract indicies from the first mesh
	int numFaces = mesh->mNumFaces;
	std::vector<unsigned int> indicies;

	for (int i = 0; i < numFaces; i++)
	{
		indicies.push_back(mesh->mFaces[i].mIndices[0]);
		indicies.push_back(mesh->mFaces[i].mIndices[2]);
		indicies.push_back(mesh->mFaces[i].mIndices[1]);

		//generate a second triangle for quads
		if (mesh->mFaces[i].mNumIndices == 4)
		{
			indicies.push_back(mesh->mFaces[i].mIndices[0]);
			indicies.push_back(mesh->mFaces[i].mIndices[3]);
			indicies.push_back(mesh->mFaces[i].mIndices[2]);
		}
	}

	//extract vertex data
	int numV = mesh->mNumVertices;
	Vertex* vertecies = new Vertex[numV];
	for (int i = 0; i < numV; i++)
	{
		vertecies[i].position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertecies[i].normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		//uv's
	}
	UploadMesh(numV, vertecies, indicies.size(), indicies.data());

	delete[] vertecies;
}


void Mesh::LoadMaterial(const char* filename)
{
	std::fstream file(filename, std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];
	while (!file.eof())
	{
		file.getline(buffer, 256);
		line = buffer;
		std::stringstream ss(line, std::stringstream::in | std::stringstream::out);

		if (line.find("Ka") == 0)
			ss >> header >> Ka.x >> Ka.y >> Ka.z;
		else if (line.find("Kd") == 0)
			ss >> header >> Kd.x >> Kd.y >> Kd.z;
		else if (line.find("Ks") == 0)
			ss >> header >> Ks.x >> Ks.y >> Ks.z;
		else if (line.find("Ns") == 0)
			ss >> header >> specularPower;
	}
}

void Mesh::ApplyMaterial(ShaderProgram* shader)
{
	shader->SetVectorUniform("Ka", Ka);
	shader->SetVectorUniform("Kd", Kd);
	shader->SetVectorUniform("Ks", Ks);
	shader->SetFloatUniform("specularPower", specularPower);
}


void Mesh::Bind()
{
	glBindVertexArray(vao);
}

void Mesh::Render()
{
	if (vCount <= 0)
	{
		glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vCount);
	}
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
}