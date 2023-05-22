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
	//	position		normal		UV		colour
	//south
		{{-15, 0, -15},	{0, 1, -1},	{0, 0 },{0.5, 0.25, 0}},
		{{-10, 10, -10},{0, 1, -1},	{0.5,1},{0.5, 0.25, 0}},
		{{-5, 0, -15 },	{0, 1, -1},	{1, 0 },{0.5, 0.25, 0}},
	//north
		{{-5, 0, -5 },	{0, 1, 1},	{0, 0 },{0.5, 0.25, 0}},
		{{-10, 10, -10},{0, 1, 1},	{0.5,1},{0.5, 0.25, 0}},
		{{-15, 0, -5},	{0, 1, 1},	{1, 0 },{0.5, 0.25, 0}},

	//base
		{{-15, 0, -15},	{0, -1, 0},	{0, 0 },{0.5, 0.25, 0}},
		{{-15, 0, -5 },	{0, -1, 0},	{0, 1 },{0.5, 0.25, 0}},
		{{-5, 0, -15 },	{0, -1, 0},	{1, 0 },{0.5, 0.25, 0}},
		{{-15, 0, -5 },	{0, -1, 0},	{0, 1 },{0.5, 0.25, 0}},
		{{-5, 0, -15 },	{0, -1, 0},	{1, 0 },{0.5, 0.25, 0}},
		{{-5, 0, -5  },	{0, -1, 0},	{1, 1 },{0.5, 0.25, 0}},
	//west
		{{-15, 0, -5 },	{-1, 1, 0},	{0, 0 },{0.5, 0.30, 0}},
		{{-10, 10, -10},{-1, 1, 0},	{0.5,1},{0.5, 0.30, 0}},
		{{-15, 0, -15},	{-1, 1, 0},	{1, 0 },{0.5, 0.30, 0}},
	//east
		{{-5, 0, -15},	{1, 1, 0},	{0, 0 },{0.5, 0.30, 0}},
		{{-10, 10, -10},{1, 1, 0},	{0.5,1},{0.5, 0.30, 0}},
		{{-5, 0, -5 },	{1, 1, 0},	{1, 0 },{0.5, 0.30, 0}},
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
		if (mesh->mTextureCoords[0])
			vertecies[i].uv = vec2(mesh->mTextureCoords[0][i].x, -mesh->mTextureCoords[0][i].y);
		else
			vertecies[i].uv = vec2(0);
		if (mesh->HasTangentsAndBitangents())
			vertecies[i].tangent = vec4(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z, 1);
	}

	if (!mesh->HasTangentsAndBitangents())
		CalculateTangents(vertecies, numV, indicies);

	UploadMesh(numV, vertecies, indicies.size(), indicies.data());

	delete[] vertecies;
}

void Mesh::InitialiseFromFile(const char* filename, vec3 pos)
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
		vertecies[i].position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z) + pos;
		vertecies[i].normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
			vertecies[i].uv = vec2(mesh->mTextureCoords[0][i].x, -mesh->mTextureCoords[0][i].y);
		else
			vertecies[i].uv = vec2(0);
		if (mesh->HasTangentsAndBitangents())
			vertecies[i].tangent = vec4(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z, 1);
	}

	if (!mesh->HasTangentsAndBitangents())
		CalculateTangents(vertecies, numV, indicies);

	UploadMesh(numV, vertecies, indicies.size(), indicies.data());

	delete[] vertecies;
}


void Mesh::LoadMaterial(const char* filename)
{
	std::fstream file(filename, std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];

	std::string directory(filename);
	int index = directory.rfind('/');
	if (index != -1)
		directory = directory.substr(0, index + 1);

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
		else if (line.find("map_Kd") == 0)
		{
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapKd.SetDirectory((directory + mapFileName));
			mapKd.LoadFromFile(mapKd.GetDirectory());
			if (mapKd.CheckStatus())
				std::cout << "Diffuse map has loaded properly" << std::endl;
			else
				std::cout << "Diffuse map has not loaded properly" << std::endl;
			mapKd.ReadDirectory();
		}
		else if (line.find("map_Ks") == 0)
		{
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapKs.SetDirectory((directory + mapFileName));
			mapKs.LoadFromFile(mapKs.GetDirectory());
			if (mapKs.CheckStatus())
				std::cout << "Specular map has loaded properly" << std::endl;
			else
				std::cout << "Specular map has not loaded properly" << std::endl;
			mapKs.ReadDirectory();

		}
		else if (line.find("bump") == 0)
		{
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapBump.SetDirectory((directory + mapFileName));
			mapBump.LoadFromFile(mapBump.GetDirectory());
			if (mapBump.CheckStatus())
				std::cout << "Normal map has loaded properly" << std::endl;
			else
				std::cout << "Normal map has not loaded properly" << std::endl;
			mapBump.ReadDirectory();
		}
	}
}

void Mesh::ApplyMaterial(ShaderProgram* shader)
{
	shader->SetVectorUniform("Ka", Ka);
	shader->SetVectorUniform("Kd", Kd);
	shader->SetVectorUniform("Ks", Ks);
	shader->SetFloatUniform("specularPower", specularPower);

	mapKd.Bind(0);
	shader->SetIntergerUniform("textureSampler", 0);
	mapKs.Bind(1);
	shader->SetIntergerUniform("textureSpec", 1);
	mapBump.Bind(2);
	shader->SetIntergerUniform("textureNorm", 2);
}

void Mesh::CalculateTangents(Vertex* vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices)
{
	vec4* tan1 = new glm::vec4[vertexCount * 2];
	vec4* tan2 = tan1 + vertexCount;
	memset(tan1, 0, vertexCount * sizeof(vec4) * 2);

	unsigned int indexCount = (unsigned int)indices.size();
	for (unsigned int a = 0; a < indexCount; a += 3)
	{
		long i1 = indices[a];
		long i2 = indices[a + 1];
		long i3 = indices[a + 2];

		const vec3& v1 = vertices[i1].position;
		const vec3& v2 = vertices[i2].position;
		const vec3& v3 = vertices[i3].position;

		const vec2& w1 = vertices[i1].uv;
		const vec2& w2 = vertices[i2].uv;
		const vec2& w3 = vertices[i3].uv;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0f / (s1 * t2 - s2 * t1);

		vec4 sDir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r, 0);
		vec4 tDir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r, 0);

		tan1[i1] += sDir;
		tan1[i2] += sDir;
		tan1[i3] += sDir;

		tan2[i1] += tDir;
		tan2[i2] += tDir;
		tan2[i3] += tDir;
	}

	for (unsigned int a = 0; a < vertexCount; a++)
	{
		const vec3& n = vec3(vertices[a].normal);
		const vec3& t = vec3(tan1[a]);

		//Gram-Schmidt orthogonalize
		vertices[a].tangent = vec4(glm::normalize(t - n * glm::dot(n, t)), 0);

		//calculate handedness (direction of bitangent)
		vertices[a].tangent.w = (glm::dot(glm::cross(vec3(n), vec3(t)), vec3(tan2[a])) < 0.0F) ? 1.0F : -1.0F;
	}

	delete[] tan1;
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